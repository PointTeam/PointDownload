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

#include "yougetprocess.h"

YouGetProcess::YouGetProcess(const TaskInfo &taskInfo, QObject *parent) :
    QObject(parent), taskInfo(taskInfo)
{
    lastDataSize = "0";
    xmlUpdateInterval = 1;

    connect(&updateTimer, SIGNAL(timeout()), this, SLOT(getTimerUpdate()));
}

void YouGetProcess::startDownload()
{
    SettingXMLHandler tmpHandler;

    tmpProcess = new QProcess(0);
    connect(tmpProcess, SIGNAL(finished(int)), tmpProcess, SLOT(deleteLater()));
    connect(tmpProcess, SIGNAL(finished(int)), this, SLOT(yougetProcessFinish(int)));
    connect(tmpProcess, SIGNAL(readyReadStandardOutput()),this,SLOT(getFeedBack()));
    connect(tmpProcess, SIGNAL(readyReadStandardError()), this, SLOT(getError()));
    connect(tmpProcess, SIGNAL(started()), this, SLOT(yougetStarted()));

    const QString yougetPath = tmpHandler.getChildElement(YouGetSetting, "ExecutePath");
    QStringList arguments;

    // you-get 路径
    arguments << yougetPath;
    // 覆盖已有文件 - 因为主程序当前没有对此的判断
//    arguments << "-f";
    // 输出目录
    arguments << "-o" << taskInfo.savePath;
    // 设置url参数，这里用解析后的url，以减少重定向开销
    arguments << taskInfo.parseUrl;

    qDebug() << "YouGet command line arguments: " << arguments;

    tmpProcess->start("python3", arguments);
}

void YouGetProcess::stopDownload()
{
    disconnect(tmpProcess, SIGNAL(finished(int)), this, SLOT(yougetProcessFinish(int)));
    tmpProcess->terminate();
}

void YouGetProcess::yougetStarted()
{
    //进程启动完成后再启动定时器
    updateTimer.start(UPDATE_INTERVAL);
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
    tmpInfo.downloadURL = taskInfo.rawUrl;

    //send to yougettask
    emit updateData(tmpInfo);

    //update xml file
    if (xmlUpdateInterval == UPDATE_XML_INTERVAL)
    {
        xmlUpdateInterval = 1;
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
}

void YouGetProcess::yougetProcessFinish(int ret)
{
    updateTimer.stop();

    if (!ret)
        emit sFinishYouGetDownload(taskInfo.rawUrl);
    else
        emit yougetError(taskInfo.rawUrl, "YouGet Error: return " + QString::number(ret), TOOL_YOUGET);
}
