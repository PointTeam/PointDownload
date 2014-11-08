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

#include "urlserver.h"

URLServer::URLServer(QObject *parent) :
    QObject(parent)
{
    localServer = new QLocalServer(this);
    connect(localServer, SIGNAL(newConnection()), this, SLOT(serverNewConnectionHandler()));
    connect(XwarePopulateObject::getInstance(), SIGNAL(sFeedbackURLParse(QString)), this, SLOT(taskParseFeedback(QString)));

    XwareParseURLHander = "XwareParseURLOrBT:";
}

URLServer::~URLServer()
{
    localServer->close();
    delete localServer;
}

void URLServer::runServer()
{
    qDebug() << "Run server ok!";

    QLocalServer::removeServer("PointURLServer");
    bool ok = localServer->listen("PointURLServer");
    if (!ok)
        qDebug() << "Add listener faild!";
}


void URLServer::serverNewConnectionHandler()
{
    QLocalSocket * socket = localServer->nextPendingConnection();
    tmp_socket = socket;
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyReadHandler()));
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
}

void URLServer::socketReadyReadHandler()
{
    QLocalSocket * socket = static_cast<QLocalSocket*>(sender());

    if (!socket)
        return ;

    TaskInfo taskInfo(socket);

//    if (taskInfo.toolType == "XwareParseURLHander")
//    {
        // take URL from msg
//        taskParseHandle(urlInfo.split(XwareParseURLHander).at(1));
//        qDebug() << "XwareParseURLHander";
//        return ;
//    }

    //启动下载
    UnifiedInterface::getInstance()->startDownload(taskInfo);

    emit newTaskAdded(taskInfo);                //此信号连接到downloadingsender类
}

void URLServer::taskParseFeedback(QString taskInfo)
{
    tmp_socket->write(taskInfo.toStdString().c_str());
    tmp_socket->flush();
}

void URLServer::taskParseHandle(QString taskInfo)
{
    if(taskInfo == "")
    {
        return;
    }

    // xware not start or not login
    if(XwareWebController::getInstance()->getLoginState() != LoginedAndBinded)
    {
        QString msgType("XwareMsgType");
        QString msgConten("XwareNotStart");
        taskParseFeedback(msgType + XWARE_CONSTANTS_STRUCT.SPLITER_BTWN_DATA + msgConten);
        return;
    }

    // BT
    if(taskInfo.startsWith("file:"))
    {
        XwarePopulateObject::getInstance()->btParse(taskInfo);
    }
    else
    {
        // common  URL
        XwarePopulateObject::getInstance()->urlParse(taskInfo);
    }
}

