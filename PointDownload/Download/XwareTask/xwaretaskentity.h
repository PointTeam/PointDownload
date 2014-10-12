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

#ifndef XWARETASKENTITY_H
#define XWARETASKENTITY_H

#include <QObject>

#include "XwareDataType.h"
#include "xwarepopulateobject.h"
#include "downloadxmlhandler.h"
#include "xwaretask.h"

// 此类主要负责反馈和保存下载中任务的信息
class XwareTaskEntity : public QObject
{
    Q_OBJECT
public:
    static XwareTaskEntity *getInstance();

    QString getTaskIdByUrl(QString url);


signals:
    void sRealTimeDataChanged(DownloadingItemInfo);
    void sFinishDownload(QString URL);

public slots:
    void startFeedbackTaskInfo();
    void stopFeedbackTaskInfo();

private slots:
    // handle login result
    void loginResultHandle(XwareLoginResultType result);

    // get task info from local json, and populate the XwareTaskInfo struct into the global taskInfoMap
    void updateTaskMap();

    // update globle magnet map
    void updateMagnetMap();

    // finish downloading task
    void hasNewCompletedTaskHandle(QString url);

private:
    explicit XwareTaskEntity(QObject *parent = 0);

     // param =>toBigUnit: (1)true: B -> KB/MB/GB,input size shuld be without unit. (2)false: KB/MB/GB -> B(without unit)
    QString convertFileSize(QString size, bool toBigUnit);

    // convert the xware state to local state
    XwareTaskState convertXwareState(QString stateText);

    // free all items of task map to prevent memory leaks
    void clearTaskMap(QMap<QString, XwareTaskInfo*> * taskInfoMap);

    // change the XwareTaskInfo struct to DownloadingItemInfo struct, and emit the task data
    void constructAndEmitRealTimeData(XwareTaskInfo *taskInfo);

    // update xml info
    void updateXMLFile(DownloadingItemInfo info);

private:
    static XwareTaskEntity * xwareTaskEntityInstance;

    // message spliter
    QString spliterBtwData;
    QString spliterEnd;
    QString defaultPara;

    // taskInfoMap sync locker
    QMutex * taskInfoMapLocker;

      // <QString, XwareTaskInfo*> : <task id, task struct>
    QMap<QString, XwareTaskInfo*> * taskInfoMap;

    // is it time for update xml
    bool isUpdateXML;

    // used to compare with UPDATE_XML_INTERVAL
    short updateXMLCounter;
    QTimer* updateTaskTimer;

    // magnet task map
    QMap<QString, QString> * magnetMap;   // <QString, QString>: <magnetName, url>
    QTimer* updateMagnetMapTimer;
    QMutex * magnetMapLocker;
};

#endif // XWARETASKENTITY_H
