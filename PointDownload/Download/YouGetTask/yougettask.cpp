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

#include "taskinfo.h"

YouGetTask::YouGetTask(QObject *parent) :
    Task(parent)
{
    initConnection();
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

void YouGetTask::start(const TaskInfo & taskInfo)
{
    YouGetProcess * yougetProcess = new YouGetProcess(taskInfo);
    connect(yougetProcess, SIGNAL(updateData(TaskItemInfo)), this ,SIGNAL(taskItemInfoUpdate(TaskItemInfo)));
    connect(yougetProcess, SIGNAL(yougetError(QString,QString,PDataType::ToolType))
            ,this ,SIGNAL(getError(QString,QString,PDataType::ToolType)));
    connect(yougetProcess, SIGNAL(finishYouGetDownload(QString)),
            this, SLOT(finishDownload(QString)));

    yougetProcess->startDownload();

    //保存下载列表
    gProcessMap.insert(taskInfo.fileID, yougetProcess);
}

void YouGetTask::stop(const QString & fileID)
{
    if (gProcessMap.value(fileID) == NULL)
        return;
    gProcessMap.value(fileID)->stopDownload();
}

void YouGetTask::suspend(const QString & fileID)
{
    if (gProcessMap.value(fileID) == NULL)
        return;
    gProcessMap.value(fileID)->stopDownload();
}

void YouGetTask::resume(const QString & fileID)
{
    if (gProcessMap.value(fileID) == NULL)
    {
        start(getPrepareInfoFromXML(fileID));
    }
    else
        gProcessMap.value(fileID)->startDownload();
}

void YouGetTask::finishDownload(const QString & fileID)
{
    gProcessMap.remove(fileID);

    emit taskFinished(fileID);
}

void YouGetTask::deleteTask(const QString &fileID)
{
    if (gProcessMap.value(fileID) == NULL)
        return;
    gProcessMap.value(fileID)->deleteLater();
    gProcessMap.remove(fileID);
}

void YouGetTask::trashTask(const QString &fileID)
{
    if (gProcessMap.value(fileID) == NULL)
        return;
    gProcessMap.value(fileID)->deleteLater();
    gProcessMap.remove(fileID);
}

TaskInfo YouGetTask::getPrepareInfoFromXML(const QString & fileID)
{
    DownloadXMLHandler xmlOpera;
    SDownloading ingNode = xmlOpera.getDLingNode(fileID);

    TaskInfo taskInfo;
    TaskFileInfo fileItem;

    taskInfo.fileID = ingNode.fileID;
    taskInfo.url = ingNode.url;
    taskInfo.maxSpeed = 0;
    taskInfo.fileSavePath = ingNode.fileSavePath;
    taskInfo.maxThreads = ingNode.threadList.size();
    taskInfo.toolType = PDataType::PToolTypeYouGet;

    fileItem.fileName = ingNode.fileName;
    fileItem.fileSize = ingNode.fileTotalSize;
    taskInfo.fileList.append(fileItem);

    return taskInfo;
}

void YouGetTask::initConnection()
{
    connect(this, SIGNAL(taskItemInfoUpdate(TaskItemInfo)),
            MainController::getInstance(), SLOT(slotTaskItemInfoUpdate(TaskItemInfo)));
    connect(this, SIGNAL(taskFinished(QString)),
            MainController::getInstance(), SLOT(slotTaskFinished(QString)));
    connect(this, SIGNAL(getError(QString,QString,PDataType::ToolType)),
            MainController::getInstance(), SLOT(slotGetError(QString,QString,PDataType::ToolType)));
}
