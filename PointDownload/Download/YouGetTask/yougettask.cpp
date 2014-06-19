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

#include "yougettask.h"

YouGetTask::YouGetTask(QObject *parent) :
    QObject(parent)
{
}


YouGetTask * YouGetTask::youGetTask = NULL;
YouGetTask * YouGetTask::getInstance()
{
    if (youGetTask == NULL)
    {
        youGetTask = new YouGetTask();
    }
    return youGetTask;
}

void YouGetTask::startDownload(PrepareDownloadInfo info)
{
    YouGetProcess * yougetProcess = new YouGetProcess(info);
    connect(yougetProcess, SIGNAL(updateData(DownloadingItemInfo)), this ,SIGNAL(sRealTimeData(DownloadingItemInfo)));
    connect(yougetProcess, SIGNAL(yougetError(QString,QString,DownloadToolsType))
            ,this ,SIGNAL(sYouGetError(QString,QString,DownloadToolsType)));
    connect(yougetProcess, SIGNAL(sFinishYouGetDownload(QString)),
            this, SLOT(slotFinishDownload(QString)));

    yougetProcess->startDownload();

    //保存下载列表
    gProcessMap.insert(info.downloadURL, yougetProcess);
}

void YouGetTask::stopDownload(QString URL)
{
    gProcessMap.value(URL)->stopDownload();
}

void YouGetTask::suspendDownloading(QString URL)
{
    gProcessMap.value(URL)->stopDownload();
}

void YouGetTask::resumeDownloading(QString URL)
{
    gProcessMap.value(URL)->startDownload();
}

void YouGetTask::slotFinishDownload(QString URL)
{
    gProcessMap.remove(URL);

    emit sFinishYouGetDownload(URL);
}

