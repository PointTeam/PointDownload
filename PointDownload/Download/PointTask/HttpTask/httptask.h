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

#ifndef HTTPTASK_H
#define HTTPTASK_H

#include <QObject>
#include <QMap>
#include "Download/DataType.h"
#include "XMLHandler/xmloperations.h"
#include "httpthreadmanager.h"

class HttpTask : public QObject
{
    Q_OBJECT
public:
    static HttpTask * getInstance();

    //对正在下载的处理
    void startDownload(PrepareDownloadInfo info);
    void stopDownload(QString URL);
    void suspendDownloading(QString URL);
    void resumeDownloading(QString URL);
signals:
    void sRealTimeData(DownloadingItemInfo info);
    void sHttpError(QString URL,QString err, DownloadToolsType toolType);
    void sDownloadFinish(QString URL);

public slots:
    void slotDownloadFinish(QString URL);

private:
    explicit HttpTask(QObject *parent = 0);

private:
    static HttpTask * httpTask;
    //URL,HttpThreadManager
    QMap<QString,HttpThreadManager *> managerMap;

};

#endif // HTTPTASK_H
