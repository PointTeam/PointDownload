#ifndef MYNETWORKACCESSMANAGER_H
#define MYNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QHostInfo>

// this class use for filtering the request
class MyNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit MyNetworkAccessManager(QObject *parent = 0);

    QNetworkReply *createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0);

signals:

public slots:

};

#endif // MYNETWORKACCESSMANAGER_H
