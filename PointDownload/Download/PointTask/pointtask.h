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

#ifndef POINTTASK_H
#define POINTTASK_H

#include <QObject>
#include <QMap>
#include "pdatatype.h"
#include "Control/maincontroller.h"
#include "HttpTask/httptask.h"

class PointTask : public Task
{
    Q_OBJECT
public:
    static PointTask * getInstance();

public slots:
    void start(const TaskInfo & taskInfo);
    void stop(const QString & fileID);
    void suspend(const QString & fileID);
    void resume(const QString & fileID);
    void finishDownload(const QString & fileID);
    void deleteTask(const QString & fileID);
    void trashTask(const QString & fileID);

private:
    explicit PointTask(QObject *parent = 0);

    void initConnection();

    PDataType::ProtocolType getProtocolType(const QString &url);

    //对http,https的下载处理
    void startHttpDownload(const TaskInfo &taskInfo);
    void stopHttpDownload(const QString & fileID);
    void suspendHttpDownload(const QString & fileID);
    void resumeHttpDownload(const QString & fileID);

    //对ftp的下载处理
    void startFtpDownload(const TaskInfo &taskInfo);
    void stopFtpDownload(const QString & fileID);
    void suspendFtpDownload(const QString & fileID);
    void resumeFtpDownload(const QString & fileID);

    //对ed2k的下载处理
    void startEd2kDownload(const TaskInfo &taskInfo);
    void stopEd2kDownload(const QString & fileID);
    void suspendEd2kDownload(const QString & fileID);
    void resumeEd2kDownload(const QString & fileID);

    //对bt的下载处理
    void startBTDownload(const TaskInfo &taskInfo);
    void stopBTDownload(const QString & fileID);
    void suspendBTDownload(const QString & fileID);
    void resumeBTDownload(const QString & fileID);

private:
    static PointTask * pointTask;
    DownloadXMLHandler downloadHandler;
    //fileID,url,不同的协议使用不同的类处理
    QMap<QString,QString> pointTaskMap;
};

#endif // POINTTASK_H
