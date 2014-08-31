/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Choldrim <choldrim@foxmail.com>
* Maintainer: Choldrim <choldrim@foxmail.com>
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

#ifndef XWARETASK_H
#define XWARETASK_H

#include <QObject>
#include "Download/DataType.h"
#include "Download/unifiedinterface.h"
#include "xwarecontroller.h"
#include "xwarewebcontroller.h"
#include "XMLHandler/settingxmlhandler.h"
#include "xwaretaskentity.h"

class XwareTask : public QObject
{
    Q_OBJECT
public:
    ~XwareTask();
    static XwareTask *getInstance();

    //对正在下载的处理
    void addNewDownload(PrepareDownloadInfo info);
    void addNewBTDownload(PrepareDownloadInfo info);
    void stopDownload(QString URL);
    void suspendDownloading(QString URL);
    void resumeDownloading(QString URL);

    void entryOfflineChannel(QString URL);
    void entryHighSpeedChannel(QString URL);


signals:
    void sRealTimeData(DownloadingItemInfo);
    void sXwareError(QString, QString, DownloadToolsType);
    void sFinishXwareDownload(QString);

public slots:

private slots:
    void updateRealTimeData(DownloadingItemInfo info);

private:
    explicit XwareTask(QObject *parent = 0);

    void updateXMLFile(DownloadingItemInfo info);
    void initConnection();
private:
    static XwareTask *xwareTask;

};

#endif // XWARETASK_H
