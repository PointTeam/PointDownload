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

HttpThreadManager::HttpThreadManager(PrepareDownloadInfo &info,QObject *parent) :
    QObject(parent),gDownloadInfo(info)
{
    touchDownloadFile();
//    initDownloadFile();
    initUpdateTimer();
    initData();
}

HttpThreadManager::HttpThreadManager(QString URL,QObject *parent):
    QObject(parent)
{
    gDownloadInfo = getPrepareInfoFromXML(URL);
//    touchDownloadFile();
//    initDownloadFile();
    initUpdateTimer();
    initData();
}

void HttpThreadManager::startDownload()
{
    //不存在则先插入xml文件中
    if (!xmlOpera.urlExit(gDownloadInfo.downloadURL,"ing"))
    {
        inserToXMLFile(gDownloadInfo);
    }
    else
    {
        //必须要及时改变状态
        changeStateToDownloading(gDownloadInfo.downloadURL);
    }

    //开始下载，全新下载和断点续传操作相同
    QList<SDownloadThread> tmpList = xmlOpera.getDownloadingNode(gDownloadInfo.downloadURL).threadList;
    for( int i = 0; i < tmpList.count(); i ++)
    {
        qint64 completed = (qint64) tmpList.at(i).completedBlockCount.toLongLong(0);
        qint64 start = (qint64) tmpList.at(i).startBlockIndex.toLongLong(0);
        qint64 end = (qint64) tmpList.at(i).endBlockIndex.toLongLong(0);

        HttpThread * tmpThread = new HttpThread( i, start , end, completed, gDownloadInfo.redirectURl);
        threadList.append(tmpThread);

        connect(tmpThread,SIGNAL(progressChanged(qint64)),
                this,SLOT(slotProgressChange(qint64)));
        connect(tmpThread,SIGNAL(finish()),this,SLOT(slotThreadFinish()));
        connect(tmpThread, SIGNAL(URLChanged(QUrl)), this, SLOT(slotGetNewRedirectURL(QUrl)));
        connect(tmpThread, SIGNAL(threadsIslimited()), this, SLOT(slotThreadsIsLimited()));

        threadList.at( i )->start();                 //启动线程下载
    }

    updateXMLTimer->start(UPDATE_XML_INTERVAL);         //每UPDATE_XML_INTERVAL秒更新一次xml文件，记录下载信息
    updateDataTimer->start(UPDATE_DATA_INTERVAL);       //每秒更新一次下载状态并发送下载信息到界面上
}

void HttpThreadManager::stopDownload()
{
    for (int i = 0; i < threadList.count(); i ++)
    {
        threadList.at(i)->stopDownload();
//        threadList.at(i)->deleteLater();
    }

    threadList.clear();
    receiveBytesPerSecond = 0;
    slotSendDataToUI();
}


void HttpThreadManager::slotSendDataToUI()
{
    DownloadingItemInfo tmpInfo;
    tmpInfo.downloadURL = gDownloadInfo.downloadURL;
    tmpInfo.downloadSpeed = getDownloadSpeed();
    tmpInfo.uploadSpeed = "0";
    tmpInfo.downloadState = dlstate_downloading;
    tmpInfo.downloadPercent = getDownloadPercent();

    emit sRealTimeData(tmpInfo);
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
            sdownlaodThread.completedBlockCount = QString::number( completeBytes );
            tmpThreadList.append( sdownlaodThread );
            readySize += threadList.at(i)->getCompleteBytes() + threadList.at(i)->getDoneByte();                        // 0518
        }
        SDownloading sd;
        sd.URL = gDownloadInfo.downloadURL;
        sd.readySize = QString::number( readySize /*getDownloadedSize() */);
        sd.state = DOWNLOADING_STATE;//如果没有达到间隔时间就被终止，会导致该项状态保持为suspend

        //平均下载速度
        QString averageSpeed0 = xmlOpera.getDownloadingNode( gDownloadInfo.downloadURL ).averageSpeed;
        QString speed = QString::number( ( averageSpeed0.toLongLong() + receiveBytesPerSecond) / 2 );
        sd.averageSpeed = speed;

        sd.threadList.append( tmpThreadList );
        xmlOpera.writeDownloadingConfigFile( sd );                //将信息写入到xml文件中
    }
}

void HttpThreadManager::slotProgressChange(qint64 doneSize)
{
    mutex.lock();
    totalDoneSize += doneSize;
    receiveBytesPerSecond += doneSize;//在每秒更新信息时再将此变量清空
    mutex.unlock();
}

void HttpThreadManager::slotThreadFinish()
{
    slotUpdataXMLFile();
    finishThreadCount ++;
    if (finishThreadCount == xmlOpera.getDownloadingNode(gDownloadInfo.downloadURL).threadList.count())
    {
        //最后一次更新xml文件
        slotUpdataXMLFile();
        slotSendDataToUI();
        //重命名文件
        QDir::setCurrent( xmlOpera.getDownloadingNode(gDownloadInfo.downloadURL).savePath);
        downloadFile.rename(gDownloadInfo.fileName + POINT_FILE_FLAG, gDownloadInfo.fileName);
        //向上层发送已完成下载的信号
        emit sDownloadFinish(gDownloadInfo.downloadURL);

        updateDataTimer->stop();
        updateXMLTimer->stop();
    }
}

void HttpThreadManager::slotGetNewRedirectURL(QUrl URL)
{
    updateXMLTimer->stop();
    updateDataTimer->stop();

    SDownloading tmpStruct;
    tmpStruct.URL = gDownloadInfo.downloadURL;
    tmpStruct.redirectRUL = URL.toString();

    xmlOpera.writeDownloadingConfigFile(tmpStruct);

    gDownloadInfo.redirectURl = URL.toString();

    stopDownload();
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

    gDownloadInfo.threadCount = "1";

    xmlOpera.removeDownloadingFileNode(gDownloadInfo.downloadURL);

    startDownload();
}

void HttpThreadManager::touchDownloadFile()
{
    if (!QDir::setCurrent(gDownloadInfo.storageDir))
        return;
    QFile * file = new QFile( gDownloadInfo.fileName + POINT_FILE_FLAG );
    if( file->open( QIODevice::WriteOnly) )
    {
        file->close();
    }
    else
        qDebug() << "open file err"<<file->errorString();

    delete file;
}

//void HttpThreadManager::initDownloadFile()
//{
//    QDir::setCurrent( xmlOpera.getDownloadingNode(gDownloadInfo.downloadURL).savePath);
//    downloadFile.setFileName(gDownloadInfo.fileName + POINT_FILE_FLAG);
//    downloadFile.open( QIODevice::ReadWrite );
//}

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
    totalDoneSize = xmlOpera.getDownloadingNode(gDownloadInfo.downloadURL).readySize.toLongLong();
    receiveBytesPerSecond = 0;

    changeLimited = false;
}

void HttpThreadManager::changeStateToDownloading(QString URL)
{
    SDownloading tmpStruct;
    tmpStruct.URL = URL;
    tmpStruct.state = "dlstate_downloading";

    xmlOpera.writeDownloadingConfigFile(tmpStruct);
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

        SDownloadThread sdownloadThread;                           //单个下载线程的结构体
        sdownloadThread.startBlockIndex = QString::number( begin );//线程的起点
        sdownloadThread.endBlockIndex = QString::number( end-1 );  //线程下载的终点
        sdownloadThread.completedBlockCount = "0";                 //线程完成的字节数
        tmpList.append(sdownloadThread);
    }
    return tmpList;
}

void HttpThreadManager::inserToXMLFile(PrepareDownloadInfo &info)
{
    //获取当前时间
    QDateTime currentTime = QDateTime::currentDateTime();
    QString current_date = currentTime.toString("yyyy:MM:dd:hh:mm:ss");

    SDownloading sdownlaoding;
    sdownlaoding.dlToolsType = "Point";
    sdownlaoding.name = info.fileName;                               //文件名
    sdownlaoding.URL = info.downloadURL;                                 //url
    sdownlaoding.redirectRUL = info.redirectURl;                 //
    sdownlaoding.savePath = info.storageDir;      //文件保存路径
    sdownlaoding.totalSize = info.fileSize;       //总大小
    sdownlaoding.readySize = "0";                           //已经下载字节数
    sdownlaoding.enableUpload = "false";                    //是否允许上传
    sdownlaoding.blockCount = "1";
    sdownlaoding.state = DOWNLOADING_STATE;                           //状态
    sdownlaoding.lastModifyTime = current_date;             //最后修改的时间
    sdownlaoding.averageSpeed = "0";                        //kb/s
    sdownlaoding.jobMaxSpeed = info.maxSpeed; //最大速度
    sdownlaoding.blockSize = "1";
    sdownlaoding.autoOpenFolder = "false";                  //完成后是否自动打开文件夹
    sdownlaoding.iconPath = info.iconPath;
    sdownlaoding.threadList = splitTask(info.threadCount.toShort(), (qint64)info.fileSize.toLongLong());                   //多线程list

    xmlOpera.insertDownloadingNode( sdownlaoding );   //写入到xml文件中
}

PrepareDownloadInfo HttpThreadManager::getPrepareInfoFromXML(QString URL)
{
    SDownloading ingNode = xmlOpera.getDownloadingNode(URL);

    PrepareDownloadInfo tmpInfo;
    tmpInfo.downloadURL = ingNode.URL;
    tmpInfo.fileName = ingNode.name;
    tmpInfo.fileSize = ingNode.totalSize;
    tmpInfo.iconPath = ingNode.iconPath;
    tmpInfo.maxSpeed = ingNode.jobMaxSpeed.toDouble();
    tmpInfo.redirectURl = ingNode.redirectRUL;
    tmpInfo.storageDir = ingNode.savePath;
    tmpInfo.threadCount = QString::number(ingNode.threadList.count());
    tmpInfo.toolType = Point;

    return tmpInfo;
}

QString HttpThreadManager::getDownloadSpeed()
{
    //KB/S
    QString tmpSpeed = QString::number((receiveBytesPerSecond / 1024) / (UPDATE_DATA_INTERVAL / 1000)) + " KB/S";

    receiveBytesPerSecond = 0;

    return tmpSpeed;
}

double HttpThreadManager::getDownloadPercent()
{
    if (gDownloadInfo.fileSize.toDouble())
        return QString::number(100 * totalDoneSize / gDownloadInfo.fileSize.toDouble(),'f',1).toDouble();
    else
        return 0;
}
