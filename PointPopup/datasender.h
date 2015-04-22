#ifndef DATASENDER_H
#define DATASENDER_H

#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QLocalSocket>
#include <QDBusConnection>
#include <QApplication>
#include <QDebug>
#include "taskinfo.h"

class DataSender : public QObject
{
    Q_OBJECT
public:
    explicit DataSender(TaskInfo taskInfo, QObject *parent = 0);
    ~DataSender();

    void startDownload();
signals:

public slots:

private slots:
    void startMainProgramError(QProcess::ProcessError error);
    void connectToMainProgram();

private:
    void startMainProgram();                    //尝试启动主程序

private:
    TaskInfo gTaskInfo;
    QLocalSocket * localSocket;

    const QString MAIN_PROGRAM_EXEC = "/opt/Point/PointDownload/PointDownload";
    const QString MAIN_PROGRAM_DBUS_NAME = "org.point.pointdownload";
    const QString TASK_RECEIVER_SERVER = "PointURLServer";
};

#endif // DATASENDER_H
