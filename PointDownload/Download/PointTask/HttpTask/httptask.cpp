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

#include "taskinfo.h"

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
    connect(tmpManager, SIGNAL(taskFinished(QString)), this, SLOT(slotDownloadFinish(QString)));
    connect(tmpManager, SIGNAL(taskItemInfoUpdate(TaskItemInfo)),
           this, SIGNAL(taskItemInfoUpdate(TaskItemInfo)));
    tmpManager->startDownload();
    managerMap.insert(taskInfo.fileID, tmpManager);
}

void HttpTask::stopDownload(const QString &taskID)
{
    if (managerMap.value(taskID) != NULL)
    {
        managerMap.value(taskID)->stopDownload();
        managerMap.value(taskID)->deleteLater();
        managerMap.remove(taskID);
    }
}

void HttpTask::suspendDownloading(const QString &taskID)
{
    stopDownload(taskID);
}

void HttpTask::resumeDownloading(const QString &taskID)
{
    //加了注释后出现以下警告
    //QObject::connect: Incompatible sender/receiver arguments
    //QNetworkSessionPrivateImpl::stateChanged(QNetworkSession::State) --> QNetworkSession::stateChanged(QNetworkSession::State)
    if (!managerMap.contains(taskID))
    {
        HttpThreadManager * tmpManager = new HttpThreadManager(taskID);
        connect(tmpManager, SIGNAL(taskFinished(QString)), this, SLOT(slotDownloadFinish(QString)));
        connect(tmpManager, SIGNAL(taskItemInfoUpdate(TaskItemInfo)),
               this, SIGNAL(taskItemInfoUpdate(TaskItemInfo)));
        tmpManager->startDownload();
        managerMap.insert(taskID, tmpManager);
    }
}


void HttpTask::slotDownloadFinish(const QString & taskID)
{
    emit taskFinished(taskID);

    managerMap.value(taskID)->deleteLater();
    managerMap.remove(taskID);
}
