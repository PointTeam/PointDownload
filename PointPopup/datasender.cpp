#include "datasender.h"

DataSender::DataSender(TaskInfo taskInfo, QObject *parent) :
    QObject(parent),gTaskInfo(taskInfo)
{
    localSocket = new QLocalSocket(this);
}

void DataSender::startDownload()
{
    if (!QDBusConnection::sessionBus().registerService(MAIN_PROGRAM_DBUS_NAME))
    {    // 服务端的serverNewConnectionHandler成员方法将被调用
        localSocket->connectToServer(TASK_RECEIVER_SERVER);
        if (localSocket->waitForConnected())
        {
            qDebug() << "connect to main program success...";
            if (localSocket->write(gTaskInfo.pToQByteArray()) == -1)
                qWarning() << "localSocket write error";
            localSocket->flush();
            localSocket->waitForBytesWritten();

            qApp->quit();
        }
        else
        {
            qDebug() << "connect faild...";
            return;
        }

    }
    else
    {
        qDebug() << "[Info]: starting main program...";
        startMainProgram();
    }
}

void DataSender::startMainProgramError(QProcess::ProcessError error)
{
    qDebug()<< "[Error]:" << error;
}

void DataSender::startMainProgram()
{
    //每次启动前先尝试启动主程序
    QStringList arguments;
    arguments << "-c";

    //该指针指向另外一个被启动的程序，所以 绝对不能被delete
    QProcess * myProcess = new QProcess();

    connect(myProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(startMainProgramError(QProcess::ProcessError)));
    connect(myProcess, SIGNAL(started()), this, SLOT(connectToMainProgram()));
    connect(myProcess, SIGNAL(finished(int)), myProcess, SLOT(deleteLater()));

    myProcess->start(MAIN_PROGRAM_EXEC, arguments);
}

void DataSender::connectToMainProgram()
{
    localSocket->connectToServer(TASK_RECEIVER_SERVER);
    if (localSocket->waitForConnected(10000))
    {
        qWarning() << "Connected to PointURLServer!";
        startDownload();
        return;
    }
    else
    {
        qWarning() << "[Error]: LocalSocket connect to localServer Error: " << localSocket->errorString();
    }
}

DataSender::~DataSender()
{

}

