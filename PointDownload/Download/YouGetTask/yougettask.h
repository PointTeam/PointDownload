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

#ifndef YOUGETTASK_H
#define YOUGETTASK_H

#include <QObject>
#include <QMap>
#include <QProcess>
#include "yougetprocess.h"
#include "Download/DataType.h"
#include "Download/unifiedinterface.h"
#include "downloadxmlhandler.h"

#include "taskinfo.h"

class YouGetTask : public QObject
{
    Q_OBJECT
public:
    static YouGetTask * getInstance();

    //对正在下载的处理
    void startDownload(const TaskInfo & taskInfo);
    void stopDownload(QString URL);
    void suspendDownloading(QString URL);
    void resumeDownloading(QString URL);

signals:
    void sRealTimeData(DownloadingItemInfo info);
    void sYouGetError(QString URL,QString err, int toolType);

public slots:
    void slotFinishDownload(QString URL);

private:
    explicit YouGetTask(QObject *parent = 0);

    TaskInfo getPrepareInfoFromXML(QString URL);
    void initConnection();
private:
    static YouGetTask * youGetTask;
    //URL,Process
    QMap<QString,YouGetProcess *> gProcessMap;
};

#endif // YOUGETTASK_H
