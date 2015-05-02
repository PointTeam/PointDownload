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
    Please name all public signal as "signalXXX(Type value, ...)"
    Please name all public slot as "slotXXX(Type value, ...)"
    Please name all public function as "pXXX(Type value, ...)"

History:
************************************************************************/

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QTimer>
#include <QDateTime>
#include <QDesktopServices>
#include <QUrl>
#include <QQmlEngine>
#include <QJsonObject>
#include <QProcess>
#include <QDebug>
#include "pdatatype.h"
#include "taskinfo.h"
#include "Download/YouGetTask/yougettask.h"

class MainController : public QObject
{
    Q_OBJECT

public:
    static MainController * getInstance();            //获取此类的单例对象
    static QObject * dataObj(QQmlEngine *engine, QJSEngine *scriptEngine);

    // 唯一的公共下载接口
    Q_INVOKABLE void pStartDownload(const TaskInfo &taskInfo);
    Q_INVOKABLE void pChangeMaxJobCount(int newCount);
    Q_INVOKABLE int pGetJobCount();
    Q_INVOKABLE void pSuspendAllTask();
    Q_INVOKABLE void pResumeAllTask();
    Q_INVOKABLE void pControlFileItem(QString fileID,int dtype, int otype);

public slots:
    void slotTaskItemInfoUpdate(const TaskItemInfo & itemInfo);//please update xmlfile in every single task progress or thread
    void slotTaskFinished(const QString & taskID);
    void slotGetError(const QString & fileID,const QString & errorMessage, PDataType::ToolType toolType);

Q_SIGNALS:
//signals:
    void signalAddDownloadingItem(QJsonObject itemInfo);
    void signalAddDownloadedItem(QJsonObject itemInfo);
    void signalAddDownloadTrashItem(QJsonObject itemInfo);
    void signalTaskItemInfoUpdate(QJsonObject itemInfo); //实时数据更新
    void signalTaskFinished(const QString &fileID);
    void signalControlResult(QJsonObject controlResult);  //动作反馈信号

private slots:
    //获取初始化信息，显示到界面
    void initDownloadList();
    void initDownloadingStart();//根据最大任务限制，启动上次退出时正在下载的下载项

private:
    //构造函数
    explicit MainController(QObject *parent = 0);
    ~MainController();

    void startPointDownload(const TaskInfo &taskInfo);
    void startYougetDownload(const TaskInfo &taskInfo);
    void startAria2Download(const TaskInfo &taskInfo);
    void startXwareDownload(const TaskInfo &taskInfo);

    //分类处理
    void handleDownloadingControl( const QString &fileID, PDataType::OperationType otype);
    void handleDownloadedControl( const QString &fileID, PDataType::OperationType otype);
    void handleDownloadTrashControl(const  QString &fileID, PDataType::OperationType otype);

    //对正在下载的处理
    void dlingDelete(const QString &fileID);
    void dlingSuspend(const QString &fileID);
    void dlingResume(const QString &fileID);
    void dlingRaise(const QString &fileID);
    void dlingOpenFolder(const QString &fileID);
    void dlingTrash(const QString &fileID);
    void dlingOfflineDownload(const QString &fileID);
    void dlingHightSpeedChannel(const QString &fileID);

    //对已下载完成的处理
    void dledDelete(const QString &fileID);
    void dledOpenFolder(const QString &fileID);
    void dledRedownload(const QString &fileID);
    void dledTrash(const QString &fileID);

    //对垃圾桶的处理
    void dltrashDelete(const QString &fileID);
    void dltrashRedownload(const QString &fileID);

    //获取初始化信息，显示到界面
    void initDLedList();
    void initDLingList();
    void initDLtrashList();

    void deleteFileFromDisk(const QString & path, const QString & fileName);
    void startPopUpProgram(const QString & url);

//    //把当前下载列表中最慢的一个暂停
//    void dropSlowest();
//    //把就绪队列中的一个提到下载队列
//    void startReady();
//    void refreshDownloadingItem();
//    TaskInfo getPrepareInfoFromSDownloading(SDownloading infoStruct);

private:
    static MainController * mainController;        //全局唯一对象
    //Map:fileID,toolType
    QMap<QString, PDataType::ToolType>  taskListMap;

    //DO NOT CHANGE THIS PROPERTY
    const QString POPUP_PROGRAM_EXEC = "/opt/Point/PopupWindow/PointPopup";
};

#endif // MAINCONTROLLER_H
