#ifndef A2IA2TASK_H
#define A2IA2TASK_H

#include <QObject>
#include <QProcess>
#include "Download/unifiedinterface.h"

class A2ia2Task : public QObject
{
    Q_OBJECT
public:
    explicit A2ia2Task(QObject *parent = 0);

    //对正在下载的处理
    void startDownload(PrepareDownloadInfo info);
    void suspendDownloading(QString URL);
    void resumeDownloading(QString URL);

signals:

public slots:

private:

};

#endif // A2IA2TASK_H
