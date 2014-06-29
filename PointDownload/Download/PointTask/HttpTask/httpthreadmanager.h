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

#ifndef HTTPTHREADMANAGER_H
#define HTTPTHREADMANAGER_H

#include <QObject>
#include <QMutex>
#include <QFile>
#include <QTimer>
#include "httpthread.h"
#include "XMLHandler/xmloperations.h"
#include "Download/DataType.h"

const QString POINT_FILE_FLAG = ".Point";
const QString SUSPEND_STATE = "dlstate_suspend";
const QString DOWNLOADING_STATE = "dlstate_downloading";
const int UPDATE_XML_INTERVAL = 3000;
const int UPDATE_DATA_INTERVAL = 1000;

class HttpThreadManager : public QObject
{
    Q_OBJECT
public:
    explicit HttpThreadManager(PrepareDownloadInfo &info, QObject *parent = 0);
    explicit HttpThreadManager(QString URL, QObject *parent = 0);

    void startDownload();
    void stopDownload();

    QFile downloadFile;//下载文件的管理对象，会分发到各个子线程中
signals:
    void sRealTimeData(DownloadingItemInfo info);
    void sHttpError(QString URL,QString err, DownloadToolsType toolType);
    void sDownloadFinish(QString);

public slots:
    void slotSendDataToUI();//由定时器触发，定时将信息发送至界面
    void slotUpdataXMLFile();//由定时器触发，定时更新xml文件

    void slotProgressChange(qint64 doneSize);//与所有子线程相连，获取下载进度
    void slotThreadFinish();//与所有子线程相连，每个子线程完成后均触发此槽进行统计

    void slotGetNewRedirectURL(QUrl URL);//
private:
    void touchDownloadFile();
//    void initDownloadFile();
    void initUpdateTimer();
    void initData();
    void changeStateToDownloading(QString URL);
    //根据任务的大小及线程数对任务进行分割下载（即实现多线程下载）
    QList<SDownloadThread> splitTask(short threadCount, qint64 size);
    //启动下载前先将下载信息写入正在下载的xml记录文件中
    void inserToXMLFile(PrepareDownloadInfo &info);
    PrepareDownloadInfo getPrepareInfoFromXML(QString URL);

    QString getDownloadSpeed();
    double getDownloadPercent();
private:
    short finishThreadCount;//已完成的线程数，当已完成的和下载前分配的线程个数相同，则下载完成
    qint64 totalDoneSize;                                           //总共已完成的字节数
    qint64 receiveBytesPerSecond;                           //每秒下载的字节数（即速度）

    QMutex mutex;
    QList<HttpThread *> threadList;
    XMLOperations  xmlOpera;
    PrepareDownloadInfo gDownloadInfo;

    QTimer * updateXMLTimer;//定时更新xml文件的计时器
    QTimer * updateDataTimer;//定时更新向界面传送信息的计时器
};

#endif // HTTPTHREADMANAGER_H
