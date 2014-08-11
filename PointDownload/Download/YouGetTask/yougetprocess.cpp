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

#include "yougetprocess.h"

YouGetProcess::YouGetProcess(PrepareDownloadInfo info,QObject *parent) :
    QObject(parent),gInfo(info)
{
    lastDataSize = "0";
    xmlUpdateInterval = 0;
}

void YouGetProcess::startDownload()
{
    SettingXMLHandler tmpHandler;
    tmpProcess = new QProcess(0);
    connect(tmpProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(getFeedBack()));
    connect(tmpProcess, SIGNAL(readyReadStandardError()), this, SLOT(getError()));
    connect(tmpProcess, SIGNAL(started()), this, SLOT(yougetStarted()));
    QStringList arguments;

    arguments << tmpHandler.getChildElement(YouGetSetting,"ExecutePath");
    arguments << gInfo.downloadURL;
    tmpProcess->setWorkingDirectory(gInfo.storageDir);
    tmpProcess->start("python3",arguments);
}

void YouGetProcess::stopDownload()
{
    tmpProcess->terminate();
}

void YouGetProcess::yougetStarted()
{
    //进程启动完成后再启动定时器
    updateTimer = new QTimer();
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(getTimerUpdate()));
    updateTimer->start(UPDATE_INTERVAL);
}

void YouGetProcess::getFeedBack()
{
    //直接从命令行传来的东西速度不定，所以放在全局变量中以定时器定时发送数据
    QString outPut = QString(tmpProcess->readAllStandardOutput());
    if (outPut.contains("%"))
        gFeedBackInfo = outPut;
}

void YouGetProcess::getTimerUpdate()
{
    DownloadingItemInfo tmpInfo;
    QString currentDataSize = "0";

    int perIndex = gFeedBackInfo.indexOf("%");
    int readIndex = gFeedBackInfo.indexOf("/");

    currentDataSize = gFeedBackInfo.mid(perIndex + 3, readIndex - perIndex - 3);    //已完成大小
    double downloadSize = currentDataSize.toDouble() - lastDataSize.toDouble();                   //MB
    lastDataSize = currentDataSize;
    tmpInfo.downloadSpeed = QString::number((downloadSize * 1024) / (UPDATE_INTERVAL / 1000),'f',1) + " KB/S";
    tmpInfo.downloadPercent = gFeedBackInfo.mid(0,perIndex).toDouble();                        //下载百分比
    tmpInfo.downloadState = dlstate_downloading;
    tmpInfo.downloadURL = gInfo.downloadURL;

    //下载已完成则结束进程
    if (tmpInfo.downloadPercent == 100)
    {
        updateTimer->stop();
        tmpProcess->terminate();
        this->deleteLater();

        emit sFinishYouGetDownload(gInfo.downloadURL);
    }

    //send to yougettask
    emit updateData(tmpInfo);

    //update xml file
    if (xmlUpdateInterval == UPDATE_XML_INTERVAL)
    {
        xmlUpdateInterval = 0;
        updateXMLFile(tmpInfo);
    }
    else
        xmlUpdateInterval ++;
}

void YouGetProcess::updateXMLFile(DownloadingItemInfo info)
{
    DownloadXMLHandler tmpOpera;
    SDownloading tmpStruct = tmpOpera.getDownloadingNode(info.downloadURL);
    //计算平均速度，用作优先下载的判断条件
    tmpStruct.averageSpeed = QString::number(qint64((info.downloadPercent / 100 * tmpStruct.totalSize.toDouble()//当前完成大小
                                                    - tmpStruct.readySize.toDouble()//上次完成大小
                                                    ) / UPDATE_XML_INTERVAL));
    tmpStruct.readySize = QString::number(qint64(info.downloadPercent / 100 * tmpStruct.totalSize.toLongLong()));
    tmpOpera.writeDownloadingConfigFile(tmpStruct);
}

void YouGetProcess::getError()
{
    qDebug() << tmpProcess->readAllStandardError();
    emit yougetError(gInfo.downloadURL, QString(tmpProcess->readAllStandardError()), youget);
}
