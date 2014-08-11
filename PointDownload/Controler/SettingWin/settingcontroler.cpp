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
    sHandler.setChildElement(GeneralSettings,"SavePath",path);
    savePath = path;
    emit savePathChange();
}

bool SettingControler::getAlertToneEnable()
{
    return alertToneEnable;
}

void SettingControler::setAlertToneEnable(bool isEnable)
{    if (isEnable)
        sHandler.setChildElement(GeneralSettings,"AlertTone","Enable");
    else
        sHandler.setChildElement(GeneralSettings,"AlertTone","Disable");

    alertToneEnable = isEnable;
    emit alertToneEnableChange();
}

QString SettingControler::getEnableUpload()
{
    return enableUpload;
}

void SettingControler::setEnableUpload(QString upload)
{
    sHandler.setChildElement(GeneralSettings,"EnableUpload",upload);
    enableUpload = upload;
    emit enableUploadChange();
}

bool SettingControler::getEnableDropzone()
{
    return enableDropzone;
}

void SettingControler::setEnableDropzone(bool flag)
{
    if (flag)
        sHandler.setChildElement(DropzoneSetting,"State","Enable");
    else
        sHandler.setChildElement(DropzoneSetting,"State","Disable");

    enableDropzone = flag;
    emit enableDropzoneChange();
}

bool SettingControler::getExitOnClose()
{
    return exitOnClose;
}

void SettingControler::setExitOnClose(bool flag)
{    if (flag)
    {
        sHandler.setChildElement(GeneralSettings,"ExitOnClose","True");
    }
    else
    {
        sHandler.setChildElement(GeneralSettings,"ExitOnClose","False");
    }
    exitOnClose = flag;
    emit exitOnCloseChange();
}

QString SettingControler::getDefaultThreadCount()
{
    return defaultThreadCount;
}

void SettingControler::setDefaultThreadCount(QString count)
{
    sHandler.setChildElement(GeneralSettings,"DefaultThreadCount",count);
    defaultThreadCount = count;
    emit defaultThreadCountChange();
}

QString SettingControler::getMaxJobCount()
{
    return maxJobCount;
}

void SettingControler::setMaxJobCount(QString count)
{
    sHandler.setChildElement(GeneralSettings,"MaxJobCount",count);
    maxJobCount = count;
    emit maxJobCountChange();

    //处理正在下载项,刷新界面
    UnifiedInterface::getInstance()->changeMaxJobCount(count.toInt());
}

QString SettingControler::getMaxDSpeed()
{
    return maxDownloadSpeed;
}

QString SettingControler::getMaxUSpeed()
{
    return maxUploadSpeed;
}

QString SettingControler::getPriorityTool()
{
    return priorityTool;
}

QString SettingControler::getSavePathState()
{
    return savePathState;
}

void SettingControler::setMaxDSpeed(QString speed)
{
    sHandler.setChildElement(GeneralSettings,"MaxDownloadSpeed",speed);
    maxDownloadSpeed = speed;
    emit maxDSpeedChange();
}


void SettingControler::setMaxUSpeed(QString speed)
{
    sHandler.setChildElement(GeneralSettings,"MaxUploadSpeed",speed);
    maxUploadSpeed = speed;
    emit maxUSpeedChange();
}

void SettingControler::setPriorityTool(QString tool)
{
    if (tool == "")
        return;
    sHandler.setChildElement(GeneralSettings,"PriorityTool",tool);
    priorityTool = tool;
    emit priorityToolChange();
}

void SettingControler::setSavePathState(QString pathState)
{
    savePathState = pathState;
    emit savePathStateChange();
}

void SettingControler::initData()
{
    setOperatingSystem(sHandler.getChildElement(GeneralSettings,"OperatingSystem"));
    setVersion(sHandler.getChildElement(GeneralSettings,"PointVersion"));
    setSavePath(sHandler.getChildElement(GeneralSettings,"SavePath"));
    setAlertToneEnable(sHandler.getChildElement(GeneralSettings,"AlertTone")=="Enable"?true:false);
    setEnableUpload(sHandler.getChildElement(GeneralSettings,"EnableUpload"));
    setExitOnClose(sHandler.getChildElement(GeneralSettings,"ExitOnClose")=="True"?true:false);
    setDefaultThreadCount(sHandler.getChildElement(GeneralSettings,"DefaultThreadCount"));
    setMaxJobCount(sHandler.getChildElement(GeneralSettings,"MaxJobCount"));
    setMaxDSpeed(sHandler.getChildElement(GeneralSettings,"MaxDownloadSpeed"));
    setMaxUSpeed(sHandler.getChildElement(GeneralSettings,"MaxUploadSpeed"));
    setEnableDropzone(sHandler.getChildElement(DropzoneSetting,"State")=="Enable"?true:false);
    setPriorityTool(sHandler.getChildElement(GeneralSettings,"PriorityTool"));

    if (getSavePath() == DEFAULT_SAVE_PATH)
        setSavePathState("Default");
    else if (getSavePath() == DESKTOP_SAVE_PATH)
        setSavePathState("Desktop");
    else
        setSavePathState("Other");
}

void SettingControler::selectSavePath(QString pathType)
{
    QString path;
    if (pathType == "Default")
    {
        path = DEFAULT_SAVE_PATH;
    }
    else if (pathType == "Desktop")
    {
        path = DESKTOP_SAVE_PATH;
    }
    else
    {
        QString oldPath = sHandler.getChildElement(GeneralSettings,"SavePath");
        QString tmpPath =  QFileDialog::getExistingDirectory(0,
                                                          tr("Open Folder"),
                                                          oldPath,
                                                          QFileDialog::ShowDirsOnly);
        if (tmpPath != "" && tmpPath != oldPath)
        {
            path = tmpPath;
        }
        else
            path = oldPath;
    }

    sHandler.setChildElement(GeneralSettings,"SavePath",path);
    setSavePath(path);
}

void SettingControler::selectPriorityTool(QString tool)
{
    sHandler.setChildElement(GeneralSettings,"PriorityTool",tool);
    setPriorityTool(tool);
}




















