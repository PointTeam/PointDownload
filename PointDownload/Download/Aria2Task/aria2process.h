#ifndef ARIA2PROCESS_H
#define ARIA2PROCESS_H

#include <QObject>
#include <QProcess>
#include <QTimer>
#include <QDebug>
#include "Download/DataType.h"
#include "downloadxmlhandler.h"
#include "settingxmlhandler.h"

class Aria2Process : public QObject
{
    Q_OBJECT
public:
    const int UPDATE_XML_INTERVAL = 3;//second
    const int UPDATE_INTERVAL = 1000;
    explicit Aria2Process(PrepareDownloadInfo info, QObject *parent = 0);

    void startDownload();
    void stopDownload();
signals:
    void updateData(DownloadingItemInfo info);
    void aria2Error(QString URL,QString err, DownloadToolsType toolType);
    void sFinishAria2Download(QString URL);

private slots:
    void aria2Started();
    void getFeedBack();
    void getTimerUpdate();
    void updateXMLFile(DownloadingItemInfo info);
    void getError();

private:
    QString analysisFeedBackSpeed(QString data);
private:
    QString gFeedBackInfo;
    PrepareDownloadInfo gInfo;
    QProcess * tmpProcess;
    QString lastDataSize;
    QTimer * updateTimer;
    short xmlUpdateInterval;

};

#endif // ARIA2PROCESS_H
