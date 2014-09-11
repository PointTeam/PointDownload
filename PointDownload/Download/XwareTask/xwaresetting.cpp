#include "xwaresetting.h"

XwareSetting::XwareSetting(QObject *parent) :
    QObject(parent)
{
}

void XwareSetting::setMaxRunTaskNumber(int max)
{
    QEventLoop loop;
    QNetworkAccessManager nam;
    QNetworkReply * reply = nam.get(QNetworkRequest(QUrl(XWARE_CONSTANTS_STRUCT.URLSTR
                                 + QString("settings?maxRunTaskNumber=")+QString::number(max))));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

void XwareSetting::setDownloadSpeedLimit(int speed)
{
    QEventLoop loop;
    QNetworkAccessManager nam;
    QNetworkReply * reply = nam.get(QNetworkRequest(QUrl(XWARE_CONSTANTS_STRUCT.URLSTR
                                 + QString("settings?downloadSpeedLimit=") + QString::number(speed))));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

void XwareSetting::setUploadSpeedLimit(int speed)
{
    QEventLoop loop;
    QNetworkAccessManager nam;
    QNetworkReply * reply = nam.get(QNetworkRequest(QUrl(XWARE_CONSTANTS_STRUCT.URLSTR
                                 + QString("settings?uploadSpeedLimit=") + QString::number(speed))));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}


