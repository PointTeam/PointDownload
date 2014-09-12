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

#ifndef URLSERVER_H
#define URLSERVER_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include "Download/DataType.h"
#include "Download/unifiedinterface.h"
#include "Download/XwareTask/XwareConstants.h"

class URLServer : public QObject
{
    Q_OBJECT
public:
    explicit URLServer(QObject *parent = 0);
    ~URLServer();

    void runServer();
signals:
    void getNewURL(QString info);//info: fileName?:?fileURL?:?fileIconPath

private slots:
    void serverNewConnectionHandler();
    void socketReadyReadHandler();
    void taskParseFeedback(QString taskInfo);

private:
      // taskInfo: margent, ftp, BT file, or other which can not be handle by the popup window
    void taskParseHandle(QString taskInfo);
    QLocalServer * localServer;

    QLocalSocket * tmp_socket;
    QString XwareParseURLHander;

    const QString ITEM_INFO_SPLIT_CHAR = "@:@";
};

#endif // URLSERVER_H
