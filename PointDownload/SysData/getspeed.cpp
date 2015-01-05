/***********************************************************************
*PointDownload
*Copyright (C) 2014~2015  PointTeam
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

#include "getspeed.h"

GetSpeed::GetSpeed(QObject *parent) :
    QObject(parent)
{
}

QStringList GetSpeed::getFileInfo(QString fileName)
{
    //QString fileName="/proc/meminfo";
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Cound't opend file!";
    }

    QTextStream stream(&file);
    //QApplication::setOverrideCursor(Qt::WaitCursor);
    QString fileText;
    QStringList list1;
    do
    {
        fileText = stream.readLine();
        list1.append(fileText);
    } while (!fileText.isNull());
    //QApplication::restoreOverrideCursor();
    file.close();
    return list1;
}


double dowNum=0;
double tranNUm=0;
double lasdowNum=0;
double lastranNUm=0;
QStringList GetSpeed::getNWS()
{
    dowNum=0;
    tranNUm=0;
    QString filename ="/proc/net/dev";
    QStringList strList = getFileInfo(filename);

    for(int i=0;i<strList.length();i++)
    {
        if (strList.at(i).contains("ppp", Qt::CaseInsensitive) ||
                strList.at(i).contains("wl", Qt::CaseInsensitive) ||
                strList.at(i).contains("usb", Qt::CaseInsensitive))
        {
            dowNum+=strList.at(i).split(" ",QString::SkipEmptyParts).at(1).toDouble();
            tranNUm+=strList.at(i).split(" ",QString::SkipEmptyParts).at(9).toDouble();
        }
    }


    double dowSpeed=(dowNum-lasdowNum)/1024;    //KB
    double tranSpeed=(tranNUm-lastranNUm)/1024; //KB

    lasdowNum=dowNum;
    lastranNUm=tranNUm;

    QStringList speedList;
    speedList += QString::number(dowSpeed < 100000?dowSpeed:1, 'f', 1);// 防止初始化时原始下载流量影响
    speedList += QString::number(tranSpeed < 100000?dowSpeed:1, 'f', 1);

    return speedList;
}

QStringList GetSpeed::getMem()
{
    QString filename="/proc/meminfo";
    QStringList strList = getFileInfo(filename);

    double totalNum=strList.at(0).split(" ",QString::SkipEmptyParts).at(1).toDouble();

    double freeNum = strList.at(1).split(" ",QString::SkipEmptyParts).at(1).toDouble();

    double bufferNum = strList.at(2).split(" ",QString::SkipEmptyParts).at(1).toDouble();

    double cacheNum = strList.at(3).split(" ",QString::SkipEmptyParts).at(1).toDouble();

    QStringList allList;
    allList += QString::number(totalNum/1024);
    allList += QString::number((freeNum+bufferNum+cacheNum)/1024);
    allList += QString::number(100*(totalNum-freeNum-bufferNum-cacheNum)/totalNum);//**%

    return allList;
}


double totalCPUTime=0;
double lastTotalCPUTime=0;
double idleTime=0;
double lastIdleTime=0;
QString GetSpeed::getCPU()
{
    QString filename="/proc/stat";
    QStringList strList = getFileInfo(filename);

    for(int i=1;i<10;i++)
    {
        totalCPUTime += strList.at(0).split(" ",QString::SkipEmptyParts).at(i).toDouble();
    }
    idleTime=strList.at(0).split(" ",QString::SkipEmptyParts).at(4).toDouble();

    double allCPUTime = totalCPUTime-lastTotalCPUTime;
    double unuseCOUTime = idleTime-lastIdleTime;

    lastTotalCPUTime=totalCPUTime;
    lastIdleTime=idleTime;
    totalCPUTime=0;

    return QString::number(100*(allCPUTime-unuseCOUTime)/allCPUTime, 'f', 1);//精确到两位小数点
}

QString GetSpeed::getDisk()
{
    SettingXMLHandler tmpHandler;
#ifdef Q_OS_LINUX
    return getLinuxFolderInfo(tmpHandler.getChildElement(GeneralSettings,"SavePath"));
#elif Q_OS_WIN
    return getWindowsFolderInfo(tmpHandler.getChildElement(GeneralSettings,"SavePath"));
#endif
}

QString GetSpeed::getLinuxFolderInfo(QString path)
{
    struct statfs lv_fs;

    if(statfs(path.toUtf8().data(),&lv_fs) < 0)
    {
        return "";
    }
    else
    {
        double diskUsage = (double)(lv_fs.f_blocks - lv_fs.f_bfree) / lv_fs.f_blocks;
        return QString::number(100 * diskUsage,'f',1);
    }
}

QString GetSpeed::getWindowsFolderInfo(QString path)
{
    Q_UNUSED(path);

    return "";
}
