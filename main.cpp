#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

#include "tabletwindow.h"

#include <QtPlugin>
#ifdef __arm__
Q_IMPORT_PLUGIN(QsgEpaperPlugin)
#endif

int main(int argc, char *argv[])
{
    qmlRegisterType<TabletWindow>("Test", 1, 0, "TabletWindow");
    qmlRegisterType<TabletCanvas>("Test", 1, 0, "TabletCanvas");

#ifdef __arm__
    qputenv("QMLSCENE_DEVICE", "epaper");
    qputenv("QT_QPA_PLATFORM", "epaper:enable_fonts");
    qputenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS", "rotate=180");
    qputenv("QT_QPA_GENERIC_PLUGINS", "evdevtablet");
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
