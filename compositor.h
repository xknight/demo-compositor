#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include <QQuickWindow>
#include <QWaylandCompositor>

class Compositor : public QQuickWindow, public QWaylandCompositor
{
    Q_OBJECT
public:
    Compositor();

    void surfaceCreated(QWaylandSurface *surface);
};

#endif // COMPOSITOR_H
