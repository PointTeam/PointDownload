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

#include "mynetworkaccessmanager.h"

MyNetworkAccessManager * MyNetworkAccessManager::networkAccessManager = NULL;
MyNetworkAccessManager::MyNetworkAccessManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
}

MyNetworkAccessManager *MyNetworkAccessManager::getInstance()
{
    if(networkAccessManager == NULL)
    {
        networkAccessManager = new MyNetworkAccessManager();
    }
    return networkAccessManager;
}

QNetworkReply *MyNetworkAccessManager::createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &req, QIODevice *outgoingData)
{
    // ================ filter request ================ //
    QNetworkRequest req_ = req;
    QUrl url = req_.url();
     if(url.host() == "homecloud.yuancheng.xunlei.com")
     {
         if(url.fileName() == "bind")
         {
             QString urlStr = url.toString();

             // add machine name to request
             QString boxNameReg = "boxName=";
             int index = url.toString().indexOf(boxNameReg) + boxNameReg.length();
             urlStr.insert(index, QHostInfo::localHostName());

             // add the tag to bind request
             url = QUrl(urlStr + "&ct=0");

             // chang
             req_.setUrl(url);
             if(XWARE_CONSTANTS_STRUCT.DEBUG)
                qDebug()<<"redefined url ==>"<<url;
         }
     }

    return QNetworkAccessManager::createRequest(op, req_, outgoingData);
}
