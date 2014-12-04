#include "dldataconverter.h"
#include <QtQml>

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
        emit sDLStateChange(URL, otype);
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

void DLDataConverter::addDownloadingItem(const TaskInfo &taskInfo)
{
    emit taskAdded(taskInfo.getInfoToString());
}

void DLDataConverter::addDownloadedItem(const TaskInfo &taskInfo)
{
    emit downloadedAdded(taskInfo.getDownloadedInfoToString());
}

void DLDataConverter::addDownloadTrashItem(const TaskInfo &taskInfo)
{
    // 由于trash的string结构和downloaded的string(?:?)结构一样，所以使用了dowbloaded的信息来代替，以后这种信息结构将废弃
    emit trashAdded(taskInfo.getDownloadedInfoToString());
}

void DLDataConverter::slotGetDownloadingInfo(DownloadingItemInfo infoList)
{
    QString tmpURL = infoList.downloadURL;

    emit sDLSpeedChange(tmpURL, infoList.downloadSpeed);
    emit sDLProgressChange(tmpURL, infoList.downloadPercent);

    switch(infoList.downloadState)
    {
    case dlstate_downloading:
        emit sDLStateChange(tmpURL, "dlstate_downloading");
        break;
    case dlstate_ready:;
        emit sDLStateChange(tmpURL, "dlstate_ready");
        break;
    case dlstate_suspend:
        emit sDLStateChange(tmpURL, "dlstate_suspend");
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
    connect(urlServer, SIGNAL(newTaskAdded(TaskInfo)), this, SLOT(addDownloadingItem(TaskInfo)));
}

void DLDataConverter::initConnection()
{
    connect(UnifiedInterface::getInstance(), SIGNAL(sAddDownloadedItem(TaskInfo)), this, SLOT(addDownloadedItem(TaskInfo)));
    connect(UnifiedInterface::getInstance(), SIGNAL(sAddDownloadingItem(TaskInfo)), this,SLOT(addDownloadingItem(TaskInfo)));
    connect(UnifiedInterface::getInstance(), SIGNAL(sAddDownloadTrashItem(TaskInfo)),this, SLOT(addDownloadTrashItem(TaskInfo)));

    connect(UnifiedInterface::getInstance(), SIGNAL(sRealTimeData(DownloadingItemInfo)),
            this, SLOT(slotGetDownloadingInfo(DownloadingItemInfo)));
    connect(UnifiedInterface::getInstance(), SIGNAL(sReturnControlResult(DownloadType,OperationType,QString,bool)),
            this, SLOT(slotGetContrlFeedback(DownloadType,OperationType,QString,bool)));
    //connect(UnifiedInterface::getInstance(), SIGNAL(sRefreshDownloadingItem()),
    //        this, SIGNAL(sRefreshDownloadingItem()));
}

