#ifndef XWARETASKENTITY_H
#define XWARETASKENTITY_H

#include <QObject>

#include "XwareDataType.h"
#include "xwarepopulateobject.h"
#include "XMLHandler/downloadxmlhandler.h"

class XwareTaskEntity : public QObject
{
    Q_OBJECT
public:
    static XwareTaskEntity *getInstance();

    QString getTaskIdByUrl(QString url);

signals:
    void sRealTimeDataChanged(DownloadingItemInfo);

public slots:

private slots:
    void feedbackDownloadList(QString tasksInfo);

private:
    explicit XwareTaskEntity(QObject *parent = 0);
    void insertTask(QStringList taskInfoStr);
    void clearTaskMap(QMap<QString, XwareTaskInfo*> * taskInfoMap); // free all items of task map to prevent memory leaks
    void constructAndEmitRealTimeData(XwareTaskInfo *taskInfo);
    void updateXMLFile(DownloadingItemInfo info);

private:
    static XwareTaskEntity * xwareTaskEntityInstance;
    QString spliterBtwData;
    QString spliterEnd;
    QString defaultPara;
    QMap<QString, XwareTaskInfo*> * taskInfoMap;
    QMutex * taskInfoMapLocker;
    bool isUpdateXML;
    short updateXMLCounter;
};

#endif // XWARETASKENTITY_H
