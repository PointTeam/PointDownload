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

#include "../Common/taskinfo.h"

PointTask::PointTask(QObject *parent) :
    QObject(parent)
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

void PointTask::startDownload(const TaskInfo & taskInfo)
{
    pointTaskMap.insert(taskInfo.rawUrl.toString() ,getProtocalTypeFromURL(taskInfo.rawUrl.toString()));
    switch (getProtocalTypeFromURL(taskInfo.rawUrl.toString()))
    {
    case point_http:
        startHttpDownload(taskInfo);
        break;
    case point_ftp:
        startFtpDownload(taskInfo);
        break;
    case point_ed2k:
        startEd2kDownload(taskInfo);
        break;
    case point_bt:
        startBTDownload(taskInfo);
        break;
    default:
        break;
    }
}

void PointTask::stopDownload(QString URL)
{
    switch (getProtocalTypeFromURL(URL))
    {
    case point_http:
        stopHttpDownload(URL);
        break;
    case point_ftp:
        stopFtpDownload(URL);
        break;
    case point_ed2k:
        stopEd2kDownload(URL);
        break;
    case point_bt:
        stopBTDownload(URL);
        break;
    default:
        break;
    }
}

void PointTask::suspendDownloading(QString URL)
{
    switch (getProtocalTypeFromURL(URL))
    {
    case point_http:
        suspendHttpDownload(URL);
        break;
    case point_ftp:
        suspendFtpDownload(URL);
        break;
    case point_ed2k:
        suspendEd2kDownload(URL);
        break;
    case point_bt:
        suspendBTDownload(URL);
        break;
    default:
        break;
    }
}

void PointTask::resumeDownloading(QString URL)
{
    switch (getProtocalTypeFromURL(URL))
    {
    case point_http:
        resumeHttpDownload(URL);
        break;
    case point_ftp:
        resumeFtpDownload(URL);
        break;
    case point_ed2k:
        resumeEd2kDownload(URL);
        break;
    case point_bt:
        resumeBTDownload(URL);
        break;
    default:
        break;
    }
}

void PointTask::slotFinishDownload(QString URL)
{
    pointTaskMap.remove(URL);

    UnifiedInterface::getInstance()->cleanDownloadFinishItem(URL);
}

void PointTask::initConnection()
{
    connect(HttpTask::getInstance(), SIGNAL(sRealTimeData(DownloadingItemInfo)),
            this, SIGNAL(sRealTimeData(DownloadingItemInfo)));
    connect(HttpTask::getInstance(), SIGNAL(sHttpError(QString,QString,int)),
            this, SIGNAL(sPointError(QString,QString,int)));
    //完成下载的信号连接
    connect(HttpTask::getInstance(), SIGNAL(sDownloadFinish(QString)), this, SLOT(slotFinishDownload(QString)));

    connect(this, SIGNAL(sRealTimeData(DownloadingItemInfo)),
            UnifiedInterface::getInstance(), SIGNAL(sRealTimeData(DownloadingItemInfo)));
    connect(this, SIGNAL(sPointError(QString,QString,int)),
            UnifiedInterface::getInstance(), SLOT(downloadGetError(QString,QString,int)));
}

ProtocalType PointTask::getProtocalTypeFromURL(QString URL)
{
    if (URL.contains("http://") || URL.contains("https://"))
        return point_http;
    else if (URL.contains("ftp://"))
        return point_ftp;
    else if (URL.contains("ed2k://"))
        return point_ed2k;
    else if (URL.contains(".torrent"))
        return point_bt;

    // 消除警告
    qWarning() << "没有匹配的格式！  At: ProtocalType PointTask::getProtocalTypeFromURL(QString URL)";
    return point_http;
}

void PointTask::startHttpDownload(const TaskInfo & taskInfo)
{
    HttpTask::getInstance()->startDownload(taskInfo);
}

void PointTask::stopHttpDownload(QString URL)
{
    HttpTask::getInstance()->stopDownload(URL);
}

void PointTask::suspendHttpDownload(QString URL)
{
    HttpTask::getInstance()->suspendDownloading(URL);
}

void PointTask::resumeHttpDownload(QString URL)
{
    HttpTask::getInstance()->resumeDownloading(URL);
}

void PointTask::startFtpDownload(const TaskInfo & taskInfo)
{
    Q_UNUSED(taskInfo);
}

void PointTask::stopFtpDownload(QString URL)
{
    Q_UNUSED(URL);
}

void PointTask::suspendFtpDownload(QString URL)
{
    Q_UNUSED(URL);
}

void PointTask::resumeFtpDownload(QString URL)
{
    Q_UNUSED(URL);
}

void PointTask::startEd2kDownload(const TaskInfo &taskInfo)
{
    Q_UNUSED(taskInfo);
}

void PointTask::stopEd2kDownload(QString URL)
{
    Q_UNUSED(URL);
}

void PointTask::suspendEd2kDownload(QString URL)
{
    Q_UNUSED(URL);
}

void PointTask::resumeEd2kDownload(QString URL)
{
    Q_UNUSED(URL);
}

void PointTask::startBTDownload(const TaskInfo &taskInfo)
{
    Q_UNUSED(taskInfo);
}

void PointTask::stopBTDownload(QString URL)
{
    Q_UNUSED(URL);
}

void PointTask::suspendBTDownload(QString URL)
{
    Q_UNUSED(URL);
}

void PointTask::resumeBTDownload(QString URL)
{
    Q_UNUSED(URL);
}












