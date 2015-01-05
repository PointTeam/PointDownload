#include "aria2task.h"

Aria2Task::Aria2Task(QObject *parent) :
    QObject(parent)
{
    initConnection();
}

Aria2Task * Aria2Task::aria2Task = NULL;
Aria2Task * Aria2Task::getInstance()
{
    if (aria2Task == NULL)
    {
        aria2Task = new Aria2Task();
    }
    return aria2Task;
}


void Aria2Task::startDownload(const TaskInfo &taskInfo)
{
    Aria2Process * aria2Process = new Aria2Process(taskInfo);
    connect(aria2Process, SIGNAL(updateData(DownloadingItemInfo)), this ,SIGNAL(sRealTimeData(DownloadingItemInfo)));
    connect(aria2Process, SIGNAL(aria2Error(QString,QString,DownloadToolsType))
            ,this ,SIGNAL(sAria2Error(QString,QString,DownloadToolsType)));
    connect(aria2Process, SIGNAL(sFinishAria2Download(QString)),
            this, SLOT(slotFinishDownload(QString)));

    aria2Process->startDownload();

    //保存下载列表
    gProcessMap.insert(taskInfo.rawUrl, aria2Process);
}

void Aria2Task::stopDownload(QString URL)
{
    if (gProcessMap.value(URL) == NULL)
        return;
    gProcessMap.value(URL)->stopDownload();
}

void Aria2Task::suspendDownloading(QString URL)
{
    if (gProcessMap.value(URL) == NULL)
        return
    gProcessMap.value(URL)->stopDownload();
}

void Aria2Task::resumeDownloading(QString URL)
{
    if (gProcessMap.value(URL) == NULL)
    {
        startDownload(getPrepareInfoFromXML(URL));
    }
    else
        gProcessMap.value(URL)->startDownload();
}

void Aria2Task::slotFinishDownload(QString URL)
{
    gProcessMap.remove(URL);

    UnifiedInterface::getInstance()->cleanDownloadFinishItem(URL);
}


TaskInfo Aria2Task::getPrepareInfoFromXML(QString URL)
{
    DownloadXMLHandler xmlOpera;
    SDownloading ingNode = xmlOpera.getDownloadingNode(URL);

    TaskInfo taskInfo;
    TaskFileItem fileItem;

    taskInfo.rawUrl = ingNode.URL;
    taskInfo.taskIconPath = ingNode.iconPath;
    taskInfo.maxSpeed = 0;
    taskInfo.parseUrl = ingNode.redirectURL;
    taskInfo.savePath = ingNode.savePath;
    taskInfo.maxThreads = ingNode.threadList.size();
    taskInfo.toolType = TOOL_ARIA2;

    fileItem.fileName = ingNode.name;
    fileItem.fileSize = ingNode.totalSize.toLongLong();
    taskInfo.fileList.append(fileItem);

    return taskInfo;
}


void Aria2Task::initConnection()
{
    connect(this, SIGNAL(sRealTimeData(DownloadingItemInfo)),
            UnifiedInterface::getInstance(), SIGNAL(sRealTimeData(DownloadingItemInfo)));
    connect(this, SIGNAL(sAria2Error(QString,QString,DownloadToolsType)),
            UnifiedInterface::getInstance(), SLOT(downloadGetError(QString,QString,DownloadToolsType)));
}
