#include "dldataconverter.h"
#include "taskinfo.h"

#include <QtQml>
#include <QQuickView>

DLDataConverter::DLDataConverter(QObject *parent) :
    QObject(parent)
{
    //import时使用Singleton.DataControler
    qmlRegisterSingletonType<DLDataConverter>("Singleton.DLDataConverter", 1, 0, "DLDataConverter", dataObj);

    initURLServer();
    initConnection();
}

DLDataConverter * DLDataConverter::dlDataConverter = NULL;
DLDataConverter * DLDataConverter::getInstance()
{
    if (dlDataConverter == NULL)
        dlDataConverter = new DLDataConverter();
    return dlDataConverter;
}

QObject *DLDataConverter::dataObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return DLDataConverter::getInstance();
}

void DLDataConverter::controlItem(const QString &dtype, const QString &otype, QString URL)
{
    // remove witespace character at start and end
    URL = URL.trimmed();

    if (dtype == "dl_downloaded")
    {
        if (otype == "download_redownload")
            UnifiedInterface::getInstance()->controlDownload(dl_downloaded, download_redownload, URL);
        else if (otype == "download_trash")
            UnifiedInterface::getInstance()->controlDownload(dl_downloaded, download_trash, URL);
        else if (otype == "download_delete")
            UnifiedInterface::getInstance()->controlDownload(dl_downloaded, download_delete, URL);
        else if (otype == "download_openFolder")
            UnifiedInterface::getInstance()->controlDownload(dl_downloaded, download_openFolder, URL);
    }
    else if (dtype == "dl_downloading")
    {
        if (otype == "download_suspend")
            UnifiedInterface::getInstance()->controlDownload(dl_downloading, download_suspend, URL);
        else if (otype == "download_resume")
            UnifiedInterface::getInstance()->controlDownload(dl_downloading, download_resume, URL);
        else if (otype == "download_priority")
            UnifiedInterface::getInstance()->controlDownload(dl_downloading, download_priority, URL);
        else if (otype == "download_trash")
            UnifiedInterface::getInstance()->controlDownload(dl_downloading, download_trash, URL);
        else if (otype == "download_delete")
            UnifiedInterface::getInstance()->controlDownload(dl_downloading, download_delete, URL);
        else if (otype == "download_openFolder")
            UnifiedInterface::getInstance()->controlDownload(dl_downloading, download_openFolder, URL);
        else if (otype == "download_offlineDownload")
            UnifiedInterface::getInstance()->controlDownload(dl_downloading,download_offlineDownload,URL);
        else if (otype == "download_hightSpeedChannel")
            UnifiedInterface::getInstance()->controlDownload(dl_downloading,download_hightSpeedChannel,URL);
        else if (otype == "download_finishDownload")
            UnifiedInterface::getInstance()->controlDownload(dl_downloading, download_finishDownload, URL);
        emit sDLStateChange(URL, TaskInfo::convertDownStateToInt(otype));
    }
    else if (dtype == "dl_search")
    {
        UnifiedInterface::getInstance()->controlDownload(dl_search,download_redownload,URL);
    }
    else
    {
        if (otype == "download_redownload")
            UnifiedInterface::getInstance()->controlDownload(dl_trash, download_redownload, URL);
        else if (otype == "download_delete")
            UnifiedInterface::getInstance()->controlDownload(dl_trash, download_delete, URL);
    }
}

void DLDataConverter::suspendAllDownloading()
{
    UnifiedInterface::getInstance()->suspendAllDownloading();
}

void DLDataConverter::resumeAllDownloading()
{
    UnifiedInterface::getInstance()->resumeAllDownloading();
}

void DLDataConverter::addTaskItem(TaskInfo *taskInfo)
{
    taskList.append(taskInfo);
    emit taskAdded(taskInfo);
}

void DLDataConverter::slotGetDownloadingInfo(DownloadingItemInfo infoList)
{
    QString tmpURL = infoList.downloadURL;

    for (TaskInfo *i : taskList)
    {
        if (i->rawUrl.compare(infoList.downloadURL))
            continue;

        // 旧数据到新数据的转换(QString -> int)
        int speed = TaskInfo::convertDownloadSpeedToInt(infoList.downloadSpeed);

        // 速度或百分比之一有改变则发送 taskInfoChange 信号
        bool speedChange(false), percentChange(false);

        // 任务的下载速度改变
        if (i->downloadSpeedNow != speed)
        {
            i->downloadSpeedNow = speed;
            speedChange = true;

            i->downloadSpeedChanged();
        }

        if (i->percentage != (float)infoList.downloadPercent)
        {
            i->percentage = infoList.downloadPercent;
            percentChange = true;
        }

        if (speedChange || percentChange)
            emit taskInfoChange(i);
    }

    switch(infoList.downloadState)
    {
    case dlstate_downloading:
        emit sDLStateChange(tmpURL, DLSTATE_DOWNLOADING);
        break;
    case dlstate_ready:
        emit sDLStateChange(tmpURL, DLSTATE_READY);
        break;
    case dlstate_suspend:
        emit sDLStateChange(tmpURL, DLSTATE_SUSPEND);
        break;
    default:
        break;
    }

    if(infoList.thunderHightSpeed == XwarePopulateObject::getInstance()->getDefaultTaskPara())
    {
        infoList.thunderHightSpeed = "";
    }
    emit sThunderHightSpeedChange(tmpURL, infoList.thunderHightSpeed);

    if(infoList.thunderOfflineSpeed == XwarePopulateObject::getInstance()->getDefaultTaskPara())
    {
        infoList.thunderOfflineSpeed = "";
    }
    emit sThunderOfflineSpeedChange(tmpURL, infoList.thunderOfflineSpeed);
}

void DLDataConverter::slotGetContrlFeedback(DownloadType dtype, OperationType otype, QString URL, bool result)
{
    switch(dtype)
    {
    case dl_downloaded:
        switch(otype)
        {
        case download_redownload:
            emit sControlFeedback("dl_downloaded", URL, "download_redownload", result);
            break;
        case download_openFolder:
            emit sControlFeedback("dl_downloaded", URL, "download_openFolder", result);
            break;
        case download_trash:
            emit sControlFeedback("dl_downloaded", URL, "download_trash", result);
            break;
        case download_delete:
            emit sControlFeedback("dl_downloaded", URL, "download_delete", result);
            break;
        default:
            break;
        }
        break;
    case dl_downloading:
        switch(otype)
        {
        case download_suspend:
            emit sControlFeedback("dl_downloading", URL, "download_suspend", result);
            break;
        case download_resume:
            emit sControlFeedback("dl_downloading", URL, "download_resume", result);
            break;
        case download_openFolder:
            emit sControlFeedback("dl_downloading", URL, "download_openFolder", result);
            break;
        case download_trash:
            emit sControlFeedback("dl_downloading", URL, "download_trash", result);
            break;
        case download_delete:
            emit sControlFeedback("dl_downloading", URL, "download_delete", result);
            break;
        default:
            break;
        }
        break;
    case dl_trash:
        switch(otype)
        {
        case download_redownload:
            emit sControlFeedback("dl_trash", URL, "download_redownload", result);
            break;
        case download_delete:
            emit sControlFeedback("dl_trash", URL, "download_delete", result);
            break;
        default:
            break;
        }
        break;
    default:
        qWarning() << "DownloadType not handled in switch. At: void DLDataConverter::slotGetContrlFeedback(DownloadType dtype, OperationType otype, QString URL, bool result)";
    }
}

void DLDataConverter::initURLServer()
{
    URLServer * urlServer = new URLServer();
    connect(urlServer, SIGNAL(newTaskAdded(TaskInfo*)), this, SLOT(addTaskItem(TaskInfo*)));
}

// 临时使用，从列表中找到任务
TaskInfo *DLDataConverter::tmp_searchTaskByUrl(const QString &url)
{
    for (TaskInfo *i : taskList)
        if (!i->rawUrl.compare(url))
            return i;

    return NULL;
}

void DLDataConverter::stopTask(const QString &url)
{
    UnifiedInterface::getInstance()->suspendDownloading(url);

    TaskInfo *task = tmp_searchTaskByUrl(url);
    task->taskState = DLSTATE_SUSPEND;

    emit taskInfoChange(task);
}

void DLDataConverter::startTask(const QString &url)
{
    UnifiedInterface::getInstance()->resumeDownloading(url);

    TaskInfo *task = tmp_searchTaskByUrl(url);
    task->taskState = DLSTATE_DOWNLOADING;

    emit taskInfoChange(task);
}

void DLDataConverter::moveToTrashTask(const QString &url)
{
    UnifiedInterface::getInstance()->trashDownloading(url);

    TaskInfo *task = tmp_searchTaskByUrl(url);
    task->taskState = DLSTATE_TRASH;

    emit taskMoveToTrash(task);
    emit taskInfoChange(task);
}

void DLDataConverter::removeTask(const QString &url)
{
    TaskInfo *task = tmp_searchTaskByUrl(url);
    task->taskState = DLSTATE_REMOVE;

    emit taskDelete(task);
    emit taskInfoChange(task);

    taskList.removeOne(task);
    task->deleteLater();
}

void DLDataConverter::restartTask(const QString &url)
{
    UnifiedInterface::getInstance()->redownloadTrash(url);

    TaskInfo *task = tmp_searchTaskByUrl(url);
    task->taskState = DLSTATE_DOWNLOADING;

    emit taskRestart(task);
    emit taskInfoChange(task);
}

void DLDataConverter::initConnection()
{
    connect(UnifiedInterface::getInstance(), SIGNAL(taskAdded(TaskInfo*)), this, SLOT(addTaskItem(TaskInfo*)));

    connect(UnifiedInterface::getInstance(), SIGNAL(sRealTimeData(DownloadingItemInfo)),
            this, SLOT(slotGetDownloadingInfo(DownloadingItemInfo)));
    connect(UnifiedInterface::getInstance(), SIGNAL(sReturnControlResult(DownloadType,OperationType,QString,bool)),
            this, SLOT(slotGetContrlFeedback(DownloadType,OperationType,QString,bool)));
    //connect(UnifiedInterface::getInstance(), SIGNAL(sRefreshDownloadingItem()),
    //        this, SIGNAL(sRefreshDownloadingItem()));
}

