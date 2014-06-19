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
#include "XMLHandler/xmloperations.h"
#include "Download/unifiedinterface.h"

class SettingControler : public QObject
{
    Q_OBJECT
    //将c++数据暴露给qml使用
    Q_PROPERTY(QString operatingSystem READ getOperatingSystem() WRITE setOperatingSystem() NOTIFY operatingSystemChange())
    Q_PROPERTY(QString version READ getVersion() WRITE setVersion() NOTIFY versionChange())
    Q_PROPERTY(QString savePath READ getSavePath() WRITE setSavePath() NOTIFY savePathChange())
    Q_PROPERTY(QString beepEnable READ getBeepEnable() WRITE setBeepEnable() NOTIFY beepEnableChange())
    Q_PROPERTY(QString enableUpload READ getEnableUpload() WRITE setEnableUpload() NOTIFY enableUploadChange())
    Q_PROPERTY(QString videoDetectType READ getVideoDetectType() WRITE setVideoDetectType() NOTIFY videoDetectTypeChange())
    Q_PROPERTY(QString audioDetectType READ getAudioDetectType() WRITE setAudioDetectType() NOTIFY audioDetectTypeChange())
    Q_PROPERTY(QString clipboard READ getClipboard() WRITE setClipboard() NOTIFY ClipboardChange())
    Q_PROPERTY(QString exitOnClose READ getExitOnClose() WRITE setExitOnClose() NOTIFY exitOnCloseChange())
    Q_PROPERTY(QString defaultThreadCount READ getDefaultThreadCount() WRITE setDefaultThreadCount() NOTIFY defaultThreadCountChange())
    Q_PROPERTY(QString maxJobCount READ getMaxJobCount() WRITE setMaxJobCount() NOTIFY maxJobCountChange())
    Q_PROPERTY(QString maxDownloadSpeed READ getMaxDSpeed() WRITE setMaxDSpeed() NOTIFY maxDSpeedChange())
public:
    explicit SettingControler(QObject *parent = 0);

    //qml中能直接调用此方法
    Q_INVOKABLE void updateBeep(QString beep);
    Q_INVOKABLE void updateExitOnClose(QString flag);
    Q_INVOKABLE void updateClipboard(QString flag);
    Q_INVOKABLE void updateThreadCount(QString count);
    Q_INVOKABLE void updateMaxJobCount(QString count);
    Q_INVOKABLE void updateDownloadSpeed(QString speed);
    Q_INVOKABLE void initData();
    Q_INVOKABLE void selectDefaultSavePath();


    QString getOperatingSystem();
    void setOperatingSystem(QString sys);
    QString getVersion();
    void setVersion(QString version);
    QString getSavePath();
    void setSavePath(QString path);
    QString getBeepEnable();
    void setBeepEnable(QString beep);
    QString getEnableUpload();
    void setEnableUpload(QString upload);
    QString getVideoDetectType();
    void setVideoDetectType(QString type);
    QString getAudioDetectType();
    void setAudioDetectType(QString tyoe);
    QString getClipboard();
    void setClipboard(QString flag);
    QString getExitOnClose();
    void setExitOnClose(QString flag);
    QString getDefaultThreadCount();
    void setDefaultThreadCount(QString count);
    QString getMaxJobCount();
    void setMaxJobCount(QString count);
    QString getMaxDSpeed();
    void setMaxDSpeed(QString speed);

signals:
    void operatingSystemChange();
    void versionChange();
    void savePathChange();
    void beepEnableChange();
    void enableUploadChange();
    void videoDetectTypeChange();
    void audioDetectTypeChange();
    void ClipboardChange();
    void exitOnCloseChange();
    void defaultThreadCountChange();
    void maxJobCountChange();
    void maxDSpeedChange();

private:
    QString operatingSystem;
    QString version;
    QString savePath;
    QString beepEnable;
    QString enableUpload;
    QString videoDetectType;
    QString audioDetectType;
    QString clipboard;
    QString exitOnClose;
    QString defaultThreadCount;
    QString maxJobCount;
    QString maxDownloadSpeed;


};

#endif // SETTINGCONTROLER_H
