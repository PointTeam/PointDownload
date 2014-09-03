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


#include "xwaretaskentity.h"

#define UPDATE_TASK_INTERVAL 1000   // msecond
#define MONITOR_COMPLETED_INTERVAL 1000   // msecond
#define UPDATE_XML_INTERVAL 4   // times

// tmp , just for debug
void debugMap(QMap<QString, XwareTaskInfo *> *taskInfoMap);

XwareTaskEntity * XwareTaskEntity::xwareTaskEntityInstance = NULL;
XwareTaskEntity::XwareTaskEntity(QObject *parent) :
    QObject(parent)
{
    spliterBtwData = XWARE_CONSTANTS_STRUCT.SPLITER_BTWN_DATA;
    spliterEnd =  XWARE_CONSTANTS_STRUCT.SPLITER_END;
    defaultPara = XWARE_CONSTANTS_STRUCT.SPLITER_DEFAULT_PARAM;
    
    taskInfoMap = new QMap<QString, XwareTaskInfo*>();
    taskInfoMapLocker = new QMutex();
    isUpdateXML = false;
    updateXMLCounter = 1;

    // monitor the completed task
    taskCompleteMonitorTimer = new QTimer();
    taskCompleteMonitorTimer->setInterval(MONITOR_COMPLETED_INTERVAL);
    connect(taskCompleteMonitorTimer, SIGNAL(timeout()), this, SLOT(taskCompletedMonitor()));

    // update task info
    updateTaskTimer = new QTimer();
    updateTaskTimer->setInterval(UPDATE_TASK_INTERVAL);
    connect(updateTaskTimer, SIGNAL(timeout()), this, SLOT(updateTaskMap()));
    
    connect(XwareWebController::getInstance(), SIGNAL(sLoginResult(XwareLoginResultType)),
            this, SLOT(loginResultHandle(XwareLoginResultType)));
}

QString XwareTaskEntity::convertFileSize(QString size, bool toBigUnit)
{
    if(toBigUnit)
    {
        bool ok;
        qint64 value = size.toLongLong(&ok);
        if(ok)
        {
            if (value > 1024 * 1024 * 1024)  //GB
                return QString::number(((double)value) / 1024 / 1024 / 1024,'f',1) + "GB";
            else if (value > 1024 * 1024)  //MB
                return QString::number(((double)value) / 1024 / 1024,'f',1) + "MB";
            else if (value > 1024)  //KB
                return QString::number(((double)value)/ 1024,'f',1) + "KB";
            else
                return QString::number(value,'f',1) + "B";
        }
    }
    else
    {
        if(size.contains("G"))
        {
            double num = size.split("G").at(0).toDouble();
            return QString::number((long long)num * 1024 * 1024 * 1024);
        }

        if(size.contains("M"))
        {
            double num = size.split("M").at(0).toDouble();
            return QString::number((long long)num * 1024 * 1024);
        }

        if(size.contains("K"))
        {
            double num = size.split("K").at(0).toDouble();
            return QString::number((long long)num * 1024);
        }

        return QString::number(size.split("B").at(0).toLongLong());
    }

    return "0";
}

XwareTaskState XwareTaskEntity::convertXwareState(QString stateText)
{
    if(stateText == "0")
    {
        return x_dload;
    }

    else if(stateText == "8")
    {
        return x_wait;
    }

    else if(stateText == "10" || stateText == "9")
    {
        return x_pause;
    }

    else
    {
        return x_other;
    }
}

XwareTaskEntity *XwareTaskEntity::getInstance()
{
    if (xwareTaskEntityInstance == NULL)
        xwareTaskEntityInstance = new XwareTaskEntity();
    return xwareTaskEntityInstance;
}

QString XwareTaskEntity::getTaskIdByUrl(QString url)
{
    // lock and prevent the task map from being change.
    taskInfoMapLocker->lock();
    QString tid = "-1";

    QMap<QString, XwareTaskInfo*>::Iterator it;
    for(it = taskInfoMap->begin(); it != taskInfoMap->end(); it++)
    {
        if(it.value()->url == url)
        {
             tid = it.value()->tid;
        }
    }

    taskInfoMapLocker->unlock();
    return tid;
}

void XwareTaskEntity::startFeedbackTaskInfo()
{
    updateTaskTimer->start();
    taskCompleteMonitorTimer->start();
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"start to feedback task info and added a monitor to completed task !";
}

void XwareTaskEntity::stopFeedbackTaskInfo()
{
    updateTaskTimer->stop();
    taskCompleteMonitorTimer->start();
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"stop to feedback task info and remove the monitor to completed task !";
}

void XwareTaskEntity::updateTaskMap()
{
    QUrl url(XWARE_CONSTANTS_STRUCT.URLSTR + "list?v=2&type=0&pos=0&number=99999&needUrl=1");

    QEventLoop loop;
    QNetworkAccessManager manager;

    // request
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    // wait for message
    loop.exec();
    reply->disconnect();

    // 读到的信息
    QString jsonStr = QUrl::fromPercentEncoding(reply->readAll());
    QJsonDocument jsd = QJsonDocument::fromJson(jsonStr.toUtf8());
    QMap<QString, QVariant> jsonMap = jsd.toVariant().toMap();

    delete reply;
    reply = NULL;
    
    
    QList<QVariant> completedTaskList = jsonMap.value("tasks").toList();
    if(completedTaskList.length() == 0)return;

    //update xml file
    if (updateXMLCounter == UPDATE_XML_INTERVAL)
    {
        isUpdateXML = true;
        updateXMLCounter = 1;
    }
    else
    {
        isUpdateXML = false;
        ++updateXMLCounter;
    }

    // lock and prevent the task map from being read.
    taskInfoMapLocker->lock();

    // clear the task map
    clearTaskMap(taskInfoMap);

    for(int i = 0; i < completedTaskList.length(); ++i)
    {
        QString tid = completedTaskList.at(i).toMap().value("id").toString();
        QString name = completedTaskList.at(i).toMap().value("name").toString();
        QString size = completedTaskList.at(i).toMap().value("size").toString();
        QString progress = completedTaskList.at(i).toMap().value("progress").toString();
        progress = QString::number(progress.toDouble() / 100) + "%";
        QString speed = convertFileSize(completedTaskList.at(i).toMap().value("speed").toString(), 1) + "/s";
        QString remainTime = completedTaskList.at(i).toMap().value("remainTime").toString();
        XwareTaskState state = convertXwareState(completedTaskList.at(i).toMap().value("state").toString());
        QString url = completedTaskList.at(i).toMap().value("url").toString();
        QString highChnlSpeed = completedTaskList.at(i).toMap().value("vipChannel").toMap().value("speed").toString();
        QString offlineChnlSpeed = completedTaskList.at(i).toMap().value("lixianChannel").toMap().value("speed").toString();

        XwareTaskInfo* taskInfoStruct = new XwareTaskInfo{tid, name, size, progress, speed, remainTime,
                state, url, highChnlSpeed, offlineChnlSpeed};

        // insert task map
        taskInfoMap->insert(tid, taskInfoStruct);

        constructAndEmitRealTimeData(taskInfoStruct);
    }

    // free the map lock
    taskInfoMapLocker->unlock();

//    debugMap(taskInfoMap);
}


// free all items of task map to prevent memory leaks
void XwareTaskEntity::clearTaskMap(QMap<QString, XwareTaskInfo *> *taskInfoMap)
{
    QMap<QString, XwareTaskInfo*>::Iterator it;
    for(it = taskInfoMap->begin(); it != taskInfoMap->end(); it++)
    {
        XwareTaskInfo* tmp = it.value();
        if(tmp != NULL)
        {
            delete tmp;
            tmp = NULL;
        }
    }
    taskInfoMap->clear();
}


void XwareTaskEntity::constructAndEmitRealTimeData(XwareTaskInfo * taskInfo)
{
    DownloadingItemInfo itemInfo;
    itemInfo.downloadURL = taskInfo->url;
    itemInfo.downloadSpeed = taskInfo->speed;
    itemInfo.uploadSpeed = "0 B/s";
    itemInfo.thunderOfflineSpeed = taskInfo->offlineChnlSpeed;
    itemInfo.thunderHightSpeed = taskInfo->highChnlSpeed;

    if(taskInfo->state == x_dload)
    {
        itemInfo.downloadState = dlstate_downloading;
    }
    else if(taskInfo->state == x_pause)
    {
        itemInfo.downloadState = dlstate_suspend;
    }
    else
    {
        itemInfo.downloadState = dlstate_ready;
    }

    itemInfo.downloadPercent = taskInfo->progress.split("%").at(0).toDouble();

    if(isUpdateXML)
    {
        updateXMLFile(itemInfo);
    }

    // emit signal to xware task
    emit sRealTimeDataChanged(itemInfo);
}

void XwareTaskEntity::taskCompletedMonitor()
{
    QUrl url(XWARE_CONSTANTS_STRUCT.URLSTR + "list?v=2&type=1&pos=0&number=99999&needUrl=1");

    QEventLoop loop;
    QNetworkAccessManager manager;

    // request
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();// wait for message
    reply->disconnect();

    // 读到的信息
    QString jsonStr = QUrl::fromPercentEncoding(reply->readAll());
    QJsonDocument jsd = QJsonDocument::fromJson(jsonStr.toUtf8());
    QMap<QString, QVariant> jsonMap = jsd.toVariant().toMap();

    delete reply;
    reply = NULL;

//    int completedNum = jsonMap.value("completeNum").toString().toInt();
    QList<QVariant> completedTaskListTmp = jsonMap.value("tasks").toList();
    if(completedTaskListTmp.length() == 0)
    {
        return;
    }

    // first time
    if(completedTaskList.length() == 0)
    {
        completedTaskList = completedTaskListTmp;
        return;
    }

    for(int i = 0; i < completedTaskListTmp.length(); ++i )
    {
        bool match = false;
        QString url = completedTaskListTmp.at(i).toMap().value("url").toString();
        for(int j = 0; j < completedTaskList.length(); ++j )
        {
            if(url == completedTaskList.at(j).toMap().value("url"))
            {
                match = true;
            }
        }

        if(!match)
        {
            // MatchFinish
            // **  ** //
            DownloadingItemInfo tmpInfo;
            tmpInfo.downloadURL = url;
            tmpInfo.downloadPercent = 100;
            tmpInfo.downloadSpeed = "0 KB/S";
            tmpInfo.downloadState = dlstate_downloading;
            tmpInfo.thunderHightSpeed = "-";
            tmpInfo.thunderOfflineSpeed = "-";
            tmpInfo.uploadSpeed = "0";

            emit sRealTimeDataChanged(tmpInfo);

            emit sFinishDownload(url);

            // tmp
            qDebug()<<"[xware info] finished dloading: ==> "<<url;
        }

    }

    completedTaskList = completedTaskListTmp;

//    qDebug()<<"completedNum : "<<completedNum;
}

void XwareTaskEntity::loginResultHandle(XwareLoginResultType result)
{
    if(result == x_LoginSuccess)
    {
        startFeedbackTaskInfo();
    }
    else if(result == x_Logout)
    {
        stopFeedbackTaskInfo();
    }
}

void XwareTaskEntity::updateXMLFile(DownloadingItemInfo info)
{
    DownloadXMLHandler tmpOpera;
    SDownloading tmpStruct = tmpOpera.getDownloadingNode(info.downloadURL);
    //计算平均速度，用作优先下载的判断条件
    tmpStruct.averageSpeed = QString::number(qint64((info.downloadPercent / 100 * tmpStruct.totalSize.toDouble()//当前完成大小
                                                    - tmpStruct.readySize.toDouble()//上次完成大小
                                                    ) / UPDATE_XML_INTERVAL));
    tmpStruct.readySize = QString::number(qint64(info.downloadPercent / 100 * tmpStruct.totalSize.toLongLong()));

    tmpOpera.writeDownloadingConfigFile(tmpStruct);
}




// debug , check the task information through Qt console
void debugMap(QMap<QString, XwareTaskInfo*> * taskInfoMap)
{
    // debug
    qDebug()<<"************************************start***************************************************";

    qDebug();
    qDebug()<<"////////////////start//////////////////";
    QMap<QString, XwareTaskInfo*>::Iterator it;
    for(it = taskInfoMap->begin(); it != taskInfoMap->end(); it++)
    {
        qDebug()<<"=========start==============";
        qDebug()<<"tid"<<it.value()->tid;
        qDebug()<<"name"<<it.value()->name;
        qDebug()<<"size"<<it.value()->size;
        qDebug()<<"progress"<<it.value()->progress;
        qDebug()<<"speed"<<it.value()->speed;
        qDebug()<<"remainTime"<<it.value()->remainTime;
        qDebug()<<"state"<<it.value()->state;
        qDebug()<<"url"<<it.value()->url;
        qDebug()<<"offlineChnlSpeed"<<it.value()->offlineChnlSpeed;
        qDebug()<<"highChnlSpeed"<<it.value()->highChnlSpeed;
        qDebug()<<"==========end=============";
    }
    qDebug()<<"/////////////////end/////////////////";
    qDebug();

    // debug
   qDebug()<<"************************************end***************************************************";
}



