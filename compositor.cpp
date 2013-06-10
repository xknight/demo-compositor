#include "compositor.h"

#include <QDebug>

Compositor::Compositor()
{
}

void Compositor::surfaceCreated(QWaylandSurface *surface)
{
    qDebug() << "Surface created" << surface;
}
