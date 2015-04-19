#ifndef DATACONTROLER_H
#define DATACONTROLER_H

#include <QObject>
#include <QStringList>
#include <QVariantList>
#include <QtQml>
#include <QQmlEngine>
#include <QJSEngine>
#include "pdatatype.h"
#include "urlhandler.h"
#include  <QDate>

class DataController : public QObject
{
    Q_OBJECT
public:
    static DataController * getInstance();
    static QObject * pDataCtrlObj(QQmlEngine *engine, QJSEngine *scriptEngine);
    ~DataController();

    void receiveURL(const QString &url);
    Q_INVOKABLE void getSupportToolsList(const QString &url);
    Q_INVOKABLE void analyzeURL(const QString &url);

signals:
    void signalReceiveNewURL(QString url);
    void signalSupportToolsListChanged(QList<int> toolsList);
    void signalFileInfoListChanged(QVariantMap infoList);

public slots:

private slots:
    void analyzeURLDone(QList<TaskFileInfo> infoList);

private:
    explicit DataController(QObject *parent = 0);

private:
    static DataController * dataControler;

};

#endif // DATACONTROLER_H
