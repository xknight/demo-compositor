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
    : d(new CompositorPrivate)
{

}

Compositor::~Compositor()
{
    delete d;
}

QObject *Compositor::model() const
{
    return &d->model;
}

void Compositor::surfaceCreated(QWaylandSurface *surface)
{
    qDebug() << "Surface created" << surface;
    if (d->model.insertRow(d->model.rowCount())) {
        d->model.setData(d->model.index(d->model.rowCount()),
                         QVariant::fromValue(surface));
    } else {
        qDebug() << "Unable to add surface to model. Figure out why!";
    }
}
