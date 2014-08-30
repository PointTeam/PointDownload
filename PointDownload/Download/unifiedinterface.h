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
#include <QDebug>
#include "DataType.h"
#include "YouGetTask/yougettask.h"
#include "PointTask/pointtask.h"
#include "SysData/dataflow.h"
#include "XMLHandler/downloadxmlhandler.h"
#include "XMLHandler/settingxmlhandler.h"
#include "Download/XwareTask/xwaretask.h"

const QString POPUP_PROGRAM_PATH ="/opt/Point/PopupWindow/PointPopup";

class UnifiedInterface : public QObject
{
    Q_OBJECT

public:
    static UnifiedInterface * getInstance();            //获取此类的单例对象

    void getPrepareDownloadInfo(PrepareDownloadInfo info);  //获取到从弹出界面传递过来的信息并调用相应的类进行下载处理

    void changeMaxJobCount(int newCount);

    void suspendAllDownloading();
    void resumeAllDownloading();
    int getJobCount();
signals:
    void sAddDownloadingItem(QString infoList);
    void sAddDownloadedItem(QString infolist);
    void sAddDownloadTrashItem(QString infoList);

    void sRealTimeData(DownloadingItemInfo info);
    //动作反馈信号
    void sReturnControlResult(DownloadType dtype,OperationType otype, QString URL,bool result);
    //主动请求刷新正在下载列表界面
    void sRefreshDownloadingItem();

public slots:
    void controlDownload(DownloadType dtype, OperationType otype, QString URL);

    void downloadFinish(QString URL);
    void downloadGetError(QString URL,QString err, DownloadToolsType toolType);

private slots:
    //获取初始化信息，显示到界面
    void initDownloadList();
    void initDownloadingStart();//根据最大任务限制，启动上次退出时正在下载的下载项
    void initTimer();

    void pingOutSide();                 //由pingTimer触发
    void getSpeedSum();              //获取正在下载项的所有项目的平均速度的总和
private:
    //构造函数
    explicit UnifiedInterface(QObject *parent = 0);

    void startPointDownload(PrepareDownloadInfo info);
    void startAria2Download(PrepareDownloadInfo info);
    void startYougetDownload(PrepareDownloadInfo info);
    void startXwareDownload(PrepareDownloadInfo info);

    //分类处理
    void handleDownloadingControl(OperationType otype, QString URL);
    void handleDownloadedControl(OperationType otype, QString URL);
    void handleDownloadTrashControl(OperationType otype, QString URL);
    void handleDownloadSearchControl(QString URL);

    //对正在下载的处理
    void stopDownloading(QString URL);
    void suspendDownloading(QString URL);
    void resumeDownloading(QString URL);
    void priorityDownloading(QString URL);
    void openFolderDownloading(QString URL);
    void trashDownloading(QString URL);
    void deleteDownloading(QString URL);
    void offlineDownloadDownloading(QString URL);
    void hightSpeedChannelDownloading(QString URL);
    void finishDownloading(QString URL);

    //对已下载完成的处理
    void redownloadDownloaded(QString URL);
    void openFolderDownloaded(QString URL);
    void trashDownloaded(QString URL);
    void deleteDownloaded(QString URL);

    //对垃圾桶的处理
    void redownloadTrash(QString URL);
    void deleteTrash(QString URL);

    //获取初始化信息，显示到界面
    void initDownloadedList();
    void initdownloadingList();
    void initTrashList();
    void initConnection();

    void deleteFileFromDisk(QString path, QString fileName);

    //把当前下载列表中最慢的一个暂停
    void dropSlowest();
    //把就绪队列中的一个提到下载队列
    void startReady();
    void refreshDownloadingItem();
    PrepareDownloadInfo getPrepareInfoFromSDownloading(SDownloading infoStruct);

    //断网处理
    bool pingNetWork();
    void suspendWhenOffLine();      //断网时暂停正在下载的项并存入suspendListmap中
    void resumeWhenOnLine();
private:
    static UnifiedInterface * unifiedInterface;        //全局唯一对象
    //Map:URL,Otype
    QMap<QString,DownloadToolsType>  downloadingListMap;
    QStringList suspendList; //断网时存储暂停项的list

    QTimer * pingTimer;//定时ping外面的时钟
    QTimer * speedSumTimer;//定时加和正在下载项的平均速度,如果加和速度为0,则设为断网状态,需要ping外面服务器

    const int PING_INTERVAL = 5000;
    const int SUM_INTERVAL = 10000;
};

#endif // UNIFIEDINTERFACE_H
