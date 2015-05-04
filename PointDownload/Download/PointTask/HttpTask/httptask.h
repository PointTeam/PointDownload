/***********************************************************************
*PointDownload
*Copyright (C) 2014~2015  PointTeam
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

#ifndef HTTPTASK_H
#define HTTPTASK_H

#include <QObject>
#include <QMap>
#include "pdatatype.h"
#include "httpthreadmanager.h"

class HttpTask : public QObject
{
    Q_OBJECT
public:
    static HttpTask * getInstance();

    //对正在下载的处理
    void startDownload(const TaskInfo &taskInfo);
    void stopDownload(const QString &taskID);
    void suspendDownloading(const QString &taskID);
    void resumeDownloading(const QString &taskID);

signals:
    void taskFinished(const QString & taskID);
    void taskItemInfoUpdate(const TaskItemInfo & info);
    void getError(const QString & fileID, const QString & error, PDataType::ToolType toolType);

private slots:
    void slotDownloadFinish(const QString & taskID);

private:
    explicit HttpTask(QObject *parent = 0);

private:
    static HttpTask * httpTask;
    //fileID,HttpThreadManager
    QMap<QString,HttpThreadManager *> managerMap;

};

#endif // HTTPTASK_H
