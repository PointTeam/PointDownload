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

class XwareTaskEntity : public QObject
{
    Q_OBJECT
public:
    static XwareTaskEntity *getInstance();

    QString getTaskIdByUrl(QString url);

signals:
    void sRealTimeDataChanged(DownloadingItemInfo);

public slots:

private slots:
    void feedbackDownloadList(QString tasksInfo);

private:
    explicit XwareTaskEntity(QObject *parent = 0);
    void insertTask(QStringList taskInfoStr);
    void clearTaskMap(QMap<QString, XwareTaskInfo*> * taskInfoMap); // free all items of task map to prevent memory leaks
    void constructAndEmitRealTimeData(XwareTaskInfo *taskInfo);
    void updateXMLFile(DownloadingItemInfo info);

private:
    static XwareTaskEntity * xwareTaskEntityInstance;
    QString spliterBtwData;
    QString spliterEnd;
    QString defaultPara;
    QMap<QString, XwareTaskInfo*> * taskInfoMap;
    QMutex * taskInfoMapLocker;
    bool isUpdateXML;
    short updateXMLCounter;
};

#endif // XWARETASKENTITY_H
