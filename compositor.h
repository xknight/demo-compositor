#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include <QQuickWindow>
#include <QWaylandCompositor>

class CompositorPrivate;

class Compositor : public QQuickWindow, public QWaylandCompositor
{
    Q_OBJECT
    Q_PROPERTY(QObject * model READ model CONSTANT)

public:
    explicit Compositor();
    ~Compositor();

    QObject *model() const;

protected:
    void surfaceCreated(QWaylandSurface *surface);

    CompositorPrivate *d;
};

#endif // COMPOSITOR_H
