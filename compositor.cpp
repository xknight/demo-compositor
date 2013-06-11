#include "compositor.h"
#include "waylandsurfacemodel.h"

#include <QWaylandSurface>

#include <QDebug>

class CompositorPrivate
{
friend class Compositor;
    WaylandSurfaceModel model;
};

Compositor::Compositor()
    : QQuickWindow()
    , QWaylandCompositor(this)
    , d(new CompositorPrivate)
{
    setClientFullScreenHint(true);
    connect(this, &QQuickWindow::frameSwapped, this, &Compositor::frameFinished);
}

Compositor::~Compositor()
{
    delete d;
}

QObject *Compositor::model() const
{
    return &d->model;
}

void Compositor::setDirectRenderSurface(QWaylandSurface *surface)
{
    if (surface) {
        QWaylandCompositor::setDirectRenderSurface(surface, openglContext());
    } else {
        //...
    }
}

void Compositor::resizeEvent(QResizeEvent *event)
{
    QQuickWindow::resizeEvent(event);
    QWaylandCompositor::setOutputGeometry(QRect(0, 0, width(), height()));
}

void Compositor::surfaceCreated(QWaylandSurface *surface)
{
    if (d->model.insertRow(d->model.rowCount())) {
        connect(surface, SIGNAL(mapped()), SLOT(surfaceMapped()));
        connect(surface, SIGNAL(destroyed(QObject*)), SLOT(surfaceDestroyed()));
    } else {
        qWarning("Unable to add surface to model.");
    }
}

void Compositor::surfaceMapped()
{
    if (QWaylandSurface *surface = qobject_cast<QWaylandSurface*>(sender())) {

        qDebug() << "surface mapped" << surface << surface->image().size() << surface->image().format() << surface->image().bytesPerLine();

        if (!surface->hasShellSurface())
            return;

        d->model.setData(d->model.index(d->model.rowCount() - 1), QVariant::fromValue(surface));
    }
}

void Compositor::surfaceDestroyed()
{
    qDebug() << "destroyed";
}

void Compositor::frameFinished()
{
    QWaylandCompositor::frameFinished();
}
