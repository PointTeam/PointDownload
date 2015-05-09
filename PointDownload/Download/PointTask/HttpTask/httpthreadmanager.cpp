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

#include "httpthreadmanager.h"

HttpThreadManager::HttpThreadManager(const TaskInfo &taskInfo, QObject *parent) :
    QObject(parent),taskInfo(taskInfo)
{
    touchDownloadFile();
    initUpdateTimer();
    initData();
}

HttpThreadManager::HttpThreadManager(const QString & fileID,QObject *parent):
    QObject(parent)
{
    taskInfo = getPrepareInfoFromXML(fileID);
    initUpdateTimer();
    initData();
}

void HttpThreadManager::startDownload()
{
    //不存在则先插入xml文件中
    if (!xmlOpera.fileIDExist(taskInfo.fileID, PDataType::PDLTypeDownloading))
    {
        inserToXMLFile(taskInfo);
    }
    else
    {
        //必须要及时改变状态
        changeStateToDownloading(taskInfo.fileID);
    }

    totalDoneSize = xmlOpera.getDLingNode(taskInfo.fileID).fileReadySize;

    //开始下载，全新下载和断点续传操作相同
    QList<SDownloadThread> tmpList = xmlOpera.getDLingNode(taskInfo.fileID).threadList;
    for( int i = 0; i < tmpList.count(); i ++)
    {
        qint64 completed = tmpList.at(i).completedBlockCount;
        qint64 start = tmpList.at(i).startBlockIndex;
        qint64 end = tmpList.at(i).endBlockIndex;

        HttpThread::ThreadData threadData;
        threadData.taskID = taskInfo.fileID;
        threadData.url = taskInfo.url;
        threadData.threadIndex = i;
        threadData.startIndex = start;
        threadData.endIndex = end;
        threadData.completeBytesCount = completed;

        HttpThread * tmpThread = new HttpThread(threadData);
        threadList.append(tmpThread);

        connect(tmpThread,SIGNAL(progressChanged(qint64)),this,SLOT(slotProgressChange(qint64)));
        connect(tmpThread,SIGNAL(finish(int)),this,SLOT(slotThreadFinish(int)));
        connect(tmpThread, SIGNAL(URLChanged(QUrl)), this, SLOT(slotGetNewRedirectURL(QUrl)));
        connect(tmpThread, SIGNAL(threadsIslimited()), this, SLOT(slotThreadsIsLimited()));

        threadList.at(i)->start();                 //启动线程下载
    }

    updateXMLTimer->start(UPDATE_XML_INTERVAL);         //每UPDATE_XML_INTERVAL秒更新一次xml文件，记录下载信息
    updateDataTimer->start(UPDATE_DATA_INTERVAL);       //每秒更新一次下载状态并发送下载信息到界面上
}

void HttpThreadManager::stopDownload()
{
    for (int i = 0; i < threadList.count(); i ++)
    {
        threadList.at(i)->stopDownload();
    }

    threadList.clear();
    receiveBytesPerSecond = 0;
    slotSendDataToUI();
}


void HttpThreadManager::slotSendDataToUI()
{
    TaskItemInfo tmpInfo;
    tmpInfo.fileID = taskInfo.fileID;
    tmpInfo.taskDLSpeed = getDownloadSpeed();
    tmpInfo.taskULSpeed = 0;
    tmpInfo.taskState = PDataType::PTaskStateDownloading;
    tmpInfo.taskProgress = getDownloadPercent();

    emit taskItemInfoUpdate(tmpInfo);
}

void HttpThreadManager::slotUpdataXMLFile()
{
    if( threadList.count() > 0 )
    {
        QList<SDownloadThread> tmpThreadList;                             //下载线程的结构体
        qint64 readySize = 0;
        for( int i = 0; i < threadList.count() ; i ++ )
        {
            qint64 completeBytes = threadList.at(i)->getCompleteBytes() + threadList.at(i)->getDoneByte();
            SDownloadThread sdownlaodThread;
            sdownlaodThread.completedBlockCount = completeBytes;
            tmpThreadList.append( sdownlaodThread );
            readySize += threadList.at(i)->getCompleteBytes() + threadList.at(i)->getDoneByte();                        // 0518
        }

        //平均下载速度
        int oldAverageSpeed = xmlOpera.getDLingNode(taskInfo.fileID).averageSpeed;
        int newAverageSpeed = ( oldAverageSpeed + receiveBytesPerSecond) / 2;

        SDownloading tmpDLingStruct;
        tmpDLingStruct.fileID = taskInfo.fileID;
        tmpDLingStruct.fileReadySize = readySize;
        tmpDLingStruct.taskState = PDataType::PTaskStateDownloading;//如果没有达到间隔时间就被终止，会导致该项状态保持为suspend
        tmpDLingStruct.averageSpeed = newAverageSpeed;
        tmpDLingStruct.threadList.append( tmpThreadList );

        xmlOpera.updateDLingNode(tmpDLingStruct);                //将信息写入到xml文件中
    }
}

void HttpThreadManager::slotRetryDownload()
{
    qDebug() << "[info]: Retry download.............";
    stopDownload();
    startDownload();
}

void HttpThreadManager::slotProgressChange(qint64 doneSize)
{
    mutex.lock();
    totalDoneSize += doneSize;
    receiveBytesPerSecond += doneSize;//在每秒更新信息时再将此变量清空
    mutex.unlock();
}

void HttpThreadManager::slotThreadFinish(int statusCode)
{
    if (statusCode == 0)
    {
        finishThreadCount = 0;
        QTimer::singleShot(RETRY_DOWNLOAD_INTERVAL, this, SLOT(slotRetryDownload()));
        return;
    }

    slotUpdataXMLFile();
    finishThreadCount ++;
    if (finishThreadCount == xmlOpera.getDLingNode(taskInfo.fileID).threadList.count())
    {
        updateDataTimer->stop();
        updateXMLTimer->stop();

        //最后一次更新xml文件
        slotUpdataXMLFile();
        slotSendDataToUI();
        //重命名文件
        QFile downloadFile;
        QDir::setCurrent( xmlOpera.getDLingNode(taskInfo.fileID).fileSavePath);
        downloadFile.rename(taskInfo.fileList.at(0).fileName + POINT_FILE_FLAG, taskInfo.fileList.at(0).fileName);

        //向上层发送已完成下载的信号
        emit taskFinished(taskInfo.fileID);
    }
}

void HttpThreadManager::slotGetNewRedirectURL(QUrl URL)
{
    SDownloading tmpStruct = xmlOpera.getDLingNode(taskInfo.fileID);
    if (tmpStruct.url == URL.toString())
        return;

    tmpStruct.url = URL.toString();

    xmlOpera.updateDLingNode(tmpStruct);

    updateXMLTimer->stop();
    updateDataTimer->stop();

    stopDownload();
    taskInfo = getPrepareInfoFromXML(taskInfo.fileID);
    startDownload();
}

void HttpThreadManager::slotThreadsIsLimited()
{
    if (changeLimited)
        return;
    else
        changeLimited = true;

    updateXMLTimer->stop();
    updateDataTimer->stop();
    stopDownload();

    taskInfo.maxThreads = 1;

    xmlOpera.removeDLingFileNode(taskInfo.fileID);

    startDownload();
}

void HttpThreadManager::touchDownloadFile()
{
    if (!QDir::setCurrent(taskInfo.fileSavePath))
        return;
    QFile * file = new QFile( taskInfo.fileList.at(0).fileName + POINT_FILE_FLAG );
    if( file->open( QIODevice::WriteOnly) )
    {
        file->close();
    }
    else
    {
        qDebug() << "[Error]: Open could not create download-file!\n"<<file->errorString();
    }

    delete file;
}

void HttpThreadManager::initUpdateTimer()
{
    updateXMLTimer = new QTimer();
    connect(updateXMLTimer, SIGNAL(timeout()), this, SLOT(slotUpdataXMLFile()));
    updateDataTimer = new QTimer();
    connect(updateDataTimer, SIGNAL(timeout()), this, SLOT(slotSendDataToUI()));
}

void HttpThreadManager::initData()
{
    finishThreadCount = 0;
    totalDoneSize = 0;
    receiveBytesPerSecond = 0;

    changeLimited = false;
}

void HttpThreadManager::changeStateToDownloading(const QString & fileID)
{
    SDownloading tmpStruct = xmlOpera.getDLingNode(fileID);
    tmpStruct.taskState = PDataType::PTaskStateDownloading;

    xmlOpera.updateDLingNode(tmpStruct);
}

QList<SDownloadThread> HttpThreadManager::splitTask(short threadCount, qint64 size)
{
    QList <SDownloadThread> tmpList;
    qint64 begin = 0;
    qint64 step =0;
    if( 0 == size / threadCount )
        step = size / threadCount;
    else
        step = (qint64)( size / threadCount );
    begin=-step;
    qint64 end = 0;

    for ( short index = 1; index <=  threadCount; index ++ )
    {
        end += step;
        begin +=step;
        if ( index ==  threadCount )
        {
            end = size;
        }

        SDownloadThread sdownloadThread;                            //单个下载线程的结构体
        sdownloadThread.startBlockIndex = begin;                    //线程的起点
        sdownloadThread.endBlockIndex = end-1;                      //线程下载的终点
        sdownloadThread.completedBlockCount = 0;                    //线程完成的字节数
        tmpList.append(sdownloadThread);
    }
    return tmpList;
}

void HttpThreadManager::inserToXMLFile(const TaskInfo &taskInfo)
{
    SDownloading sdownlaoding;
    sdownlaoding.fileID = taskInfo.fileID;
    sdownlaoding.toolType = PDataType::PToolTypePoint;
    sdownlaoding.fileName = taskInfo.getTaskName();                               //文件名
    sdownlaoding.url = taskInfo.url;                                 //url
    sdownlaoding.fileSavePath = taskInfo.fileSavePath;      //文件保存路径
    sdownlaoding.fileTotalSize = taskInfo.getTaskSize();       //总大小
    sdownlaoding.fileReadySize = 0;                           //已经下载字节数
    sdownlaoding.enableUpload = false;                    //是否允许上传
    sdownlaoding.blockCount = 1;
    sdownlaoding.taskState = PDataType::PTaskStateDownloading;                           //状态
    sdownlaoding.averageSpeed = 0;                        //kb/s
    sdownlaoding.taskMaxSpeed = taskInfo.maxSpeed; //最大速度
    sdownlaoding.blockSize = 1;
    sdownlaoding.threadList = splitTask((short)taskInfo.maxThreads, (qint64)taskInfo.getTaskSize());                   //多线程list

    qWarning() << "==>[Info] Inser new task record to config-file:" << xmlOpera.insertDLingNode(sdownlaoding);   //写入到xml文件中
}

TaskInfo HttpThreadManager::getPrepareInfoFromXML(const QString & fileID)
{
    SDownloading ingNode = xmlOpera.getDLingNode(fileID);

    TaskInfo taskInfo;
    taskInfo.fileID = ingNode.fileID;
    taskInfo.url = ingNode.url;
    taskInfo.taskIconPath = "";
    taskInfo.maxSpeed = ingNode.taskMaxSpeed;
    taskInfo.fileSavePath = ingNode.fileSavePath;
    taskInfo.maxThreads = ingNode.threadList.count();
    taskInfo.toolType = PDataType::PToolTypePoint;

    TaskFileInfo fileInfo;
    fileInfo.fileName = ingNode.fileName;
    fileInfo.fileSize = ingNode.fileTotalSize;
    fileInfo.fileType = "File";
    taskInfo.fileList.append(fileInfo);

    return taskInfo;
}

int HttpThreadManager::getDownloadSpeed()
{
    int tmpSpeed = receiveBytesPerSecond / (UPDATE_DATA_INTERVAL / 1000);

    receiveBytesPerSecond = 0;

    return tmpSpeed;
}

double HttpThreadManager::getDownloadPercent()
{
    if (!taskInfo.fileList.at(0).fileSize)
        return 0;

    return (double)totalDoneSize / taskInfo.getTaskSize();
}
