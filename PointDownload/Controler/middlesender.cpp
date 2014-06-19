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

#include "middlesender.h"

MiddleSender::MiddleSender(QObject *parent) :
    QObject(parent)
{
    QTimer * refreshTimer = new QTimer();
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(updateDate()));
    refreshTimer->start(REFRESH_TIMER);

    cpuUsage = 0;
    downSpeed = 0;
    upSpeed = 0;
    diskUsage = 0;
}

double MiddleSender::getCpuUsage()
{
    return cpuUsage;
}

void MiddleSender::setCpuUsage(double usage)
{
    cpuUsage = usage;
    emit sendCpuUsageChange();
}

double MiddleSender::getDownSpeed()
{
    return downSpeed;
}

void MiddleSender::setDownSpeed(double speed)
{
    downSpeed = speed/(REFRESH_TIMER / 1000);//注意返回结果并没有除以时间，只是返回上一次与这次的数据量的差值
    emit sendDownSpeedChange();
}

double MiddleSender::getUpSpeed()
{
    return upSpeed;
}

void MiddleSender::setUpSpeed(double speed)
{
    upSpeed = speed;
    emit sendUpSpeedChange();
}

double MiddleSender::getDiskUsage()
{
    return diskUsage;
}

void MiddleSender::setDiskUsage(double usage)
{
    diskUsage = usage;
    emit sendDiskUsageChange();
}

QString MiddleSender::getDataList()
{
    return dataList;
}

void MiddleSender::setDataList(QString tmpList)
{
    dataList = tmpList;
    emit sendDataListChange();
}

void MiddleSender::updateDate()
{
    GetSpeed geter;
    setCpuUsage(geter.getCPU().toDouble());
    QStringList tmpList = geter.getNWS();
    if (tmpList.count() == 2)
    {
        if (tmpList.at(0).toDouble() == 0)
            setDownSpeed(0.1);//防止分母为0
        else
            setDownSpeed(tmpList.at(0).toDouble());
        setUpSpeed(tmpList.at(1).toDouble());
    }
    else
    {
        setDownSpeed(0.1);
        setUpSpeed(0.1);
    }
    setDiskUsage(geter.getDisk().toDouble());

    QString tmpDataList =
            DataFlow::getData("星期一") + "#"
            + DataFlow::getData("星期二") + "#"
            + DataFlow::getData("星期三") + "#"
            + DataFlow::getData("星期四") + "#"
            + DataFlow::getData("星期五") + "#"
            + DataFlow::getData("星期六") + "#"
            + DataFlow::getData("星期日");
    setDataList(tmpDataList);
}







