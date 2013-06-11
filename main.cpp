#include <QGuiApplication>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QWaylandSurfaceItem>
#include <QWaylandSurface>
#include "compositor.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    qmlRegisterType<QWaylandSurfaceItem>("QtQuick.Compositor", 1, 0, "WaylandSurfaceItem");
    qmlRegisterType<QWaylandSurface>("QtQuick.Compositor", 1, 0, "WaylandSurface");
    qmlRegisterType<Compositor>("Compositor", 1, 0, "Compositor");

    QGuiApplication app(argc, argv);

    QQmlEngine engine;
    QQmlComponent component(&engine, QUrl("qrc:/main.qml"));
    if (Compositor *compositor = qobject_cast<Compositor*>(component.create())) {
        QSurfaceFormat format = compositor->format();
        /*format.setAlphaBufferSize(8);
        format.setRedBufferSize(8);
        format.setGreenBufferSize(8);
        format.setBlueBufferSize(8);
        compositor->setFormat(format);*/
        qDebug() << format;
        compositor->showFullScreen();
    } else {
        qWarning("Error: %s", qPrintable(component.errorString()));
    }

    return app.exec();
}
