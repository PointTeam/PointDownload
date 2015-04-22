#include "taskreceiverserver.h"

TaskReceiverServer::TaskReceiverServer(QObject *parent) :
    QObject(parent)
{

}

void TaskReceiverServer::startServer()
{
    QLocalServer::removeServer(TASK_RECEIVER_SERVER);
    localServer = new QLocalServer(this);
    if (!localServer->listen(TASK_RECEIVER_SERVER))
        qWarning() << "localServer listen error!" << localServer->errorString();
    else
        qWarning() << "[Info]: " << TASK_RECEIVER_SERVER << "started!";

    connect(localServer, SIGNAL(newConnection()), this, SLOT(serverNewConnectionHandler()));
}

TaskReceiverServer::~TaskReceiverServer()
{

}

void TaskReceiverServer::serverNewConnectionHandler()
{
    QLocalSocket * socket = localServer->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyReadHandler()));
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
}

void TaskReceiverServer::socketReadyReadHandler()
{
    QLocalSocket * socket = static_cast<QLocalSocket*>(sender());
    TaskInfo taskInfo(socket);

    //启动下载
    MainController::getInstance()->pStartDownload(taskInfo);

    emit newTaskAdded(taskInfo);
}
