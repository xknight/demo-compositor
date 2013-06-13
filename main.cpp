#include <QGuiApplication>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QWaylandSurfaceItem>
#include <QWaylandSurface>
#include "compositor.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    qmlRegisterRevision<QWindow, 1>("Compositor", 1, 0);
    qmlRegisterType<QWaylandSurfaceItem>("QtQuick.Compositor", 1, 0, "WaylandSurfaceItem");
    qmlRegisterType<QWaylandSurface>("QtQuick.Compositor", 1, 0, "WaylandSurface");
    qmlRegisterType<Compositor>("Compositor", 1, 0, "Compositor");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine(QUrl("qrc:/main.qml"));

    return app.exec();
}
