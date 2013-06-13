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
    if (surface == directRenderSurface())
        return;

    QWaylandCompositor::setDirectRenderSurface(surface, openglContext());

    emit directRenderSurfaceChanged();
}

void Compositor::resizeEvent(QResizeEvent *event)
{
    QQuickWindow::resizeEvent(event);
    QWaylandCompositor::setOutputGeometry(QRect(0, 0, width(), height()));
}

void Compositor::surfaceCreated(QWaylandSurface *surface)
{
    connect(surface, SIGNAL(mapped()), SLOT(surfaceMapped()));
    connect(surface, SIGNAL(destroyed(QObject*)), SLOT(surfaceDestroyed()));
}

void Compositor::surfaceMapped()
{
    if (QWaylandSurface *surface = qobject_cast<QWaylandSurface*>(sender())) {
        if (!surface->hasShellSurface())
            return;

        if (d->model.insertRow(d->model.rowCount())) {
            d->model.setData(d->model.index(d->model.rowCount() - 1), QVariant::fromValue(surface));
        } else {
            qWarning("Unable to add surface to model.");
        }
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
