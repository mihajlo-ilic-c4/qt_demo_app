/*
 * Copyright 2023 Snap One, LLC. All Rights Reserved.
*/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QQmlContext>

#include "FpsCounter.hpp"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);

    qmlRegisterType<FpsCounter>("PerfModule", 1, 0, "FpsCounter");

    QSettings settings("./demo_config.ini", QSettings::IniFormat);

    unsigned listSize = settings.value("list-size", 10000).toUInt();
    bool autoScroll = settings.value("auto-scroll", false).toBool();
    bool autoScrollExit = settings.value("auto-scroll-exit", true).toBool();
    unsigned scrollSpeed = settings.value("scroll-speed", 500).toUInt();
    bool transparentDelegates = settings.value("transparent-delegates", true).toBool();
    bool useFpsCounter = settings.value("show-fps-counter", true).toBool();

    engine.rootContext()->setContextProperty("listSize", listSize);
    engine.rootContext()->setContextProperty("autoScrollExit", autoScrollExit);
    engine.rootContext()->setContextProperty("autoScroll", autoScroll);
    engine.rootContext()->setContextProperty("scrollSpeed", scrollSpeed);
    engine.rootContext()->setContextProperty("transparentDelegates", transparentDelegates);
    engine.rootContext()->setContextProperty("useFpsCounter", useFpsCounter);

    engine.load(url);

    return app.exec();
}
