#ifndef XWAREPOPULATEOBJECT_H
#define XWAREPOPULATEOBJECT_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QDebug>
#include <QThread>
#include <QMutex>

#include "XwareDataType.h"
#include "xwarewebcontroller.h"
#include "Download/DataType.h"

class XwarePopulateObject : public QObject
{
    Q_OBJECT
public:
    static XwarePopulateObject *getInstance();
    ~XwarePopulateObject();

    // add new task
    void addNewDownloadTask(QString url, QString storage, QStringList fileList);
    void addNewBTDownloadTask(QString btFilePath, QString storage, QStringList fileList);

    // task controller
    void suspendDownloadingTask(QString tid);
    void resumeDownloadingTask(QString tid);
    void removeDownloadingTask(QString tid);
    void entryOfflineChannel(QString tid);
    void entryHighSpeedChannel(QString tid);

//    QString getTaskIdByUrl(QString url_);  // get task id through download URL , -1 will be returned when not find

    void urlParse(QString url);
    void btParse(QString btFilePath);

//    XwareTaskInfo getTaskInfoStructById(QString tid);

    QString getDefaultTaskPara();
    QString getSpliterBtwData();
    QString getSpliterEnd();
signals:
    void sLogin(QString, QString);
    void sLogout();
    void sReturnAllBindedPeerIds(QStringList);
//    void sRealTimeDataChanged(DownloadingItemInfo);
    void sFeedbackURLParse(QString);
    void sFinishDownload(QString);  // QString URL
    void sFeedbackDownloadList(QString);

    // ============================>  emit to javascript <================================= //
    // get all binded machine code(peer id)
    void sJSGetAllBindedPeerIds();

    // reflash the task list
    void sJSReflashDownloadList();

    // add new task
    void sJSAddNewDownloadTask(QString, QString, QStringList);  // param: url, storage, fileList
//    void sAddNewBTDownloadTask(QString, QString, QStringList);  // param: btFilePath, storage, fileList

    // task controller
    void sJSSuspendDownloadingTask(QString);  // param: task id
    void sJSResumeDownloadingTask(QString);  // param: task id
    void sJSRemoveDownloadingTask(QString);  // param: task id
    void sJSEntryOfflineChannel(QString);  // param: task id
    void sJSEntryHighSpeedChannel(QString);  // param: task id

    // parse url , and then js will feedback the url parsed info
    void sJSUrlParse(QString);
    void sJSBTParse(QString);
    // ================================================================================== //

public slots:
    void login(QString userName, QString pwd);  // called by web controller
    void logout();
    void getAllBindedPeerIds();  // called by controller
    void startFeedbackDloadList();  // called by controller

    // =============================>  called by javascript <================================== //
    void justForJSTest(QString testStr);      // tmp js debugger //
    void setAllBindedPeerIds(QString ids);  //  return all bind peer ids
    void feedbackDownloadList(QString tasksInfo);
    void feedbackURLParse(QString taskInfoList);
    void finishDownload(QString tid);
    // ================================================================================== //

private slots:
//    void emitReturnAllBindedPeerIdsSignal();

private:
    explicit XwarePopulateObject(QObject *parent = 0);
    static XwarePopulateObject *xwarePopulateObject;

//    void insertTask(QStringList taskInfoStr);
//    void clearTaskMap(QMap<QString, XwareTaskInfo*> * taskInfoMap); // free all items of task map to prevent memory leaks
//    void constructAndEmitRealTimeData(XwareTaskInfo *taskInfo);

    QString spliterBtwData;
    QString spliterEnd;
    QString defaultPara;
//    QMap<QString, XwareTaskInfo*> * taskInfoMap;
//    QMutex * taskInfoMapLocker;
};

#endif // XWAREPOPULATEOBJECT_H
