/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Match <2696627729@qq.com>
* Maintainer: Match <2696627729@qq.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

#include "downloaddatasender.h"
#include <QtQml>

DownloadDataSender::DownloadDataSender(QObject *parent) :
    QObject(parent)
{
    //import时使用Singleton.DataControler
    qmlRegisterSingletonType<DownloadDataSender>("Singleton.DownloadDataSender", 1, 0, "DownloadDataSender", dataObj);

    initURLServer();
    initConnection();

    isAllSuspend = false;
}

DownloadDataSender * DownloadDataSender::downloadDataSender = NULL;
DownloadDataSender * DownloadDataSender::getInstance()
{
    if (downloadDataSender == NULL)
    {
        downloadDataSender  = new DownloadDataSender();
    }
    return downloadDataSender;
}

void DownloadDataSender::controlItem(QString dtype, QString otype, QString URL)
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

void DownloadDataSender::suspendAllDownloading()
{
    UnifiedInterface::getInstance()->suspendAllDownloading();
    isAllSuspend = true;
}

void DownloadDataSender::resumeAllDownloading()
{
    UnifiedInterface::getInstance()->resumeAllDownloading();
    isAllSuspend = false;
}

QString DownloadDataSender::getDownloadType()
{
    return downloadType;
}

QString DownloadDataSender::getDownloadURL()
{
    return downloadURL;
}

QString DownloadDataSender::getFileName()
{
    return fileName;
}

QString DownloadDataSender::getFileInfo()
{
    return fileInfo;
}

QString DownloadDataSender::getBTInfo()
{
    return btInfo;
}

QString DownloadDataSender::getDownloadState()
{
    return downloadState;
}

QString DownloadDataSender::getDownloadSpeed()
{
    return downloadSpeed;
}

QString DownloadDataSender::getThunderOfflineSpeed()
{
    return thunderOfflineSpeed;
}

QString DownloadDataSender::getThunderHightSpeed()
{
    return thunderHightSpeed;
}

double DownloadDataSender::getCompletePercentage()
{
    return completePercentage;
}

QString DownloadDataSender::getContrlResultType()
{
    return contrlResultType;
}

bool DownloadDataSender::getIsAllSuspend()
{
    return isAllSuspend;
}

void DownloadDataSender::setDownloadType(QString type)
{
    downloadType = type;
    emit downloadTypeChange();
}

void DownloadDataSender::setDownloadURL(QString url)
{
    downloadURL = url;
    emit downloadURLChange();
}

void DownloadDataSender::setFileName(QString name)
{
    fileName = name;
    emit fileNameChange();
}

void DownloadDataSender::setFileInfo(QString info)
{
    fileInfo = info;
    emit fileInfoChange();
}

void DownloadDataSender::setBTInfo(QString info)
{
    btInfo = info;
    emit btInfoChange();
}

void DownloadDataSender::setDownloadState(QString state)
{
    downloadState = state;
    emit downloadStateChange();
}

void DownloadDataSender::setDownloadSpeed(QString speed)
{
    downloadSpeed = speed;
    emit downloadSpeedChange();
}

void DownloadDataSender::setThunderOfflineSpeed(QString speed)
{
    thunderOfflineSpeed = speed;

    qDebug()<<"thunderOfflineSpeedChange ============>"<<speed;

    emit thunderOfflineSpeedChange();
}

void DownloadDataSender::setThunderHightSpeed(QString speed)
{
    thunderHightSpeed = speed;

    qDebug()<<"thunderHightSpeedChange ============>"<<speed;

    emit thunderHightSpeedChange();
}

void DownloadDataSender::setCompletePercentage(double perc)
{
    completePercentage = perc;
    emit completePercentageChange();
}

void DownloadDataSender::setContrlResultType(QString type)
{
    contrlResultType = type;
    emit contrlResultTypeChange();
}

void DownloadDataSender::setIsAllSuspend(bool value)
{
    isAllSuspend = value;
    emit isAllSuspendChange();
}

void DownloadDataSender::addDownloadingItem(QString infoList)
{
    setDownloadType("dl_downloading");
    setFileInfo(infoList);
}

void DownloadDataSender::addDownloadedItem(QString infoList)
{
    setDownloadType("dl_downloaded");
    setFileInfo(infoList);
}

void DownloadDataSender::addDownloadTrashItem(QString infoList)
{
    setDownloadType("dl_trash");
    setFileInfo(infoList);
}

void DownloadDataSender::slotGetDownloadingInfo(DownloadingItemInfo infoList)
{
    setDownloadURL(infoList.downloadURL);
    setDownloadSpeed(infoList.downloadSpeed);
    setCompletePercentage(infoList.downloadPercent);

    if((infoList.thunderHightSpeed != "") &&
             (infoList.thunderHightSpeed != XwarePopulateObject::getInstance()->getDefaultTaskPara()))
    {
        setThunderHightSpeed(infoList.thunderHightSpeed);
    }

    if((infoList.thunderOfflineSpeed != "") &&
             (infoList.thunderOfflineSpeed != XwarePopulateObject::getInstance()->getDefaultTaskPara()))
    {
        setThunderHightSpeed(infoList.thunderOfflineSpeed);
    }

    switch(infoList.downloadState)
    {
    case dlstate_downloading:
        setDownloadState("dlstate_downloading");
        break;
    case dlstate_ready:
        setDownloadState("dlstate_ready");
        break;
    case dlstate_suspend:
        setDownloadState("dlstate_suspend");
        break;
    default:
        break;
    }
    setDownloadType("dl_downloading");
}

void DownloadDataSender::slotGetContrlResult(DownloadType dtype, OperationType otype, QString URL, bool result)
{
    switch(dtype)
    {
    case dl_downloaded:
        setDownloadURL(URL);
        setDownloadType("dl_downloaded");
        switch(otype)
        {
        case download_redownload:
            setContrlResultType("download_redownload");
            break;
        case download_openFolder:
            setContrlResultType("download_openFolder");
            break;
        case download_trash:
            setContrlResultType("download_trash");
            break;
        case download_delete:
            setContrlResultType("download_delete");
            break;
        default:
            break;
        }
        break;
    case dl_downloading:
        setDownloadURL(URL);
        setDownloadType("dl_downloading");
        switch(otype)
        {
        case download_suspend:
            setContrlResultType("download_suspend");
            break;
        case download_resume:
            setContrlResultType("download_resume");
            break;
        case download_openFolder:
            setContrlResultType("download_openFolder");
            break;
        case download_trash:
            setContrlResultType("download_trash");
            break;
        case download_delete:
            setContrlResultType("download_delete");
            break;
        default:
            break;
        }
        break;
    case dl_trash:
        setDownloadURL(URL);
        setDownloadType("dl_trash");
        switch(otype)
        {
        case download_redownload:
            setContrlResultType("download_redownload");
            break;
        case download_delete:
            setContrlResultType("download_delete");
            break;
        default:
            break;
        }
        break;
    }
}

void DownloadDataSender::initURLServer()
{
    URLServer * urlServer = new URLServer();
    connect(urlServer, SIGNAL(getNewURL(QString)), this, SLOT(addDownloadingItem(QString)));
    urlServer->runServer();

}

void DownloadDataSender::initConnection()
{
    connect(UnifiedInterface::getInstance(), SIGNAL(sAddDownloadedItem(QString)), this, SLOT(addDownloadedItem(QString)));
    connect(UnifiedInterface::getInstance(),SIGNAL(sAddDownloadingItem(QString)), this,SLOT(addDownloadingItem(QString)));
    connect(UnifiedInterface::getInstance(),SIGNAL(sAddDownloadTrashItem(QString)),this, SLOT(addDownloadTrashItem(QString)));

    connect(UnifiedInterface::getInstance(), SIGNAL(sRealTimeData(DownloadingItemInfo)),
            this, SLOT(slotGetDownloadingInfo(DownloadingItemInfo)));
    connect(UnifiedInterface::getInstance(), SIGNAL(sReturnControlResult(DownloadType,OperationType,QString,bool)),
            this, SLOT(slotGetContrlResult(DownloadType,OperationType,QString,bool)));
    connect(UnifiedInterface::getInstance(), SIGNAL(sRefreshDownloadingItem()),
            this, SIGNAL(sRefreshDownloadingItem()));
}
