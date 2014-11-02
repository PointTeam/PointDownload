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

#include "dataflow.h"

DataFlow::DataFlow(QObject *parent) :
    QObject(parent)
{
}

void DataFlow::touchDataFile()
{
    QFile dataFile(DATAFILE_PATH);
    if (!dataFile.exists())
    {
        if (!dataFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            return;
        }

        QTextStream out(&dataFile);
        out << "0"<< "\n"//起始号数
            << "0" << "\n"//星期一
            << "0" << "\n"//星期二
            << "0" << "\n"//星期三
            << "0" << "\n"//星期四
            << "0" << "\n"//星期五
            << "0" << "\n"//星期六
            << "0" << "\n";//星期天
        dataFile.close();
    }
}

void DataFlow::setStartDate(QString date)
{
    touchDataFile();

    setData(0,date);
}

QString DataFlow::getStartDate()
{
    touchDataFile();

    return getLineData(0);
}

void DataFlow::addData(QString weekDay, QString dataSize)
{
    touchDataFile();

    if (weekDay == "星期一" || weekDay == "Monday")
    {
        QDateTime current_date_time = QDateTime::currentDateTime();
        QString day = current_date_time.toString("d");
        if (day != getStartDate())
        {
            cleanData();
            setStartDate(day);
        }
    }

    qint64 tmpSize = getData(weekDay).toLongLong() + dataSize.toLongLong();

    setData(getWeekIndex(weekDay),QString::number(tmpSize));
}

QString DataFlow::getData(QString weekDay)
{
    touchDataFile();

    return getLineData(getWeekIndex(weekDay));
}

void DataFlow::cleanData()
{
    QFile file(DATAFILE_PATH);

    if (!file.remove())
        qDebug() << "remove data file failed";

    touchDataFile();
}


void DataFlow::setData(int lineIndex, QString data)
{
    touchDataFile();

    QString newData = "";

    QFile file(DATAFILE_PATH);
    if (!file.open(QFile::ReadOnly))
    {
        qDebug()<<"Cound't opend file!";
    }
    else
    {
        QTextStream stream(&file);

        QString lineData = "";
        for (int i = 0; i < 8; i ++)
        {
            lineData = stream.readLine();

            if (i == lineIndex)
            {
                newData += lineData.replace(getLineData(lineIndex),data) + "\n";
            }
            else
                newData += lineData + "\n";
        }

        file.close();
    }

    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        file.write(newData.toUtf8());
        file.close();
    }
}

QString DataFlow::getLineData(int lineIndex)
{
    touchDataFile();

    QFile file(DATAFILE_PATH);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Cound't opend file!";
    }

    QTextStream stream(&file);

    QString lineData;

    for (int i = 0; i < lineIndex + 1; i ++)
        lineData = stream.readLine();

    file.close();

    return lineData;
}

int DataFlow::getWeekIndex(QString weekDay)
{
    if (weekDay == "星期一" || weekDay == "Monday")
        return 1;
    else if (weekDay == "星期二" || weekDay == "Tuesday")
        return 2;
    else if (weekDay == "星期三" || weekDay == "Wednesday")
        return 3;
    else if (weekDay == "星期四" || weekDay == "Thursday")
        return 4;
    else if (weekDay == "星期五" || weekDay == "Friday")
        return 5;
    else if (weekDay == "星期六" || weekDay == "Saturday")
        return 6;
    else
        return 7;
}
