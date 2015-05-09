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

HttpThread::HttpThread(const ThreadData &data):
    threadData(data)
{
    threadIndex = data.threadIndex;
    qint64 startIndex = data.startIndex;
    qint64  endIndex = data.endIndex;
    completeBytes = data.completeBytesCount > endIndex - startIndex + 1 ? endIndex - startIndex + 1
                                                                              : data.completeBytesCount;
    doneBytes = 0;
    url = QUrl(data.url);
}

void HttpThread::run()
{
    if (getStartByte() >= threadData.endIndex)
    {
        emit finish(206);
        return;
    }

    QNetworkAccessManager * manager = new QNetworkAccessManager;

    QString strData = QString("bytes=%1-%2").arg(QString::number(getStartByte())).arg(QString::number(threadData.endIndex));

    QNetworkRequest request(url);
    request.setRawHeader("Range", strData.toLatin1() );
    request.setRawHeader("Connection", "keep-alive");

    QNetworkReply * reply = manager->get(request);
    if(!reply)
    {
        return;
    }

    FileWriter * writer = new FileWriter(threadData, reply);
    writer->setParent(manager);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(managerFnish(QNetworkReply*)));
    connect(reply, SIGNAL(readyRead()), writer, SLOT(writeToFile()));
    connect(writer, SIGNAL(progressChanged(qint64)), this, SLOT(slotProgressChanged(qint64)));

    this->exec();
}

void HttpThread::managerFnish(QNetworkReply *tmpReply)
{
    int statusCode = tmpReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(statusCode == 302)
    {
        QUrl newUrl = tmpReply->header(QNetworkRequest::LocationHeader).toUrl();
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
        //write last data
        DownloadXMLHandler tmpHandler;
        QString savePath = tmpHandler.getDLingNode(threadData.taskID).fileSavePath;
        QString filename = tmpHandler.getDLingNode(threadData.taskID).fileName + POINT_FILE_FLAG;
        QDir::setCurrent(savePath);

        QFile downloadFile(filename);
        if (!downloadFile.open(QIODevice::ReadWrite))
            return;

        QReadWriteLock lock;
        QByteArray tempArry = tmpReply->readAll();
        lock.lockForWrite();
        downloadFile.seek(getStartByte() + doneBytes);
        downloadFile.write(tempArry);
        lock.unlock();
        doneBytes += tempArry.size();
        emit this->progressChanged(tempArry.size());

        downloadFile.close();
    }

    emit finish(statusCode);
}

void HttpThread::slotProgressChanged(qint64 value)
{
    doneBytes += value;
    emit this->progressChanged(value);
}

void HttpThread::stopDownload()
{
    this->quit();
}

qint64 HttpThread::getStartByte()
{
    return threadData.startIndex + completeBytes;
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

}

FileWriter::FileWriter(const HttpThread::ThreadData &data, QNetworkReply * reply):
    networkReply(reply)
{
    DownloadXMLHandler tmpHandler;
    savePath = tmpHandler.getDLingNode(data.taskID).fileSavePath;
    filename = tmpHandler.getDLingNode(data.taskID).fileName + POINT_FILE_FLAG;
    QDir::setCurrent(savePath);

    startIndex = data.startIndex;
    endIndex = data.endIndex;
    doneBytes = 0;
    completeBytes = data.completeBytesCount > endIndex - startIndex + 1 ? endIndex - startIndex + 1
                                                                              : data.completeBytesCount;
}

void FileWriter::writeToFile()
{
    QFile downloadFile(filename);
    if (!downloadFile.open(QIODevice::ReadWrite))
        return;

    if ( networkReply->bytesAvailable() > 30000 )  //100000
    {
        QReadWriteLock lock;
        QByteArray tempArry = networkReply->readAll();
        lock.lockForWrite();
        downloadFile.seek(getStartByte() + doneBytes);
        downloadFile.write(tempArry);
        lock.unlock();
        doneBytes += tempArry.size();
        emit this->progressChanged( tempArry.size() );
    }

    downloadFile.close();
}

qint64 FileWriter::getStartByte()
{
    return startIndex + completeBytes;
}
