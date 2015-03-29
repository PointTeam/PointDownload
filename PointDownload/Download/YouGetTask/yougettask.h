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

#ifndef YOUGETTASK_H
#define YOUGETTASK_H

#include <QObject>
#include <QMap>
#include <QProcess>
#include "yougetprocess.h"
#include "task.h"
#include "pdatatype.h"
#include "Control/maincontroller.h"
#include "downloadxmlhandler.h"

#include "taskinfo.h"

class YouGetTask : public Task
{
    Q_OBJECT
public:
    static YouGetTask * getInstance();

public slots:
    void start(const TaskInfo & taskInfo);
    void stop(const QString & fileID);
    void suspend(const QString & fileID);
    void resume(const QString & fileID);
    void finishDownload(const QString & fileID);

private:
    explicit YouGetTask(QObject *parent = 0);

    TaskInfo getPrepareInfoFromXML(const QString & fileID);
    void initConnection();

private:
    static YouGetTask * youGetTask;
    //FileID,Process
    QMap<QString,YouGetProcess *> gProcessMap;
};

#endif // YOUGETTASK_H
