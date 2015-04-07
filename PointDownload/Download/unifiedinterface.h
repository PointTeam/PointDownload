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
/***********************************************************************
Date:   2014.5.31~
Description:
此类负责的任务有：
    1.负责将弹出窗口传递过来的URL进行分类，然后调用对应的类进行下载
    2.负责在初始化时读取xml配置文件，将已下载，正在下载，垃圾桶的项目数据提取并发送到qml界面显示
    3.定时向qml界面发送数据实时更新界面显示
    4.接受界面控制命令，如暂停，删除等，使用对应的类进行处理
    5.检查网络是否畅通，管理断网续传工作
Others:

History:
************************************************************************/

#ifndef UNIFIEDINTERFACE_H
#define UNIFIEDINTERFACE_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QTimer>
#include <QDateTime>
#include <QDesktopServices>
#include <QUrl>
#include <QSound>
#include <QSoundEffect>
#include <QDebug>
#include "DataType.h"
#include "Aria2Task/aria2task.h"
#include "YouGetTask/yougettask.h"
#include "PointTask/pointtask.h"
#include "SysData/dataflow.h"
#include "downloadxmlhandler.h"
#include "settingxmlhandler.h"
#include "Download/XwareTask/xwaretask.h"
#include "normalnotice.h"

#include "taskinfo.h"

// 新建窗口的命令名字
//const QString POPUP_PROGRAM_EXEC = "/tmp/build-pointdownload-Desktop-Debug/PointPopup/PointPopup";
const QString POPUP_PROGRAM_EXEC = "pointpopup";

class UnifiedInterface : public QObject
{
    Q_OBJECT

public:
    static UnifiedInterface * getInstance();            //获取此类的单例对象

    void cleanDownloadFinishItem(QString dlURL);

    void changeMaxJobCount(int newCount);

    void suspendAllDownloading();
    void resumeAllDownloading();
    int getJobCount();
signals:
    void taskAdded(TaskInfo *taskInfo);

    //实时数据
    void sRealTimeData(DownloadingItemInfo info);
    //动作反馈信号
    void sReturnControlResult(DownloadType dtype,OperationType otype, QString URL,bool result);
    //主动请求刷新正在下载列表界面
    void sDownloadItemChanged();

public slots:
    void controlDownload(DownloadType dtype, OperationType otype, QString URL);

    void downloadFinish(QString URL);
    void downloadGetError(QString URL,QString err, int toolType);

private slots:
    //获取初始化信息，显示到界面
    void initDownloadList();
    void initDownloadingStart();//根据最大任务限制，启动上次退出时正在下载的下载项

private:
    //构造函数
    explicit UnifiedInterface(QObject *parent = 0);

    void startPointDownload(TaskInfo *taskInfo);
    void startAria2Download(TaskInfo *taskInfo);
    void startYougetDownload(TaskInfo *taskInfo);
    void startXwareDownload(TaskInfo *taskInfo);
public:
    // 唯一的公共下载接口
    void startDownload(TaskInfo *taskInfo);

public:
    void trashDownloading(QString URL);
    void stopDownloading(QString URL);
    void suspendDownloading(QString URL);
    void resumeDownloading(QString URL);
    void redownloadTrash(QString URL);
    void deleteDownloading(QString URL);
    void deleteTrash(QString URL);
    void deleteDownloaded(QString URL);

private:
    //分类处理
    void handleDownloadingControl(OperationType otype, QString URL);
    void handleDownloadedControl(OperationType otype, QString URL);
    void handleDownloadTrashControl(OperationType otype, QString URL);
    void handleDownloadSearchControl(QString URL);

    //对正在下载的处理
    void priorityDownloading(QString URL);
    void openFolderDownloading(QString URL);
    void offlineDownloadDownloading(QString URL);
    void hightSpeedChannelDownloading(QString URL);
    void finishDownloading(QString URL);

    //对已下载完成的处理
    void redownloadDownloaded(QString URL);
    void openFolderDownloaded(QString URL);
    void trashDownloaded(QString URL);

    //获取初始化信息，显示到界面
    void initDownloadedList();
    void initdownloadingList();
    void initTrashList();

    void deleteFileFromDisk(QString path, QString fileName);

    //把当前下载列表中最慢的一个暂停
    void dropSlowest();
    //把就绪队列中的一个提到下载队列
    void startReady();
    void refreshDownloadingItem();
    TaskInfo *getPrepareInfoFromSDownloading(SDownloading infoStruct);

private:
    static UnifiedInterface * unifiedInterface;        //全局唯一对象
    //Map:URL,Otype
    QMap<QString, int>  downloadingListMap;
};

#endif // UNIFIEDINTERFACE_H
