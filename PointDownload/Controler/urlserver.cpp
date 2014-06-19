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
//    qDebug() << "New Connection";

    QLocalSocket * socket = localServer->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyReadHandler()));
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
}

void URLServer::socketReadyReadHandler()
{
    QLocalSocket * socket = static_cast<QLocalSocket*>(sender());
    if (socket)
    {
        QTextStream stream(socket);

        QString urlInfo = stream.readAll();

        //取出数据，调用统一接口启动下载
        QStringList infoList = urlInfo.split("?:?");

        //info: toolsType?:?fileNameList?:?URL?:?RedirectURL?:?iconName?:?savePath?:?threadCount?:?maxSpeed
//        qDebug() << "infoList: "<<infoList;
        if (infoList.count() == 8)
        {
            PrepareDownloadInfo dlInfo;
            if (infoList.at(0) == "Point")
                dlInfo.toolType = Point;
            else if (infoList.at(0) == "youget")
                dlInfo.toolType = youget;
            else
                dlInfo.toolType = aria2;

            dlInfo.fileName = infoList.at(1).split("?:?").at(0).split("@").at(2);
            dlInfo.downloadURL = infoList.at(2);
            dlInfo.redirectURl = infoList.at(3);
            dlInfo.iconPath = infoList.at(4);
            dlInfo.fileSize = infoList.at(1).split("?:?").at(0).split("@").at(1);
            dlInfo.storageDir = infoList.at(5);
            dlInfo.threadCount = infoList.at(6);
            dlInfo.maxSpeed = infoList.at(7).toDouble();

            //启动下载
            UnifiedInterface::getInstance()->getPrepareDownloadInfo(dlInfo);

            //将信息传到界面，在界面新增一个下载项
            //fileSize: B
            //info: dlToolsType?:?fileName?:?URL?:?RedirectURL?:?iconName?:?fileSize?:?savePath?:?threadCount?:?maxSpeed?:?readyPercentage
            urlInfo = infoList.at(0)  + "?:?" + dlInfo.fileName + "?:?" + dlInfo.downloadURL + "?:?"
                    + dlInfo.redirectURl + "?:?" + dlInfo.iconPath + "?:?" + dlInfo.fileSize + "?:?" + dlInfo.storageDir + "?:?"
                    + dlInfo.threadCount + "?:?" + QString::number(dlInfo.maxSpeed) + "?:?0";
            emit getNewURL(urlInfo);                //此信号连接到downloadingsender类
        }
    }
}
