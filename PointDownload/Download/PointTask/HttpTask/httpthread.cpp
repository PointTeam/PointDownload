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

HttpThread::HttpThread(short t, qint64 start, qint64 end, qint64 complete, QUrl u)
{
    moveToThread(this);
    setThreadIndex( t );
    setStartByte( start );
    setEndByte( end );
    setCompeleteBytes( complete>end - start + 1?end - start + 1:complete );
    setDoneByte( 0 );
    setURL( u );
}

void HttpThread::run()
{
    if (getStartByte() >= getEndByte())
    {
        emit finish(206);
        return;
    }

    manager = new QNetworkAccessManager;
    request = new QNetworkRequest( getURL() );


    QString strData = QString( "bytes=%1-%2" ).arg(QString::number(getStartByte())).arg(QString::number(getEndByte()));

    request->setRawHeader("Range", strData.toLatin1() );
    request->setRawHeader("Connection", "keep-alive");

    reply = manager->get( *request );
    if( ! reply )
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
    QDir::setCurrent( xmlOpera.getDownloadingNode(url.toString()).savePath);
    downloadFile.setFileName(xmlOpera.getDownloadingNode(url.toString()).name + POINT_FILE_FLAG);
    downloadFile.open( QIODevice::ReadWrite );
}

void HttpThread::closeDownloadFile()
{
    downloadFile.close();
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
        setDoneByte( getDoneByte() + tempArry.size() );
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
        }
    }
    if (statusCode == 403 || statusCode == 503)
    {
        emit threadsIslimited();
    }

    if (tmpReply->size() > 0)
    {
        QByteArray tempArry = tmpReply->readAll();

        lock.lockForWrite();
        downloadFile.seek( getStartByte() + getDoneByte() );
        downloadFile.write( tempArry );
        lock.unlock();
        setDoneByte( getDoneByte() + tempArry.size() );
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



/*****start ** getter &s setter *********************************************/
QUrl HttpThread::getURL()
{
    return url;
}
void HttpThread::setURL(QUrl u)
{
    this->url = u;
}

short HttpThread::getThreadIndex()
{
    return ThreadIndex;
}
void HttpThread::setThreadIndex(short t)
{
    this->ThreadIndex = t;
}

qint64 HttpThread::getStartByte()
{
    return startByte + getCompleteBytes() ;
}
void HttpThread::setStartByte(qint64 s)
{
    this->startByte = s;
}

qint64 HttpThread::getEndByte()
{
    return endByte;
}
void HttpThread::setEndByte(qint64 e)
{
    this->endByte = e;
}

qint64 HttpThread::getCompleteBytes()
{
    return completeBytes;
}
void HttpThread::setCompeleteBytes(qint64 c)
{
    this->completeBytes = c;
}

qint64 HttpThread::getDoneByte()
{
    return doneBytes;
}
void HttpThread::setDoneByte(qint64 d)
{
    this->doneBytes = d;
}
/*****end  ** getter &s setter **********************************************/

HttpThread::~HttpThread()
{
    downloadFile.close();
    reply->deleteLater();
    manager->deleteLater();
}
