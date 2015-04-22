#ifndef DATASENDER_H
#define DATASENDER_H

#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QLocalSocket>
#include <QDBusConnection>
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include "taskinfo.h"

class DataSender : public QObject
{
    Q_OBJECT
public:
    explicit DataSender(QObject *parent = 0);
    ~DataSender();

signals:

public slots:
    void startDownload(TaskInfo taskInfo);

private slots:
    void startMainProgramError(QProcess::ProcessError error);

private:
    void startMainProgram();                    //尝试启动主程序

private:
    QLocalSocket * localSocket;

    const QString MAIN_PROGRAM_EXEC = "/opt/Point/PointDownload/PointDownload";
    const QString MAIN_PROGRAM_DBUS_NAME = "org.point.pointdownload";
    const QString TASK_RECEIVER_SERVER = "PointURLServer";
};

#endif // DATASENDER_H
