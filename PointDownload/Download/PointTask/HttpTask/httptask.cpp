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

#include "httptask.h"

#include "../Common/taskinfo.h"

HttpTask::HttpTask(QObject *parent) :
    QObject(parent)
{
}

HttpTask * HttpTask::httpTask = NULL;
HttpTask * HttpTask::getInstance()
{
    if (httpTask == NULL)
        httpTask = new HttpTask();
    return httpTask;
}

void HttpTask::startDownload(const TaskInfo & taskInfo)
{
    HttpThreadManager * tmpManager = new HttpThreadManager(taskInfo);
    connect(tmpManager, SIGNAL(sDownloadFinish(QString)), this, SLOT(slotDownloadFinish(QString)));
    connect(tmpManager, SIGNAL(sRealTimeData(DownloadingItemInfo)),
           this, SIGNAL(sRealTimeData(DownloadingItemInfo)));
    tmpManager->startDownload();
    managerMap.insert(taskInfo.rawUrl.toString(), tmpManager);
}

void HttpTask::stopDownload(QString URL)
{
    if (managerMap.value(URL) != NULL)
    {
        managerMap.value(URL)->stopDownload();
        managerMap.value(URL)->deleteLater();
        managerMap.remove(URL);
    }
}

void HttpTask::suspendDownloading(QString URL)
{
    stopDownload(URL);
}

void HttpTask::resumeDownloading(QString URL)
{
    //加了注释后出现以下警告
    //QObject::connect: Incompatible sender/receiver arguments
    //QNetworkSessionPrivateImpl::stateChanged(QNetworkSession::State) --> QNetworkSession::stateChanged(QNetworkSession::State)
    if (!managerMap.contains(URL))
    {
        HttpThreadManager * tmpManager = new HttpThreadManager(URL);
        connect(tmpManager, SIGNAL(sDownloadFinish(QString)), this, SLOT(slotDownloadFinish(QString)));
        connect(tmpManager, SIGNAL(sRealTimeData(DownloadingItemInfo)),
               this, SIGNAL(sRealTimeData(DownloadingItemInfo)));
        tmpManager->startDownload();
        managerMap.insert(URL, tmpManager);
    }
}


void HttpTask::slotDownloadFinish(QString URL)
{
    emit sDownloadFinish(URL);

    managerMap.value(URL)->deleteLater();
    managerMap.remove(URL);
}
