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

    Q_INVOKABLE void setDirectRenderSurface(QWaylandSurface *surface);

protected:
    void resizeEvent(QResizeEvent *);
    void surfaceCreated(QWaylandSurface *surface);

private slots:
    void surfaceMapped();
    void surfaceDestroyed();

private:
    void frameFinished();

    CompositorPrivate *d;
};

#endif // COMPOSITOR_H
