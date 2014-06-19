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

#include "settingcontroler.h"

SettingControler::SettingControler(QObject *parent) :
    QObject(parent)
{
    initData();
}

void SettingControler::updateBeep(QString beep)
{
    if (beep !="")
    {
        XMLOperations tmpOpera;
        SMainConfig tmpConfig;
        tmpConfig.beep = beep;
        tmpOpera.writeMainConfigFile(tmpConfig);
        initData();
    }
    else
        return;
}

void SettingControler::updateExitOnClose(QString flag)
{
    if (flag !="")
    {
        XMLOperations tmpOpera;
        SMainConfig tmpConfig;
        tmpConfig.exitOnClose = flag;
        tmpOpera.writeMainConfigFile(tmpConfig);
        initData();
    }
    else
        return;
}

void SettingControler::updateClipboard(QString flag)
{
        if (flag !="")
        {
            XMLOperations tmpOpera;
            SMainConfig tmpConfig;
            tmpConfig.clipboard = flag;
            tmpOpera.writeMainConfigFile(tmpConfig);
            initData();
        }
        else
            return;
}

void SettingControler::updateThreadCount(QString count)
{
    if (count != "")
    {
        XMLOperations tmpOPera;
        SMainConfig tmpConfig;
        tmpConfig.defaultThreadCount = count;
        tmpOPera.writeMainConfigFile(tmpConfig);
        initData();
    }
    else
        return;
}

void SettingControler::updateMaxJobCount(QString count)
{
    if (count != "")
    {
        XMLOperations tmpOPera;
        SMainConfig tmpConfig;
        tmpConfig.maxJobCount = count;
        tmpOPera.writeMainConfigFile(tmpConfig);
        initData();

        //处理正在下载项,刷新界面
        UnifiedInterface::getInstance()->changeMaxJobCount(count.toInt());
    }
    else
        return;
}

void SettingControler::updateDownloadSpeed(QString speed)
{
    if (speed != "")
    {
        XMLOperations tmpOPera;
        SMainConfig tmpConfig;
        tmpConfig.downloadSpeed = speed;
        tmpOPera.writeMainConfigFile(tmpConfig);
        initData();
    }
    else
        return;
}

QString SettingControler::getOperatingSystem()
{
    return operatingSystem;
}

void SettingControler::setOperatingSystem(QString sys)
{
    operatingSystem =sys;
    emit operatingSystemChange();
}

QString SettingControler::getVersion()
{
    return version;
}

void SettingControler::setVersion(QString tmpVersion)
{
    version = tmpVersion;
    emit versionChange();
}

QString SettingControler::getSavePath()
{
    return savePath;
}

void SettingControler::setSavePath(QString path)
{
    savePath = path;
    emit savePathChange();
}

QString SettingControler::getBeepEnable()
{
    return beepEnable;
}

void SettingControler::setBeepEnable(QString beep)
{
    beepEnable = beep;
    emit beepEnableChange();
}

QString SettingControler::getEnableUpload()
{
    return enableUpload;
}

void SettingControler::setEnableUpload(QString upload)
{
    enableUpload = upload;
    emit enableUploadChange();
}

QString SettingControler::getVideoDetectType()
{
    return videoDetectType;
}

void SettingControler::setVideoDetectType(QString tyoe)
{
    videoDetectType = tyoe;
    emit videoDetectTypeChange();
}

QString SettingControler::getAudioDetectType()
{
    return audioDetectType;
}

void SettingControler::setAudioDetectType(QString type)
{
    audioDetectType = type;
    emit audioDetectTypeChange();
}

QString SettingControler::getClipboard()
{
    return clipboard;
}

void SettingControler::setClipboard(QString flag)
{
    clipboard = flag;
    emit ClipboardChange();
}

QString SettingControler::getExitOnClose()
{
    return exitOnClose;
}

void SettingControler::setExitOnClose(QString flag)
{
    exitOnClose = flag;
    emit exitOnCloseChange();
}

QString SettingControler::getDefaultThreadCount()
{
    return defaultThreadCount;
}

void SettingControler::setDefaultThreadCount(QString count)
{
    defaultThreadCount = count;
    emit defaultThreadCountChange();
}

QString SettingControler::getMaxJobCount()
{
    return maxJobCount;
}

void SettingControler::setMaxJobCount(QString count)
{
    maxJobCount = count;
    emit maxJobCountChange();
}

QString SettingControler::getMaxDSpeed()
{
    return maxDownloadSpeed;
}

void SettingControler::setMaxDSpeed(QString speed)
{
    maxDownloadSpeed = speed;
    emit maxDSpeedChange();
}


void SettingControler::initData()
{
    XMLOperations tmpOpera;
    SMainConfig tmpConfig = tmpOpera.getMainConfig();
    setOperatingSystem(tmpConfig.operatingSysType);
    setVersion(tmpConfig.version);
#ifdef Q_OS_LINUX
    setSavePath(tmpConfig.linuxSavePath);
#elif Q_OS_WIN
    setSavePath(tmpConfig.windowsSavePath);
#endif
    setBeepEnable(tmpConfig.beep);
    setEnableUpload(tmpConfig.enableUpload);
    setVideoDetectType(tmpConfig.videoDetectType);
    setAudioDetectType(tmpConfig.audioDetectType);
    setClipboard(tmpConfig.clipboard);
    setExitOnClose(tmpConfig.exitOnClose);
    setDefaultThreadCount(tmpConfig.defaultThreadCount);
    setMaxJobCount(tmpConfig.maxJobCount);
    setMaxDSpeed(tmpConfig.downloadSpeed);
}

void SettingControler::selectDefaultSavePath()
{
    XMLOperations tmpOpera;
#ifdef Q_OS_LINUX
    QString defaultPath = tmpOpera.getMainConfig().linuxSavePath;
#elif Q_OS_WIN
    QString defaultPath = tmpOpera.getMainConfig().windowsSavePath;
#endif
    QString tmpPath =  QFileDialog::getExistingDirectory(0,
                                                      tr("Open Folder"),
                                                      defaultPath,
                                                      QFileDialog::ShowDirsOnly);
    if (tmpPath != "" && tmpPath != defaultPath)
    {
        SMainConfig tmpStruct;
        tmpStruct.linuxSavePath = tmpPath;
        tmpStruct.windowsSavePath = tmpPath;
        tmpOpera.writeMainConfigFile(tmpStruct);
        setSavePath(tmpPath);
    }
}



























