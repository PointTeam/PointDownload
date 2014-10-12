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

#ifndef SETTINGCONTROLER_H
#define SETTINGCONTROLER_H

#include <QObject>
#include <QFileDialog>
#include "settingxmlhandler.h"
#include "Download/unifiedinterface.h"

class SettingControler : public QObject
{
    Q_OBJECT
    //将c++数据暴露给qml使用
    Q_PROPERTY(QString operatingSystem READ getOperatingSystem() WRITE setOperatingSystem() NOTIFY operatingSystemChange())
    Q_PROPERTY(QString version READ getVersion() WRITE setVersion() NOTIFY versionChange())
    Q_PROPERTY(QString savePath READ getSavePath() WRITE setSavePath() NOTIFY savePathChange())
    Q_PROPERTY(bool alertToneEnable READ getAlertToneEnable() WRITE setAlertToneEnable() NOTIFY alertToneEnableChange())
    Q_PROPERTY(QString enableUpload READ getEnableUpload() WRITE setEnableUpload() NOTIFY enableUploadChange())
    Q_PROPERTY(bool enableDropzone READ getEnableDropzone WRITE setEnableDropzone NOTIFY enableDropzoneChange)
    Q_PROPERTY(bool exitOnClose READ getExitOnClose() WRITE setExitOnClose() NOTIFY exitOnCloseChange())
    Q_PROPERTY(QString defaultThreadCount READ getDefaultThreadCount() WRITE setDefaultThreadCount() NOTIFY defaultThreadCountChange())
    Q_PROPERTY(QString maxJobCount READ getMaxJobCount() WRITE setMaxJobCount() NOTIFY maxJobCountChange())
    Q_PROPERTY(QString maxDownloadSpeed READ getMaxDSpeed() WRITE setMaxDSpeed() NOTIFY maxDSpeedChange())
    Q_PROPERTY(QString maxUploadSpeed READ getMaxUSpeed WRITE setMaxUSpeed NOTIFY maxUSpeedChange)
    Q_PROPERTY(QString priorityTool READ getPriorityTool WRITE setPriorityTool NOTIFY priorityToolChange)

    Q_PROPERTY(QString savePathState READ getSavePathState WRITE setSavePathState NOTIFY savePathStateChange)
public:
    explicit SettingControler(QObject *parent = 0);

    //qml中能直接调用此方法
    Q_INVOKABLE void initData();
    Q_INVOKABLE void selectSavePath(QString pathType);//Default,Desktop,Other
    Q_INVOKABLE void selectPriorityTool(QString tool);//Point,Aria2,Xware

    Q_INVOKABLE bool getShowSysDataFlag();              //记录中部信息面板是否显示
    Q_INVOKABLE void setShowSysDataFlag(bool flag);
    Q_INVOKABLE bool getSettingWinShowed();
    Q_INVOKABLE void setSettingWinShowed(bool flag);


    QString getOperatingSystem();
    QString getVersion();
    QString getSavePath();
    bool getAlertToneEnable();
    QString getEnableUpload();
    bool getEnableDropzone();
    bool getExitOnClose();
    QString getDefaultThreadCount();
    QString getMaxJobCount();
    QString getMaxDSpeed();
    QString getMaxUSpeed();
    QString getPriorityTool();

    QString getSavePathState();

    void setOperatingSystem(QString sys);
    void setVersion(QString version);
    void setSavePath(QString path);
    void setAlertToneEnable(bool isEnable);
    void setEnableUpload(QString upload);
    void setEnableDropzone(bool flag);
    void setExitOnClose(bool flag);
    void setDefaultThreadCount(QString count);
    void setMaxJobCount(QString count);
    void setMaxDSpeed(QString speed);
    void setMaxUSpeed(QString speed);
    void setPriorityTool(QString tool);

    void setSavePathState(QString pathState);
signals:
    void operatingSystemChange();
    void versionChange();
    void savePathChange();
    void alertToneEnableChange();
    void enableUploadChange();
    void enableDropzoneChange();
    void exitOnCloseChange();
    void defaultThreadCountChange();
    void maxJobCountChange();
    void maxDSpeedChange();
    void maxUSpeedChange();
    void priorityToolChange();

    void savePathStateChange();
private:
    QString operatingSystem;
    QString version;
    QString savePath;
    bool alertToneEnable;
    QString enableUpload;
    bool enableDropzone;
    bool exitOnClose;
    QString defaultThreadCount;
    QString maxJobCount;
    QString maxDownloadSpeed;
    QString maxUploadSpeed;
    QString priorityTool;

    QString savePathState; //Default,Desktop,Other

    SettingXMLHandler sHandler;

    const QString DEFAULT_SAVE_PATH =
            QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).at(0) + "/PointDownload";
    const QString DESKTOP_SAVE_PATH =
            QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0);
};

#endif // SETTINGCONTROLER_H
