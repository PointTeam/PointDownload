/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     起点 <88231398@qq.com>
* Maintainer: 起点 <88231398@qq.com>
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

#include "httpthread.h"

//#define SECOND 500  //每秒写入文件一次

#include <qdebug.h>

HttpThread::HttpThread(const ThreadData &threadData)
{
    moveToThread(this);
    threadIndex = threadData.threadIndex;
    startIndex = threadData.startIndex;
    endIndex = threadData.endIndex;
    completeBytes = threadData.completeBytesCount > endIndex - startIndex + 1 ? endIndex - startIndex + 1
                                                                              : threadData.completeBytesCount;
    doneBytes = 0;
    url = QUrl(threadData.url);
}

void HttpThread::run()
{
    if (getStartByte() >= endIndex)
    {
        emit finish(206);
        return;
    }

    manager = new QNetworkAccessManager;
    request = new QNetworkRequest(url);

    QString strData = QString("bytes=%1-%2").arg(QString::number(getStartByte())).arg(QString::number(endIndex));

    request->setRawHeader("Range", strData.toLatin1() );
    request->setRawHeader("Connection", "keep-alive");

    reply = manager->get(*request);
    if(!reply)
    {
        return;
    }

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(managerFnish(QNetworkReply*)));
    connect( reply, SIGNAL( readyRead() ), this, SLOT( writeToFile() ) );

    initDownloadFile();

    this->exec();
}

void HttpThread::initDownloadFile()
{
    QDir::setCurrent( xmlOpera.getDLingNode(taskID).fileSavePath);
    downloadFile.setFileName(xmlOpera.getDLingNode(taskID).fileName + POINT_FILE_FLAG);
    downloadFile.open( QIODevice::ReadWrite );
}

void HttpThread::writeToFile()
{
    if ( reply->bytesAvailable() > 30000 )  //100000
    {
        QByteArray tempArry = reply->readAll();
        lock.lockForWrite();
        downloadFile.seek( getStartByte() + getDoneByte());
        downloadFile.write( tempArry );
        lock.unlock();
        doneBytes += tempArry.size();
        emit this->progressChanged( tempArry.size() );
    }
}

void HttpThread::managerFnish(QNetworkReply *tmpReply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(statusCode == 302)
    {
        QUrl newUrl = reply->header(QNetworkRequest::LocationHeader).toUrl();
        if(newUrl.isValid())
        {
            qDebug()<<"重定向："<<newUrl;
            emit URLChanged( newUrl );
            stopDownload();
            return;
        }
    }
    if (statusCode == 403 || statusCode == 503)
    {
        emit threadsIslimited();
        stopDownload();
        return;
    }

    if (tmpReply->size() > 0)
    {
        QByteArray tempArry = tmpReply->readAll();

        lock.lockForWrite();
        downloadFile.seek( getStartByte() + getDoneByte() );
        downloadFile.write( tempArry );
        lock.unlock();
        doneBytes += tempArry.size();
        emit this->progressChanged( tempArry.size() );
    }

    downloadFile.close();
    emit finish( statusCode );
}

void HttpThread::stopDownload()
{
    downloadFile.close();
    this->quit();
}

qint64 HttpThread::getStartByte()
{
    return startIndex + completeBytes;
}

qint64 HttpThread::getCompleteBytes()
{
    return completeBytes;
}

qint64 HttpThread::getDoneByte()
{
    return doneBytes;
}

HttpThread::~HttpThread()
{
    downloadFile.close();
    reply->deleteLater();
    manager->deleteLater();
}
