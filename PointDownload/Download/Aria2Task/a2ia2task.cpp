#include "a2ia2task.h"

A2ia2Task::A2ia2Task(QObject *parent) :
    QObject(parent)
{
}

void A2ia2Task::startDownload(PrepareDownloadInfo info)
{
//    //每次启动前先尝试启动主程序
//    QObject * mparent;
//    QStringList arguments;
//    arguments << "-c";

//    //该指针指向另外一个被启动的程序，所以 绝对不能被delete
//    QProcess * myProcess = new QProcess(parent);
//    myProcess->start(MAIN_PROGRAM_PATH,arguments);
//    connect(myProcess,SIGNAL(started()),this,SLOT(mainStarted()));
}

void A2ia2Task::suspendDownloading(QString URL)
{

}

void A2ia2Task::resumeDownloading(QString URL)
{

}
