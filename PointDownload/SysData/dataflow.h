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

#ifndef DATAFLOW_H
#define DATAFLOW_H

#include <QObject>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStandardPaths>

const QString DATAFILE_PATH =
        QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.PointConfig/PointDownloadData";
class DataFlow : public QObject
{
    Q_OBJECT
public:
    explicit DataFlow(QObject *parent = 0);

    static void touchDataFile();//探测文件是否存在，不存在则创建
    static void setStartDate(QString date);//设置星期一对应的号数,用于判断是否需要重新清空数据
    static QString getStartDate();
    static void addData(QString weekDay,QString dataSize);//添加统计流量
    static QString getData(QString weekDay);//获取统计流量
    static void cleanData();//清除所有的流量

private:
    static void setData(int lineIndex, QString data);//将对应行改成新的数据
    static QString getLineData(int lineIndex);
    static int getWeekIndex(QString weekDay);

};

#endif // DATAFLOW_H
