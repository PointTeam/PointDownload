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

    const QString yougetPath = tmpHandler.getChildElement(SettingXMLHandler::YouGetSetting, "ExecutePath");
    QStringList arguments;

    // you-get 路径
    arguments << yougetPath;
    // 覆盖已有文件 - 因为主程序当前没有对此的判断
//    arguments << "-f";
    // 输出目录
    arguments << "-o" << taskInfo.fileSavePath;
    // 设置url参数，这里用解析后的url，以减少重定向开销
    arguments << taskInfo.url;

    qDebug() << "YouGet command line arguments: " << arguments;

    tmpProcess->start("python3", arguments);
}

void YouGetProcess::stopDownload()
{
    tmpProcess->kill();
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
    TaskItemInfo tmpInfo;
    QString currentDataSize = "0";

    int perIndex = gFeedBackInfo.indexOf("%");
    int readIndex = gFeedBackInfo.indexOf("/");

    currentDataSize = gFeedBackInfo.mid(perIndex + 3, readIndex - perIndex - 3);            //已完成大小
    double downloadSize = currentDataSize.toDouble() - lastDataSize.toDouble();                   //MB
    lastDataSize = currentDataSize;
    tmpInfo.taskDLSpeed = (downloadSize * 1024 * 1024) / (UPDATE_INTERVAL / 1000);              //B/S
    tmpInfo.taskProgress = gFeedBackInfo.mid(0,perIndex).toDouble();                        //下载百分比
    tmpInfo.taskState = PDataType::PTaskStateDownloading;
    tmpInfo.fileID = taskInfo.fileID;

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

void YouGetProcess::updateXMLFile(TaskItemInfo info)
{
    DownloadXMLHandler tmpOpera;
    SDownloading tmpStruct = tmpOpera.getDLingNode(info.fileID);
    //计算平均速度，用作优先下载的判断条件
    tmpStruct.averageSpeed = (info.taskProgress * tmpStruct.fileTotalSize//当前完成大小
            - tmpStruct.fileReadySize//上次完成大小
            ) / UPDATE_XML_INTERVAL;
    tmpStruct.fileReadySize = info.taskProgress * tmpStruct.fileTotalSize;
    tmpOpera.updateDLingNode(tmpStruct);
}

void YouGetProcess::getError()
{
    qDebug() << tmpProcess->readAllStandardError();
    emit yougetError(taskInfo.fileID,QString(tmpProcess->readAllStandardError()), PDataType::PToolTypeYouGet);
}

void YouGetProcess::yougetProcessFinish(int ret)
{
    // 由于 you-get 暂停使用的是强制结束进程，所以这里要区分进程的退出是主动退出还是被kill
    int perIndex = gFeedBackInfo.indexOf("%");
    if (gFeedBackInfo.mid(0,perIndex).toDouble() <= 99.9)
        return;

    updateTimer->stop();

    if (!ret)
        emit finishYouGetDownload(taskInfo.fileID);
    else
        emit yougetError(taskInfo.fileID, "YouGet Error: return " + QString::number(ret), PDataType::PToolTypeYouGet);
}
