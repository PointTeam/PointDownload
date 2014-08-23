#include "xwaretask.h"

#define UPDATE_XML_INTERVAL 3

XwareTask::XwareTask(QObject *parent) :
    QObject(parent)
{
    connect(XwareController::getInstance(), SIGNAL(sRealTimeDataChanged(DownloadingItemInfo)),
            this, SLOT(updateRealTimeData(DownloadingItemInfo)));

    connect(XwareController::getInstance(), SIGNAL(sFinishDownload(QString)),
            this, SIGNAL(sFinishXwareDownload(QString)));

    xmlUpdateInterval = 0;
}

XwareTask * XwareTask::xwareTask = NULL;
XwareTask::~XwareTask()
{
    qDebug()<<"~XwareTask()  was be called !!";
}

XwareTask * XwareTask::getInstance()
{
    if (xwareTask == NULL)
        xwareTask = new XwareTask();
    return xwareTask;
}

void XwareTask::addNewDownload(PrepareDownloadInfo info)
{
    QString mappingDir = "";
    // mappingDir = XwareDloadFolderController::getInstance()->getMappingFolder(info.storageDir);

    XwarePopulateObject::getInstance()->addNewDownloadTask(info.downloadURL, mappingDir, QStringList()<<info.fileName);
}

void XwareTask::stopDownload(QString URL)
{
    suspendDownloading(URL);
}

void XwareTask::suspendDownloading(QString URL)
{
    QString tid = XwarePopulateObject::getInstance()->getTaskIdByUrl(URL);
    if(tid == "-1")
    {
        // error
        emit sXwareError(URL, QString("no task can not be found by URL:" + URL), Xware);
        return;
    }

    XwarePopulateObject::getInstance()->suspendDownloadingTask(tid);
}

void XwareTask::resumeDownloading(QString URL)
{
    QString tid = XwarePopulateObject::getInstance()->getTaskIdByUrl(URL);
    if(tid == "-1")
    {
        // error
        emit sXwareError(URL, QString("no task can not be found by URL:" + URL), Xware);
        return;
    }

    XwarePopulateObject::getInstance()->resumeDownloadingTask(tid);
}

void XwareTask::entryOfflineChannel(QString URL)
{
    QString tid = XwarePopulateObject::getInstance()->getTaskIdByUrl(URL);
    if(tid == "-1")
    {
        // error
        emit sXwareError(URL, QString("no task can not be found by URL:" + URL), Xware);
        return;
    }

    XwarePopulateObject::getInstance()->entryOfflineChannel(tid);
}

void XwareTask::entryHighSpeedChannel(QString URL)
{
    QString tid = XwarePopulateObject::getInstance()->getTaskIdByUrl(URL);
    if(tid == "-1")
    {
        // error
        emit sXwareError(URL, QString("no task can not be found by URL:" + URL), Xware);
        return;
    }

    XwarePopulateObject::getInstance()->entryHighSpeedChannel(tid);
}

void XwareTask::updateRealTimeData(DownloadingItemInfo info)
{
    emit sRealTimeData(info);

    //update xml file
    if (xmlUpdateInterval == UPDATE_XML_INTERVAL)
    {
        xmlUpdateInterval = 0;
        updateXMLFile(info);
    }
    else
        xmlUpdateInterval ++;
}

void XwareTask::updateXMLFile(DownloadingItemInfo info)
{

//    qDebug()<<"updateXMLFile";

    DownloadXMLHandler tmpOpera;
    SDownloading tmpStruct = tmpOpera.getDownloadingNode(info.downloadURL);
    //计算平均速度，用作优先下载的判断条件
    tmpStruct.averageSpeed = QString::number(qint64((info.downloadPercent / 100 * tmpStruct.totalSize.toDouble()//当前完成大小
                                                    - tmpStruct.readySize.toDouble()//上次完成大小
                                                    ) / UPDATE_XML_INTERVAL));
    tmpStruct.readySize = QString::number(qint64(info.downloadPercent / 100 * tmpStruct.totalSize.toLongLong()));

    qDebug()<<"****************************  readySize :"<<tmpStruct.readySize<<"*****************************";

    tmpOpera.writeDownloadingConfigFile(tmpStruct);
}

