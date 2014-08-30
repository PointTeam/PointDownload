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

#ifndef POINTTASK_H
#define POINTTASK_H

#include <QObject>
#include <QMap>
#include "Download/DataType.h"
#include "Download/unifiedinterface.h"
#include "HttpTask/httptask.h"

class PointTask : public QObject
{
    Q_OBJECT
public:
    static PointTask * getInstance();

    //对正在下载的处理
    void startDownload(PrepareDownloadInfo info);
    void stopDownload(QString URL);
    void suspendDownloading(QString URL);
    void resumeDownloading(QString URL);


signals:
    void sRealTimeData(DownloadingItemInfo info);
    void sPointError(QString URL,QString err, DownloadToolsType toolType);
    void sFinishPointDownload(QString URL);

public slots:
    void slotFinishDownload(QString URL);

private:
    explicit PointTask(QObject *parent = 0);

    void initConnection();

    ProtocalType getProtocalTypeFromURL(QString URL);

    //对http,https的下载处理
    void startHttpDownload(PrepareDownloadInfo info);
    void stopHttpDownload(QString URL);
    void suspendHttpDownload(QString URL);
    void resumeHttpDownload(QString URL);

    //对ftp的下载处理
    void startFtpDownload(PrepareDownloadInfo info);
    void stopFtpDownload(QString URL);
    void suspendFtpDownload(QString URL);
    void resumeFtpDownload(QString URL);

    //对ed2k的下载处理
    void startEd2kDownload(PrepareDownloadInfo info);
    void stopEd2kDownload(QString URL);
    void suspendEd2kDownload(QString URL);
    void resumeEd2kDownload(QString URL);

    //对bt的下载处理
    void startBTDownload(PrepareDownloadInfo info);
    void stopBTDownload(QString URL);
    void suspendBTDownload(QString URL);
    void resumeBTDownload(QString URL);

private:
    static PointTask * pointTask;

    //URL,protocalType,不同的协议使用不同的类处理
    QMap<QString,ProtocalType> pointTaskMap;
};

#endif // POINTTASK_H
