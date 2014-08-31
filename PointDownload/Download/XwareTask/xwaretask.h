#ifndef XWARETASK_H
#define XWARETASK_H

#include <QObject>
#include "Download/DataType.h"
#include "xwarecontroller.h"
#include "xwarewebcontroller.h"
#include "XMLHandler/settingxmlhandler.h"
#include "xwaretaskentity.h"

class XwareTask : public QObject
{
    Q_OBJECT
public:
    ~XwareTask();
    static XwareTask *getInstance();

    //对正在下载的处理
    void addNewDownload(PrepareDownloadInfo info);
    void addNewBTDownload(PrepareDownloadInfo info);
    void stopDownload(QString URL);
    void suspendDownloading(QString URL);
    void resumeDownloading(QString URL);

    void entryOfflineChannel(QString URL);
    void entryHighSpeedChannel(QString URL);


signals:
    void sRealTimeData(DownloadingItemInfo);
    void sXwareError(QString, QString, DownloadToolsType);
    void sFinishXwareDownload(QString);

public slots:

private slots:
    void updateRealTimeData(DownloadingItemInfo info);

private:
    explicit XwareTask(QObject *parent = 0);

private:
    static XwareTask *xwareTask;

};

#endif // XWARETASK_H
