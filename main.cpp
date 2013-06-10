#include <QGuiApplication>
#include "compositor.h"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    Compositor compositor;
    compositor.showFullScreen();

    return app.exec();
}
