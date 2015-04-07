#include "aria2process.h"

Aria2Process::Aria2Process(TaskInfo *taskInfo, QObject *parent) :
    QObject(parent),taskInfo(taskInfo)
{
    lastDataSize = "0";
    xmlUpdateInterval = 1;
}

void Aria2Process::startDownload()
{
    SettingXMLHandler tmpHandler;
    tmpProcess = new QProcess(0);
    connect(tmpProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(getFeedBack()));
    connect(tmpProcess, SIGNAL(readyReadStandardError()), this, SLOT(getError()));
    connect(tmpProcess, SIGNAL(started()), this, SLOT(aria2Started()));
    QStringList arguments;

    arguments << QString("--auto-save-interval=10");
    arguments << QString("--summary-interval=1");
    arguments << QString("-x ") + QString::number(taskInfo->maxThreads);
    arguments << taskInfo->rawUrl;
    tmpProcess->setWorkingDirectory(taskInfo->savePath);
    tmpProcess->start(tmpHandler.getChildElement(Aria2Setting,"ExecutePath"),arguments);
}

void Aria2Process::stopDownload()
{
    tmpProcess->terminate();
}

void Aria2Process::aria2Started()
{
    //进程启动完成后再启动定时器
    updateTimer = new QTimer();
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(getTimerUpdate()));
    updateTimer->start(UPDATE_INTERVAL);
}

void Aria2Process::getFeedBack()
{
    //直接从命令行传来的东西速度不定，所以放在全局变量中以定时器定时发送数据
    QString outPut = QString(tmpProcess->readAllStandardOutput());

    gFeedBackInfo = outPut;
}

void Aria2Process::getTimerUpdate()
{
    DownloadingItemInfo tmpInfo;
    //complete or error
    if (gFeedBackInfo.contains("+====+===========+"))
    {
        if (gFeedBackInfo.contains("|OK"))
        {
            tmpInfo.downloadSpeed =  "0 KB/S";
            tmpInfo.downloadPercent = 100;//下载百分比
            tmpInfo.downloadState = dlstate_downloading;
            tmpInfo.downloadURL = taskInfo->rawUrl;
            //send to aria2task,last update
            emit updateData(tmpInfo);

            updateTimer->stop();
            tmpProcess->terminate();
            this->deleteLater();

            emit sFinishAria2Download(taskInfo->rawUrl);
        }
        else
        {
            emit aria2Error(taskInfo->rawUrl,gFeedBackInfo, TOOL_ARIA2);
        }
    }
    else
    {
        QString tmpInfoString = gFeedBackInfo.split("\n").at(0);
        if (!tmpInfoString.contains("%)"))
            return;

        tmpInfo.downloadSpeed
                = analysisFeedBackSpeed(gFeedBackInfo.mid(gFeedBackInfo.indexOf("DL:") + 3
                                                          ,gFeedBackInfo.indexOf(" ",gFeedBackInfo.indexOf("DL:"))
                                                          - gFeedBackInfo.indexOf("DL:") - 3));
        tmpInfo.downloadPercent
                = gFeedBackInfo.mid(tmpInfoString.indexOf("(") + 1
                                    ,tmpInfoString.indexOf("%)") - tmpInfoString.indexOf("(") - 1).toDouble();//下载百分比
        tmpInfo.downloadState = dlstate_downloading;
        tmpInfo.downloadURL = taskInfo->rawUrl;

        //send to aria2task
        emit updateData(tmpInfo);
    }

    //update xml file
    if (xmlUpdateInterval == UPDATE_XML_INTERVAL)
    {
        xmlUpdateInterval = 1;
        updateXMLFile(tmpInfo);
    }
    else
        xmlUpdateInterval ++;
}

void Aria2Process::updateXMLFile(DownloadingItemInfo info)
{
    DownloadXMLHandler tmpOpera;
    SDownloading tmpStruct = tmpOpera.getDownloadingNode(info.downloadURL);
    //计算平均速度，用作优先下载的判断条件
    tmpStruct.averageSpeed = QString::number(qint64((info.downloadPercent / 100 * tmpStruct.totalSize.toDouble()//当前完成大小
                                                    - tmpStruct.readySize.toDouble()//上次完成大小
                                                    ) / UPDATE_XML_INTERVAL));
    tmpStruct.readySize = QString::number(qint64(info.downloadPercent / 100 * tmpStruct.totalSize.toLongLong()));
    tmpOpera.writeDownloadingConfigFile(tmpStruct);
}

void Aria2Process::getError()
{
    qDebug() << tmpProcess->readAllStandardError();
    emit aria2Error(taskInfo->rawUrl, QString(tmpProcess->readAllStandardError()), TOOL_ARIA2);
}

QString Aria2Process::analysisFeedBackSpeed(QString data)
{
    if (data.contains("MiB"))
    {
        return QString::number(data.left(data.length() - 3).toDouble() * 1024) + " KB/S";
    }
    else if (data.contains("KiB"))
    {
        return data.left(data.length() - 3) + " KB/S";
    }
    else
        return "0.0 KB/S";
}
