/***********************************************************************
*PointDownload
*Copyright (C) 2014~2015  PointTeam
*
* Author:     Choldrim <choldrim@foxmail.com>
* Maintainer: Choldrim <choldrim@foxmail.com>
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

#ifndef MYNETWORKACCESSMANAGER_H
#define MYNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QHostInfo>

#include "XwareConstants.h"

// this class use for filtering the request
class MyNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    static MyNetworkAccessManager * getInstance();

    QNetworkReply *createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0);

signals:

public slots:

private:
    explicit MyNetworkAccessManager(QObject *parent = 0);

private:
    static MyNetworkAccessManager * networkAccessManager;

};

#endif // MYNETWORKACCESSMANAGER_H
