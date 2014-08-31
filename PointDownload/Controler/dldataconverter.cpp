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


void DLDataConverter::controlItem(QString dtype, QString otype, QString URL)
{
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


void DLDataConverter::addDownloadingItem(QString infoList)
{
    emit sFileInfoChange("dl_downloading",infoList);
}

void DLDataConverter::addDownloadedItem(QString infoList)
{
    emit sFileInfoChange("dl_downloaded",infoList);
}

void DLDataConverter::addDownloadTrashItem(QString infoList)
{
    emit sFileInfoChange("dl_trash",infoList);
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

    if((infoList.thunderHightSpeed != "")
            && (infoList.thunderHightSpeed != XwarePopulateObject::getInstance()->getDefaultTaskPara()))
    {
        emit sThunderHightSpeedChange(tmpURL, infoList.thunderHightSpeed);
    }

    if((infoList.thunderOfflineSpeed != "")
            && (infoList.thunderOfflineSpeed != XwarePopulateObject::getInstance()->getDefaultTaskPara()))
    {
        emit sThunderOfflineSpeedChange(tmpURL, infoList.thunderOfflineSpeed);
    }
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
    }
}

void DLDataConverter::initURLServer()
{
    URLServer * urlServer = new URLServer();
    connect(urlServer, SIGNAL(getNewURL(QString)), this, SLOT(addDownloadingItem(QString)));
    urlServer->runServer();

}


void DLDataConverter::initConnection()
{
    connect(UnifiedInterface::getInstance(), SIGNAL(sAddDownloadedItem(QString)), this, SLOT(addDownloadedItem(QString)));
    connect(UnifiedInterface::getInstance(),SIGNAL(sAddDownloadingItem(QString)), this,SLOT(addDownloadingItem(QString)));
    connect(UnifiedInterface::getInstance(),SIGNAL(sAddDownloadTrashItem(QString)),this, SLOT(addDownloadTrashItem(QString)));

    connect(UnifiedInterface::getInstance(), SIGNAL(sRealTimeData(DownloadingItemInfo)),
            this, SLOT(slotGetDownloadingInfo(DownloadingItemInfo)));
    connect(UnifiedInterface::getInstance(), SIGNAL(sReturnControlResult(DownloadType,OperationType,QString,bool)),
            this, SLOT(slotGetContrlFeedback(DownloadType,OperationType,QString,bool)));
    connect(UnifiedInterface::getInstance(), SIGNAL(sRefreshDownloadingItem()),
            this, SIGNAL(sRefreshDownloadingItem()));
}

