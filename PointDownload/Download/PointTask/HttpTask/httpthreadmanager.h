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

#ifndef HTTPTHREADMANAGER_H
#define HTTPTHREADMANAGER_H

#include <QObject>
#include <QMutex>
#include <QFile>
#include <QTimer>
#include "httpthread.h"
#include "downloadxmlhandler.h"
#include "pdatatype.h"
#include "taskinfo.h"

class HttpThreadManager : public QObject
{
    Q_OBJECT
public:
    explicit HttpThreadManager(const TaskInfo & taskInfo, QObject *parent = 0);
    explicit HttpThreadManager(const QString & fileID, QObject *parent = 0);

    void startDownload();
    void stopDownload();

signals:
    void taskFinished(const QString & taskID);
    void taskItemInfoUpdate(const TaskItemInfo & info);
    void getError(const QString & fileID, const QString & error, PDataType::ToolType toolType);

public slots:
    void slotProgressChange(qint64 doneSize);//与所有子线程相连，获取下载进度
    void slotThreadFinish(int statusCode);//与所有子线程相连，每个子线程完成后均触发此槽进行统计

    void slotGetNewRedirectURL(QUrl URL);   //url重定向之后再下载
    void slotThreadsIsLimited();            //某些服务器会限制连接数导致不能下载完全，此时使用一个线程下载

private slots:
    void slotSendDataToUI();    //由定时器触发，定时将信息发送至界面
    void slotUpdataXMLFile();   //由定时器触发，定时更新xml文件
    void slotRetryDownload();   //线程不正常退出，重试下载

private:
    void touchDownloadFile();
    void initUpdateTimer();
    void initData();
    void changeStateToDownloading(const QString & fileID);
    //根据任务的大小及线程数对任务进行分割下载
    QList<SDownloadThread> splitTask(short threadCount, qint64 size);
    //启动下载前先将下载信息写入正在下载的xml记录文件中
    void inserToXMLFile(const TaskInfo & taskInfo);
    TaskInfo getPrepareInfoFromXML(const QString & fileID);

    int getDownloadSpeed();
    double getDownloadPercent();
private:
    short finishThreadCount;    //已完成的线程数，当已完成的和下载前分配的线程个数相同，则下载完成
    qint64 totalDoneSize;       //总共已完成的字节数
    qint64 receiveBytesPerSecond;                           //每秒下载的字节数（即速度）
    bool changeLimited;

    QMutex mutex;
    QList<HttpThread *> threadList;
    DownloadXMLHandler  xmlOpera;
    TaskInfo taskInfo;

    QTimer * updateXMLTimer;//定时更新xml文件的计时器
    QTimer * updateDataTimer;//定时更新向界面传送信息的计时器

    const int RETRY_DOWNLOAD_INTERVAL = 5000;
    const int UPDATE_DATA_INTERVAL = 1000;
    const int UPDATE_XML_INTERVAL = 3000;
    const QString POINT_FILE_FLAG = ".Point";
};

#endif // HTTPTHREADMANAGER_H
