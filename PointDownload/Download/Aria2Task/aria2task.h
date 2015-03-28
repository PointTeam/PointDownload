#ifndef ARIA2TASK_H
#define ARIA2TASK_H

#include <QObject>
#include "aria2process.h"
#include "Download/DataType.h"
#include "Download/unifiedinterface.h"
#include "downloadxmlhandler.h"

#include "taskinfo.h"

class Aria2Task : public QObject
{
    Q_OBJECT
public:
    static Aria2Task * getInstance();

    //对正在下载的处理
    void startDownload(TaskInfo *taskInfo);
    void stopDownload(QString URL);
    void suspendDownloading(QString URL);
    void resumeDownloading(QString URL);

signals:
    void sRealTimeData(DownloadingItemInfo info);
    void sAria2Error(QString URL,QString err, int toolType);

public slots:
    void slotFinishDownload(QString URL);

private:
    explicit Aria2Task(QObject *parent = 0);

    TaskInfo *getPrepareInfoFromXML(QString URL);
    void initConnection();
private:
    static Aria2Task * aria2Task;
    //URL,Process
    QMap<QString,Aria2Process *> gProcessMap;

};

#endif // ARIA2TASK_H
