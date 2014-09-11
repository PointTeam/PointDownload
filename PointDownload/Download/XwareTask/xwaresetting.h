#ifndef XWARESETTING_H
#define XWARESETTING_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>

#include "XwareConstants.h"

class XwareSetting : public QObject
{
    Q_OBJECT
public:
    static void setMaxRunTaskNumber(int max);
    static void setDownloadSpeedLimit(int speed);
    static void setUploadSpeedLimit(int speed);

signals:

public slots:

private:
    explicit XwareSetting(QObject *parent = 0);
};

#endif // XWARESETTING_H
