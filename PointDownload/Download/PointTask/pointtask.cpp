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

#include "pointtask.h"

#include "taskinfo.h"

PointTask::PointTask(QObject *parent) :
    Task(parent)
{
    initConnection();
}

PointTask * PointTask::pointTask = NULL;
PointTask * PointTask::getInstance()
{
    if (pointTask == NULL)
        pointTask = new PointTask();
    return pointTask;
}

void PointTask::start(const TaskInfo & taskInfo)
{
    pointTaskMap.insert(taskInfo.fileID, taskInfo.url);
    switch (getProtocolType(taskInfo.url))
    {
    case PDataType::HTTP:
    case PDataType::HTTPS:
        startHttpDownload(taskInfo);
        break;
    case PDataType::FTP:
        startFtpDownload(taskInfo);
        break;
    case PDataType::Ed2k:
        startEd2kDownload(taskInfo);
        break;
    case PDataType::BitTorrent:
        startBTDownload(taskInfo);
        break;
    default:
        break;
    }
}

void PointTask::stop(const QString & fileID)
{
    switch (getProtocolType(pointTaskMap.value(fileID)))
    {
    case PDataType::HTTP:
    case PDataType::HTTPS:
        stopHttpDownload(fileID);
        break;
    case PDataType::FTP:
        stopFtpDownload(fileID);
        break;
    case PDataType::Ed2k:
        stopEd2kDownload(fileID);
        break;
    case PDataType::BitTorrent:
        stopBTDownload(fileID);
        break;
    default:
        break;
    }
}

void PointTask::suspend(const QString & fileID)
{
    switch (getProtocolType(pointTaskMap.value(fileID)))
    {
    case PDataType::HTTP:
    case PDataType::HTTPS:
        suspendHttpDownload(fileID);
        break;
    case PDataType::FTP:
        suspendFtpDownload(fileID);
        break;
    case PDataType::Ed2k:
        suspendEd2kDownload(fileID);
        break;
    case PDataType::BitTorrent:
        suspendBTDownload(fileID);
        break;
    default:
        break;
    }
}

void PointTask::resume(const QString & fileID)
{
    switch (getProtocolType(pointTaskMap.value(fileID)))
    {
    case PDataType::HTTP:
    case PDataType::HTTPS:
        resumeHttpDownload(fileID);
        break;
    case PDataType::FTP:
        resumeFtpDownload(fileID);
        break;
    case PDataType::Ed2k:
        resumeEd2kDownload(fileID);
        break;
    case PDataType::BitTorrent:
        resumeBTDownload(fileID);
        break;
    default:
        break;
    }
}

void PointTask::finishDownload(const QString & fileID)
{
    pointTaskMap.remove(fileID);

    emit taskFinished(fileID);
}

void PointTask::deleteTask(const QString &fileID)
{
    stop(fileID);
}

void PointTask::trashTask(const QString &fileID)
{
    stop(fileID);
}

void PointTask::initConnection()
{
    //直接连接到MainController
    connect(HttpTask::getInstance(), SIGNAL(taskFinished(QString)),
            MainController::getInstance(), SLOT(slotTaskFinished(QString)));
    connect(HttpTask::getInstance(), SIGNAL(taskItemInfoUpdate(TaskItemInfo)),
            MainController::getInstance(), SLOT(slotTaskItemInfoUpdate(TaskItemInfo)));
    connect(HttpTask::getInstance(), SIGNAL(getError(QString,QString,PDataType::ToolType)),
            MainController::getInstance(), SLOT(slotGetError(QString,QString,PDataType::ToolType)));
}

PDataType::ProtocolType PointTask::getProtocolType(const QString &url)
{
    if (url.startsWith("http://"))
        return PDataType::HTTP;
    else if (url.startsWith("https://"))
        return PDataType::HTTPS;
    else if (url.startsWith("ftp://"))
        return PDataType::FTP;
    else if (url.endsWith(".torrent"))//url is file path
        return PDataType::BitTorrent;
    else if (url.endsWith(".meta4"))//url is file path
        return PDataType::Metalink;
    else if (url.startsWith("magnet:?xt"))
        return PDataType::Magnet;
    else if (url.startsWith("ed2k://"))
        return PDataType::Ed2k;
}

void PointTask::startHttpDownload(const TaskInfo & taskInfo)
{
    HttpTask::getInstance()->startDownload(taskInfo);
}

void PointTask::stopHttpDownload(const QString & fileID)
{
    HttpTask::getInstance()->stopDownload(fileID);
}

void PointTask::suspendHttpDownload(const QString & fileID)
{
    HttpTask::getInstance()->suspendDownloading(fileID);
}

void PointTask::resumeHttpDownload(const QString & fileID)
{
    HttpTask::getInstance()->resumeDownloading(fileID);
}

void PointTask::startFtpDownload(const TaskInfo & taskInfo)
{
    Q_UNUSED(taskInfo);
}

void PointTask::stopFtpDownload(const QString & fileID)
{
    Q_UNUSED(fileID);
}

void PointTask::suspendFtpDownload(const QString & fileID)
{
    Q_UNUSED(fileID);
}

void PointTask::resumeFtpDownload(const QString & fileID)
{
    Q_UNUSED(fileID);
}

void PointTask::startEd2kDownload(const TaskInfo &taskInfo)
{
    Q_UNUSED(taskInfo);
}

void PointTask::stopEd2kDownload(const QString & fileID)
{
    Q_UNUSED(fileID);
}

void PointTask::suspendEd2kDownload(const QString & fileID)
{
    Q_UNUSED(fileID);
}

void PointTask::resumeEd2kDownload(const QString & fileID)
{
    Q_UNUSED(fileID);
}

void PointTask::startBTDownload(const TaskInfo &taskInfo)
{
    Q_UNUSED(taskInfo);
}

void PointTask::stopBTDownload(const QString & fileID)
{
    Q_UNUSED(fileID);
}

void PointTask::suspendBTDownload(const QString & fileID)
{
    Q_UNUSED(fileID);
}

void PointTask::resumeBTDownload(const QString & fileID)
{
    Q_UNUSED(fileID);
}












