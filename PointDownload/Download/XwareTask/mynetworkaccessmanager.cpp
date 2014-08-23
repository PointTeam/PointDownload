#include "mynetworkaccessmanager.h"

MyNetworkAccessManager::MyNetworkAccessManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
}

QNetworkReply *MyNetworkAccessManager::createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &req, QIODevice *outgoingData)
{
    ////////////////////// filter request //////////////////////
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
             qDebug()<<"redefined url ==>"<<url;
         }
     }

    return QNetworkAccessManager::createRequest(op, req_, outgoingData);
}
