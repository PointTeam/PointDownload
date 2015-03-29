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

#ifndef YOUGETPROCESS_H
#define YOUGETPROCESS_H

#include <QObject>
#include <QProcess>
#include <QTimer>
#include <QDebug>
#include "pdatatype.h"
#include "downloadxmlhandler.h"
#include "settingxmlhandler.h"

#include "taskinfo.h"

const int UPDATE_INTERVAL = 1000;

class YouGetProcess : public QObject
{
    Q_OBJECT
public:
    const int UPDATE_XML_INTERVAL = 3;//second
    explicit YouGetProcess(const TaskInfo & taskInfo, QObject *parent = 0);

    void startDownload();
    void stopDownload();
signals:
    void updateData(TaskItemInfo info);
    void yougetError(QString fileID, QString message, PDataType::ToolType toolType);
    void finishYouGetDownload(QString fileID);

private slots:
    void yougetStarted();
    void getFeedBack();
    void getTimerUpdate();
    void updateXMLFile(TaskItemInfo info);
    void getError();
    void yougetProcessFinish(int ret);

private:
    QString gFeedBackInfo;
    TaskInfo taskInfo;
    QProcess * tmpProcess;
    QString lastDataSize;
    QTimer * updateTimer;
    short xmlUpdateInterval;
};

#endif // YOUGETPROCESS_H
