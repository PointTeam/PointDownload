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

    QLocalServer::removeServer("PointURLServer");
    localServer = new QLocalServer(this);
    if (!localServer->listen("PointURLServer"))
        qWarning() << "localServer listen error!" << localServer->errorString();

    connect(localServer, SIGNAL(newConnection()), this, SLOT(serverNewConnectionHandler()));

    connect(XwarePopulateObject::getInstance(), SIGNAL(sFeedbackURLParse(TaskInfo)),
            this, SLOT(taskParseFeedback(TaskInfo)));
}

URLServer::~URLServer()
{
    localServer->close();
    delete localServer;
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
    TaskInfo taskInfo(socket);

    qDebug() << taskInfo;

    if (TOOL_XWARE_PARSE == taskInfo.toolType)
    {
         // take URL from msg
        taskParseHandle(taskInfo.rawUrl);
        qDebug() << "Xware is parsing the URL";
        return ;
    }

    //启动下载
    UnifiedInterface::getInstance()->startDownload(taskInfo);

    emit newTaskAdded(taskInfo);                //此信号连接到downloadingsender类
}

void URLServer::taskParseFeedback(TaskInfo taskInfo)
{
    taskInfo.rawUrl = tmp_url;
    taskInfo.parseUrl = tmp_url;
    qDebug()<<taskInfo;
    tmp_socket->write(taskInfo.toQByteArray());
    tmp_socket->flush();
}

void URLServer::taskParseHandle(QString url)
{
    if(url.isEmpty())
    {
        return;
    }

    // xware not start or not login
    if(XwareWebController::getInstance()->getLoginState() != LoginedAndBinded)
    {
        qDebug()<<"Can not parsing URL, Thunder is not at the login state.";
        return;
    }

    tmp_url = url;
     XwarePopulateObject::getInstance()->urlParse(url);
}

