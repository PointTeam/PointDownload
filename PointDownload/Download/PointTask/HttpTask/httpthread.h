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

#ifndef HTTPTHREAD_H
#define HTTPTHREAD_H

#include <QUrl>
#include <QFile>
#include <qdir.h>
#include <QThread>
#include <qtimer.h>
#include <QEventLoop>
#include "QByteArray"
#include <QReadWriteLock>
#include <qmessagebox.h>
#include <qfileinfo.h>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>


class HttpThread : public QThread
{
    Q_OBJECT
public:
    HttpThread(short ThreadIndex, qint64 startByte, qint64 endByte, qint64 completeByte, QUrl url, QFile *file);
    void run();
    void stopDownload();

    QUrl getURL();
    void setURL(QUrl);
    short getThreadIndex();
    void setThreadIndex(short);
    qint64 getStartByte();
    void setStartByte(qint64);
    qint64 getEndByte();
    void setEndByte(qint64);
    qint64 getCompleteBytes();
    void setCompeleteBytes(qint64);
    qint64 getDoneByte();
    void setDoneByte(qint64);


private:
    QUrl url;
    short ThreadIndex;
    qint64 startByte;
    qint64 endByte;
    qint64 completeBytes;
    qint64 doneBytes;

    QFile *file;                                        //timer to write
    QReadWriteLock lock;
    QNetworkReply * reply;
    QNetworkRequest * request;
    QNetworkAccessManager * manager;

signals:
    void URLChanged(QUrl URL);
    void statusCodeChanged(int code);
    void progressChanged(qint64);
    void finish();

public slots:
    void writeToFile();
    void managerFnish(QNetworkReply * tmpReply);
};

#endif // HTTPTHREAD_H
