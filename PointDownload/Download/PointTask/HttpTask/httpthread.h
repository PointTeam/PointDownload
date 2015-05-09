/***********************************************************************
*PointDownload
*Copyright (C) 2014~2015  PointTeam
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
#include "downloadxmlhandler.h"
#include <QDebug>

class HttpThread : public QThread
{
    Q_OBJECT
public:
    struct ThreadData
    {
        QString taskID;
        QString url;
        short threadIndex;
        qint64 startIndex;
        qint64 endIndex;
        qint64 completeBytesCount;
    };

    HttpThread(const ThreadData &data);
    ~HttpThread();
    void run();
    void stopDownload();

    qint64 getStartByte();
    qint64 getCompleteBytes();
    qint64 getDoneByte();

signals:
    void URLChanged(QUrl URL);
    void threadsIslimited();
    void progressChanged(qint64);
    void finish(int statusCode);

public slots:
    void managerFnish(QNetworkReply * tmpReply);
    void slotProgressChanged(qint64 value);

private:
    ThreadData threadData;
    QString taskID;
    QUrl url;
    short threadIndex;
    qint64 completeBytes;
    qint64 doneBytes;

    const QString POINT_FILE_FLAG = ".Point";
};

class FileWriter : public QObject
{
    Q_OBJECT
public:
    FileWriter(const HttpThread::ThreadData &data, QNetworkReply * reply);

public slots:
    void writeToFile();

signals:
    void progressChanged(qint64 value);

private:
    qint64 getStartByte();

private:
    qint64 startIndex;
    qint64 endIndex;
    qint64 completeBytes;
    qint64 doneBytes;

    QNetworkReply * networkReply;
    QString savePath;
    QString filename;

    const QString POINT_FILE_FLAG = ".Point";
};

#endif // HTTPTHREAD_H
