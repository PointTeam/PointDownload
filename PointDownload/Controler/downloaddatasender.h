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

#ifndef DOWNLOADDATASENDER_H
#define DOWNLOADDATASENDER_H

#include <QObject>
#include <QTimer>
#include <QQmlEngine>
#include "Download/unifiedinterface.h"
#include "urlserver.h"

class DownloadDataSender : public QObject
{
    Q_OBJECT

    //将c++数据暴露给qml使用
    Q_PROPERTY(QString downloadType  READ getDownloadType WRITE setDownloadType NOTIFY downloadTypeChange)
    Q_PROPERTY(QString downloadURL  READ getDownloadURL WRITE setDownloadURL NOTIFY downloadURLChange)
    Q_PROPERTY(QString fileName READ getFileName WRITE setFileName NOTIFY fileNameChange)
    Q_PROPERTY(QString fileInfo READ getFileInfo WRITE setFileInfo NOTIFY fileInfoChange)
    Q_PROPERTY(QString btInfo READ getBTInfo WRITE setBTInfo NOTIFY btInfoChange)
    Q_PROPERTY(QString downloadState READ getDownloadState WRITE setDownloadState NOTIFY downloadStateChange)
    Q_PROPERTY(QString downloadSpeed READ getDownloadSpeed WRITE setDownloadSpeed NOTIFY downloadSpeedChange)
    Q_PROPERTY(QString thunderOfflineSpeed READ getThunderOfflineSpeed WRITE setThunderOfflineSpeed NOTIFY thunderOfflineSpeedChange)
    Q_PROPERTY(QString thunderHightSpeed READ getThunderHightSpeed WRITE setThunderHightSpeed NOTIFY thunderHightSpeedChange)
    Q_PROPERTY(double completePercentage READ getCompletePercentage WRITE setCompletePercentage NOTIFY completePercentageChange)
    Q_PROPERTY(QString contrlResultType READ getContrlResultType WRITE setContrlResultType NOTIFY contrlResultTypeChange)
    Q_PROPERTY(bool isAllSuspend READ getIsAllSuspend WRITE setIsAllSuspend NOTIFY isAllSuspendChange)

public:
    static DownloadDataSender * getInstance();
    //qml中能直接调用此方法
    Q_INVOKABLE void controlItem(QString dtype, QString otype, QString URL);//dtype:DownloadType otype:OperationType
    Q_INVOKABLE void suspendAllDownloading();
    Q_INVOKABLE void resumeAllDownloading();

    //传递到qml用到的get和set函数
    QString getDownloadType();
    QString getDownloadURL();
    QString getFileName();
    QString getFileInfo();
    QString getBTInfo();
    QString getDownloadState();
    QString getDownloadSpeed();
    QString getThunderOfflineSpeed();
    QString getThunderHightSpeed();
    double getCompletePercentage();
    QString getContrlResultType();
    bool getIsAllSuspend();

    void setDownloadType(QString type);
    void setDownloadURL(QString url);
    void setFileName(QString name);
    void setFileInfo(QString info);
    void setBTInfo(QString info);
    void setDownloadState(QString state);
    void setDownloadSpeed(QString speed);
    void setThunderOfflineSpeed(QString speed);
    void setThunderHightSpeed(QString speed);
    void setCompletePercentage(double perc);
    void setContrlResultType(QString type);
    void setIsAllSuspend(bool value);

signals:
    //用于通知qml的信号
    void downloadTypeChange();  //不管是哪种类型的数据，每次向界面发送数据时都会发送此信号，可以根据此信号做相应的更新
    void downloadURLChange();
    void fileNameChange();
    void fileInfoChange();
    void btInfoChange();
    void downloadStateChange();
    void downloadSpeedChange();
    void thunderOfflineSpeedChange();
    void thunderHightSpeedChange();
    void completePercentageChange();

    //监听到控制结果反馈时，将触发qml界面做相应更新,URL使用downloadURL确定,项目类型由downloadType确定
    void contrlResultTypeChange();

    void isAllSuspendChange();

    //通知界面更新下载项列表的排列
    void sRefreshDownloadingItem();
public slots:
    //用于接收统一接口类信号的接收
    //为列表面板添加项
    void addDownloadingItem(QString infoList);
    void addDownloadedItem(QString infoList);
    void addDownloadTrashItem(QString infoList);

    void slotGetDownloadingInfo(DownloadingItemInfo infoList);
    //操作返回值
    void slotGetContrlResult(DownloadType dtype,OperationType otype, QString URL,bool result);

    void initURLServer();
private:
    //构造函数
    explicit DownloadDataSender(QObject *parent = 0);

    void initConnection();
private:
    static DownloadDataSender * downloadDataSender; //全局实例

    QString downloadType;       //项目类型：Downloading、Downloaded、DownloadTrash
    QString downloadURL;        //所有都可以使用
    QString fileName;               //所有都可以使用
    QString fileInfo;                   //正在下载和已下载项使用,文件名，URL，文件大小，图标路径等等
    QString btInfo;                     //正在下载项使用,BT下载信息，因为BT都含有较为多的信息
    QString downloadState;     //正在下载项使用,文件状态 , "dlstate_downloading" 或者是 "dlstate_suspend",经常更新
    QString downloadSpeed;      //正在下载项使用,下载速度,经常更新
    QString thunderOfflineSpeed; //迅雷离线速度
    QString thunderHightSpeed;  //迅雷高速通道速度
    double completePercentage;  //正在下载项使用,已完成的百分比,经常更新
    QString contrlResultType;       //控制反馈结果类型

    bool isAllSuspend;          //是否全部都已经被暂停,为弹出窗口提供控制依据
};


//将单例对象注册到qml中使用的回调函数
static QObject * dataObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return DownloadDataSender::getInstance();
}

#endif // DOWNLOADDATASENDER_H
