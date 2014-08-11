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

#include "getsavepathdialog.h"

/**************************************************************************************************
Function: GetSavePathDialog()
Description: 构造函数，首先确定存储路径是否存在，不存在则创建
Calls:
    1.touchSaveFolder（）
Input:  parent
Output:
Return:
Others:
**************************************************************************************************/
GetSavePathDialog::GetSavePathDialog(QObject *parent) :
    QObject(parent)
{
    touchSaveFolder();//make sure the save folder is exist
}

/**************************************************************************************************
Function: getPathName()
Description: 弹出文件对话框
Calls:
    1.setSavePathName（）
Input:
Output:
Return:
Others:
**************************************************************************************************/
void GetSavePathDialog::getPathName()
{
    SettingXMLHandler tmpHandler;
    QString tmpPath =  QFileDialog::getExistingDirectory(0,
                                                      tr("Open Folder"),
                                                      tmpHandler.getChildElement(GeneralSettings,"SavePath"),
                                                      QFileDialog::ShowDirsOnly);
    if (tmpPath != "")
        setSavePathName(tmpPath);
}

/**************************************************************************************************
Function: folderInfo()
Description: 根据Qt宏定义确定系统类型，然后再根据不同的类型获取路径的存储情况
Calls:
    1.getLinuxFolderInfo（）
    2.setSavePathSpace（）
Input:
    1.path：目录路径
Output:
Return:
Others:
**************************************************************************************************/
void GetSavePathDialog::folderInfo(QString path)
{
#ifdef Q_OS_LINUX
    setSavePathSpace(getLinuxFolderInfo(path));
#elif Q_OS_WIN
    setSavePathSpace(getWindowsFolderInfo(path));
#endif
}

QString GetSavePathDialog::getSavePathSpace()
{
    return savePathSpace;
}

void GetSavePathDialog::setSavePathSpace(QString tmpSpace)
{
    savePathSpace = tmpSpace;
    emit sendSavePathSpaceChange();
}

QString GetSavePathDialog::getSavePathName()
{
    return savePathName;
}

void GetSavePathDialog::setSavePathName(QString tmpName)
{
    savePathName = tmpName;
    emit sendSavePathNameChange();
}

/**************************************************************************************************
Function: getLinuxFolderInfo()
Description: 调用linux的系统函数获取剩余空间信息
Calls:
Input:
    1.path：目录路径
Output:
Return:
    QString：QString类型带单位的大小，因为这个数据是要直接在QMl界面上显示的
Others:
**************************************************************************************************/
QString GetSavePathDialog::getLinuxFolderInfo(QString path)
{
    struct statfs lv_fs;

    if(statfs(path.toUtf8().data(),&lv_fs) < 0)
    {
        return "";
    }
    else
    {
        double freeSize = lv_fs.f_bfree * lv_fs.f_bsize; // Byte
        if (freeSize > 1024 * 1024 * 1024)//GB
            return QString::number(freeSize / 1024 / 1024 / 1024,'f',1) + "GB";
        else if (freeSize > 1024 * 1024)//MB
            return QString::number(freeSize / 1024 / 1024,'f',1) + "MB";
        else if (freeSize > 1024)//KB
            return QString::number(freeSize/ 1024,'f',1) + "KB";
        else
            return QString::number(freeSize,'f',1) + "B";
    }
}

/**************************************************************************************************
Function: getWindowsFolderInfo()
Description: 获取windows下的存储路径的大小，暂时未实现
Calls:
Input:
    1.path：目录路径
Output:
Return:
    QString：QString类型带单位的大小，因为这个数据是要直接在QMl界面上显示的
Others:
**************************************************************************************************/
QString GetSavePathDialog::getWindowsFolderInfo(QString path)
{
    return "";
}


/**************************************************************************************************
Function: touchSaveFolder()
Description: 根据不同的操作系统类型和配置文件信息，查询存储路径是否存在，不存在则创建路径
Calls:
    1.getMainConfig
    2.mkpath
Input:
Output:
Return:
Others:
**************************************************************************************************/
void GetSavePathDialog::touchSaveFolder()
{
    QDir localConfigDir;
    SettingXMLHandler tmpHandler;
#ifdef Q_OS_LINUX
        QString dirName = tmpHandler.getChildElement(GeneralSettings,"SavePath");
#elif Q_OS_WIN
        QString dirName = tmpHandler.getChildElement(GeneralSettings,"SavePath");
#endif

    //如果路径不存在,则先新建文件夹,通常只会执行一次,即程序初次运行
    if (!localConfigDir.exists(dirName))
    {
        localConfigDir.mkpath(dirName);
    }
}
