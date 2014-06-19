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

#ifndef GETSPEED_H
#define GETSPEED_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include<QStringList>
#include<QDebug>
#ifdef Q_OS_LINUX
    #include <sys/vfs.h>
#endif
#include "XMLHandler/xmloperations.h"

class GetSpeed : public QObject
{
    Q_OBJECT
public:
    explicit GetSpeed(QObject *parent = 0);

    QStringList getNWS();           //read the network speed
    QStringList getMem();           //read memory
    QString getCPU();                   //read CPU state
    QString getDisk();              //get disk usage

private:
    QStringList getFileInfo(QString);  //return the infomation on the file
    QString getLinuxFolderInfo(QString path);
    QString getWindowsFolderInfo(QString path);

};

#endif // GETSPEED_H
