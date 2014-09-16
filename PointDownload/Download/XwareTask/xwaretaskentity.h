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
#include "XMLHandler/downloadxmlhandler.h"
#include "xwaretask.h"

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
    void updateTaskMap();
    void taskCompletedMonitor();
    void loginResultHandle(XwareLoginResultType result);
    void updateMagnetMap();  // update globle magnet map

private:
    explicit XwareTaskEntity(QObject *parent = 0);

     // param =>toBigUnit: (1)true: B -> KB/MB/GB,input size shuld be without unit. (2)false: KB/MB/GB -> B(without unit)
    QString convertFileSize(QString size, bool toBigUnit);

    // convert the xware state to local state
    XwareTaskState convertXwareState(QString stateText);

    void clearTaskMap(QMap<QString, XwareTaskInfo*> * taskInfoMap); // free all items of task map to prevent memory leaks
    void constructAndEmitRealTimeData(XwareTaskInfo *taskInfo);
    void updateXMLFile(DownloadingItemInfo info);


private:
    static XwareTaskEntity * xwareTaskEntityInstance;
    QString spliterBtwData;
    QString spliterEnd;
    QString defaultPara;

    // task Info Map
    QMutex * taskInfoMapLocker;
    QMap<QString, XwareTaskInfo*> * taskInfoMap;

    bool isUpdateXML;   // it is time for update xml
    short updateXMLCounter;   // used to compare with UPDATE_XML_INTERVAL
    QTimer* updateTaskTimer;
    int completedNum = 0;
    QList<QVariant> completedTaskList;
    QTimer* taskCompleteMonitorTimer;

    // magnet task map
    QMap<QString, QString> * magnetMap;   // <QString, QString>: <magnetName, url>
    QTimer* updateMagnetMapTimer;
    QMutex * magnetMapLocker;
};

#endif // XWARETASKENTITY_H
