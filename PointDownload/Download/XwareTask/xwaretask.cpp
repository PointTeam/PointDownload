/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Choldrim <choldrim@foxmail.com>
* Maintainer: Choldrim <choldrim@foxmail.com>
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

#include "xwaretask.h"

#define UPDATE_XML_INTERVAL 0

XwareTask::XwareTask(QObject *parent) :
    QObject(parent)
{
    //match add,2014.8.30
    initConnection();
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
    // clear the completed task
    CompletedListWebView::getInstance()->clearAllCompletedTask(false);

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
    if(XwareWebController::getInstance()->getLoginState() != XwareWebController::Logined)return;
    QString tid = XwareTaskEntity::getInstance()->getTaskIdByUrl(URL);
    if(tid == "-1")
    {
        // error
        NormalNotice::getInstance()->showMessage(tr("Task Miss"), Notice_Color_Error, tr("Task can not be found, Please try to add the task again"));
        return;
    }

    XwarePopulateObject::getInstance()->suspendDownloadingTask(tid);
}

void XwareTask::resumeDownloading(QString URL)
{
    if(XwareWebController::getInstance()->getLoginState() != XwareWebController::Logined)return;
    QString tid = XwareTaskEntity::getInstance()->getTaskIdByUrl(URL);
    if(tid == "-1")
    {
        // error
        NormalNotice::getInstance()->showMessage(tr("Task Miss"), Notice_Color_Error, tr("Task can not be found, Please try to add the task again"));
        return;
    }

    XwarePopulateObject::getInstance()->resumeDownloadingTask(tid);
}

void XwareTask::removeDownloading(QString URL)
{
    if(XwareWebController::getInstance()->getLoginState() != XwareWebController::Logined)return;
    QString tid = XwareTaskEntity::getInstance()->getTaskIdByUrl(URL);
    if(tid == "-1")
    {
        // error
        NormalNotice::getInstance()->showMessage(tr("Task Miss"), Notice_Color_Error, tr("Task can not be found, Please try to add the task again"));
        return;
    }

    XwarePopulateObject::getInstance()->removeDownloadingTask(tid);
}

void XwareTask::entryOfflineChannel(QString URL)
{
    if(XwareWebController::getInstance()->getLoginState() != XwareWebController::Logined)return;
    QString tid = XwareTaskEntity::getInstance()->getTaskIdByUrl(URL);
    if(tid == "-1")
    {
        // error
        NormalNotice::getInstance()->showMessage(tr("Task Miss"), Notice_Color_Error, tr("Task can not be found, Please try to add the task again"));
        return;
    }

    XwarePopulateObject::getInstance()->entryOfflineChannel(tid);
}

void XwareTask::entryHighSpeedChannel(QString URL)
{
    if(XwareWebController::getInstance()->getLoginState() != XwareWebController::Logined)return;
    QString tid = XwareTaskEntity::getInstance()->getTaskIdByUrl(URL);
    if(tid == "-1")
    {
        // error
        NormalNotice::getInstance()->showMessage(tr("Task Miss"), Notice_Color_Error, tr("Task can not be found, Please try to add the task again"));
        return;
    }

    XwarePopulateObject::getInstance()->entryHighSpeedChannel(tid);
}

void XwareTask::slotFinishDownload(QString URL)
{
    UnifiedInterface::getInstance()->cleanDownloadFinishItem(URL);
}

void XwareTask::updateRealTimeData(DownloadingItemInfo info)
{
    emit sRealTimeData(info);
}

void XwareTask::initConnection()
{
    // UnifiedInterface
    connect(this, SIGNAL(sRealTimeData(DownloadingItemInfo)),
            UnifiedInterface::getInstance(), SIGNAL(sRealTimeData(DownloadingItemInfo)));
    connect(this, SIGNAL(sXwareError(QString,QString,DownloadToolsType)),
            UnifiedInterface::getInstance(), SLOT(downloadGetError(QString,QString,DownloadToolsType)));
    connect(this, SIGNAL(sFinishXwareDownload(QString)),
            UnifiedInterface::getInstance(), SLOT(downloadFinish(QString)));

    // Real Time Data update
    connect(XwareTaskEntity::getInstance(), SIGNAL(sRealTimeDataChanged(DownloadingItemInfo)),
            this, SLOT(updateRealTimeData(DownloadingItemInfo)));

    // finish download
    connect(XwareTaskEntity::getInstance(), SIGNAL(sFinishDownload(QString)),
            this, SLOT(slotFinishDownload(QString)));
}
