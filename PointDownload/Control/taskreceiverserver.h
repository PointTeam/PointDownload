#ifndef TASKRECEIVERSERVER_H
#define TASKRECEIVERSERVER_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include "pdatatype.h"
#include "taskinfo.h"
#include "maincontroller.h"

class TaskReceiverServer : public QObject
{
    Q_OBJECT
public:
    explicit TaskReceiverServer(QObject *parent = 0);
    ~TaskReceiverServer();

    void startServer();

signals:
    void newTaskAdded(const TaskInfo &taskInfo);

private slots:
    void serverNewConnectionHandler();
    void socketReadyReadHandler();

private:
    QLocalServer * localServer;

    const QString TASK_RECEIVER_SERVER = "PointURLServer";
};

#endif // TASKRECEIVERSERVER_H
