#include "datasender.h"

DataSender::DataSender(QObject *parent) :
    QObject(parent)
{
    localSocket = new QLocalSocket(this);
    startMainProgram();
}

void DataSender::startDownload(TaskInfo taskInfo)
{
    if (!QDBusConnection::sessionBus().registerService(MAIN_PROGRAM_DBUS_NAME))
    {
        if (!localSocket->isValid())
            localSocket->connectToServer(TASK_RECEIVER_SERVER);
        if (localSocket->waitForConnected())
        {
            qDebug() << "[Info]: connect to main program success...";
            if (localSocket->write(taskInfo.toQByteArray()) == -1)
                qWarning() << "[Error]: localSocket write error";
            localSocket->flush();
            localSocket->waitForBytesWritten();

            qApp->quit();
        }
        else
        {
            qDebug() << "[Error]: connect to main program faild...";
            return;
        }

    }
    else
    {
        qDebug() << "[Error]: main program not running!";
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

    myProcess->start(MAIN_PROGRAM_EXEC, arguments);
}


DataSender::~DataSender()
{

}

