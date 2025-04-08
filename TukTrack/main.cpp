#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "corecontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    CoreController controller;
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("TukTrack", "Main");

    return app.exec();
}
