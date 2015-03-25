#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDBusConnection>
#include <QDebug>
#include "pdatatype.h"
#include "taskinfo.h"
#include "Control/maincontroller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!QDBusConnection::sessionBus().registerService("org.point.pointdownload"))
    {
        qDebug() << "Warning: process is running...";
        return 0;
    }

    MainController::getInstance();

    qmlRegisterType<PDataType>("PDataType", 1, 0, "PDataType");
    qmlRegisterType<TaskInfo>("TaskInfo", 1, 0, "TaskInfo");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/PointDownload/main.qml")));

    return app.exec();
}
