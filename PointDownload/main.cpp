#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDBusConnection>
#include <QDebug>
#include "pdatatype.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!QDBusConnection::sessionBus().registerService("org.point.pointdownload"))
    {
        qDebug() << "Warning: process is running...";
        return 0;
    }

    qmlRegisterType<PDataType>("PDataType", 1, 0, "PDataType");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/PointDownload/main.qml")));

    return app.exec();
}
