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
/*****************************************************************************
Date:   2014.3.5~
Description:
    打开文件另存为的对话框，然后将用户的选择从新发送到qml界面上显示
Others:

History:
********************************************************************************/
#ifndef GETSAVEPATHDIALOG_H
#define GETSAVEPATHDIALOG_H

#include <QObject>
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>
#include <sys/vfs.h>
#include "xmloperations.h"

class GetSavePathDialog : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString savePathSpace READ getSavePathSpace() WRITE setSavePathSpace() NOTIFY sendSavePathSpaceChange())
    Q_PROPERTY(QString savePathName READ getSavePathName() WRITE setSavePathName() NOTIFY sendSavePathNameChange())

public:
    explicit GetSavePathDialog(QObject *parent = 0);

    Q_INVOKABLE void getPathName();             //由qml界面调用，打开对话窗口
    Q_INVOKABLE void folderInfo(QString path);  //返回存储路径的空余空间给qml

    //传递到qml界面的get、set函数
    QString getSavePathSpace();
    void setSavePathSpace(QString tmpSpace);
    QString getSavePathName();
    void setSavePathName(QString tmpName);

signals:
    void sendSavePathSpaceChange();
    void sendSavePathNameChange();

private:
    QString savePathSpace;
    QString savePathName;
private:
    QString getLinuxFolderInfo(QString path);   //获取linux下的存储剩余空间
    QString getWindowsFolderInfo(QString path); //获取windows下的存储剩余空间
    void touchSaveFolder();                     //如果路径不存在，则新建路径
};

#endif // GETSAVEPATHDIALOG_H
