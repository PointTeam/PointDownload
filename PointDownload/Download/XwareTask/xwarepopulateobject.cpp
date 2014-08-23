#include "xwarepopulateobject.h"

XwarePopulateObject::XwarePopulateObject(QObject *parent) :
    QObject(parent)
{
    spliterBtwData = "#..#";
    spliterEnd = "#.^_^.#";
    defaultPara = "--";
    taskInfoMap = new QMap<QString, XwareTaskInfo*>;
    taskInfoMapLocker = new QMutex;
}

XwarePopulateObject * XwarePopulateObject::xwarePopulateObject = NULL;
XwarePopulateObject * XwarePopulateObject::getInstance()
{
    if (xwarePopulateObject == NULL)
        xwarePopulateObject = new XwarePopulateObject();
    return xwarePopulateObject;
}

XwarePopulateObject::~XwarePopulateObject()
{
    qDebug()<<"~XwarePopulateObject()  was be called !!";
}

void XwarePopulateObject::addNewDownloadTask(QString url, QString storage, QStringList fileList)
{
    emit sAddNewDownloadTask(url, storage, fileList);
}

void XwarePopulateObject::addNewBTDownloadTask(QString btFilePath, QString storage, QStringList fileList)
{
    emit addNewBTDownloadTask(btFilePath, storage, fileList);
}

void XwarePopulateObject::suspendDownloadingTask(QString tid)
{
    emit sSuspendDownloadingTask(tid);
}

void XwarePopulateObject::resumeDownloadingTask(QString tid)
{
    emit sResumeDownloadingTask(tid);
}

void XwarePopulateObject::entryOfflineChannel(QString tid)
{
    emit sEntryOfflineChannel(tid);
}

void XwarePopulateObject::entryHighSpeedChannel(QString tid)
{
    emit sEntryHighSpeedChannel(tid);
}

// called by javascript
void XwarePopulateObject::setAllBindedPeerIds(QString ids)
{
    // debug
    qDebug()<<"recv sReturnAllBindedPeerIds !!" << ids;

    QStringList list;
    if(! ids.contains(spliterBtwData))
    {
        // debug
        qDebug()<<"ids is empty, return ~~~";
        return;
    }
    {
        list = ids.split(spliterBtwData);
        list.removeLast(); // remove the last empty element
    }

    // debug
    qDebug()<< list << " .....";
    emit sReturnAllBindedPeerIds(list);
}

// emit the singal to javascript to start feedbacking tasks information
void XwarePopulateObject::startFeedbackDloadList()
{
    emit sReflashDownloadList();
}

void XwarePopulateObject::login(QString userName, QString pwd)
{
    qDebug()<<"======== XwarePopulateObject::login ===========";

    // emit this to javascript
    emit sLogin(userName, pwd);
}

void XwarePopulateObject::logout()
{
     qDebug()<<"======== XwarePopulateObject::logout ===========";
    
    // emit this to javascript
    emit sLogout();
}

void XwarePopulateObject::getAllBindedPeerIds()
{
    // emit this to javascript
    emit sGetAllBindedPeerIds();
}

void XwarePopulateObject::justForJSTest(QString testStr)
{
    qDebug()<<"****++++***** javascript test feedback!! ******++++**** ==>" << testStr;
}

void XwarePopulateObject::insertTask(QStringList taskInfoStr)
{
    // the format of "taskInfoStr": tid  taskName  size progress speed  remain  state;

    // check Parameters
    for(int i = 0; i < taskInfoStr.length(); ++i)
    {
        if(taskInfoStr.at(i).trimmed().length() == 0)
        {
            taskInfoStr.replace(i, defaultPara);
        }
    }

    XwareTaskState taskState;
    if(taskInfoStr.at(6).endsWith("dload"))
    {
        taskState = x_dload;
    }
    else if(taskInfoStr.at(6).endsWith("pause"))
    {
        taskState = x_pause;
    }
    else if(taskInfoStr.at(6).endsWith("wait"))
    {
        taskState = x_wait;
    }
    else
    {
        taskState = x_other;
    }

    // the format of "taskInfoStr": tid + taskName + size + progress + speed + remain + state + ;
    XwareTaskInfo* taskInfoStruct = new XwareTaskInfo{taskInfoStr.at(0), taskInfoStr.at(1), taskInfoStr.at(2),
            taskInfoStr.at(3), taskInfoStr.at(4), taskInfoStr.at(5), taskState, taskInfoStr.at(7), taskInfoStr.at(8), taskInfoStr.at(9)};

    // insert task map
    taskInfoMap->insert(taskInfoStr.at(0), taskInfoStruct);

    constructAndEmitRealTimeData(taskInfoStruct);
}

void XwarePopulateObject::constructAndEmitRealTimeData(XwareTaskInfo * taskInfo)
{
    DownloadingItemInfo itemInfo;
    itemInfo.downloadURL = taskInfo->url;
    itemInfo.downloadSpeed = taskInfo->speed;
    itemInfo.uploadSpeed = "0 KB";
    itemInfo.thunderOfflineSpeed = taskInfo->offlineChnlSpeed;
    itemInfo.thunderHightSpeed = taskInfo->highChnlSpeed;
    itemInfo.downloadState = taskInfo->state == x_dload?dlstate_downloading:dlstate_suspend;
    itemInfo.downloadPercent = taskInfo->progress.split("%").at(0).toDouble();

    // emit signal to unified interface and then emited to UI
    emit sRealTimeDataChanged(itemInfo);
}

QString XwarePopulateObject::getTaskIdByUrl(QString url_)
{
    // lock and prevent the task map from being change.
    taskInfoMapLocker->lock();
    QString tid_ = "-1";

    QMap<QString, XwareTaskInfo*>::Iterator it;
    for(it = taskInfoMap->begin(); it != taskInfoMap->end(); it++)
    {
        if(it.value()->url == url_)
        {
             tid_ = it.value()->tid;
        }
    }

    taskInfoMapLocker->unlock();
    return tid_;
}

void XwarePopulateObject::urlParse(QString url)
{
//    qDebug()<<"emit sUrlParse to js";
    emit sUrlParse(url);
}

void XwarePopulateObject::btParse(QString btFilePath)
{
    qDebug()<<"emit sBTParse to js";
    emit sBTParse(btFilePath);
}

// free all items of task map to prevent memory leaks
void XwarePopulateObject::clearTaskMap(QMap<QString, XwareTaskInfo *> *taskInfoMap)
{
    QMap<QString, XwareTaskInfo*>::Iterator it;
    for(it = taskInfoMap->begin(); it != taskInfoMap->end(); it++)
    {
        XwareTaskInfo* tmp = it.value();
        if(tmp != NULL)
        {
            delete tmp;
            tmp = NULL;
        }
    }
    taskInfoMap->clear();
}


void debugMap(QMap<QString, XwareTaskInfo *> *taskInfoMap);  // temp
void XwarePopulateObject::feedbackDownloadList(QString tasksInfo)
{
   if(tasksInfo.trimmed().length() == 0)
    {
        // debug
//        qDebug()<<"it dose not contain any  downloading task information!!";
        return;
    }

    // lock and prevent the task map from being read.
    taskInfoMapLocker->lock();

    // clear the task map
    clearTaskMap(taskInfoMap);

    QStringList taskList = tasksInfo.split(spliterEnd);

    foreach (QString task, taskList)
    {
        QStringList taskInfo = task.split(spliterBtwData);

        if(taskInfo.length() <= 1){continue;}
        insertTask(taskInfo);
    }

    // free the map lock
    taskInfoMapLocker->unlock();

     // debug
//    debugMap(taskInfoMap);
}

void XwarePopulateObject::feedbackURLParse(QString taskInfoList)
{
    // debug
//    QStringList list = taskInfoList.split(spliterEnd);
//    qDebug()<<"XwarePopulateObject::feedbackURLParse"<<list;

    emit sFeedbackURLParse(taskInfoList);
}

void XwarePopulateObject::finishDownload(QString tid)
{
    taskInfoMapLocker->lock();
    emit sFinishDownload(this->taskInfoMap->value(tid)->url);
    taskInfoMapLocker->unlock();
}

QString XwarePopulateObject::getDefaultTaskPara()
{
    return this->defaultPara;
}

QString XwarePopulateObject::getSpliterEnd()
{
    return this->spliterEnd;
}

QString XwarePopulateObject::getSpliterBtwData()
{
    return this->spliterBtwData;
}


// debug , check the task information through Qt console
void debugMap(QMap<QString, XwareTaskInfo*> * taskInfoMap)
{
    // debug
    qDebug()<<"************************************start***************************************************";

    qDebug();
    qDebug()<<"////////////////start//////////////////";
    QMap<QString, XwareTaskInfo*>::Iterator it;
    for(it = taskInfoMap->begin(); it != taskInfoMap->end(); it++)
    {
        qDebug()<<"=========start==============";
        qDebug()<<"tid"<<it.value()->tid;
        qDebug()<<"name"<<it.value()->name;
        qDebug()<<"size"<<it.value()->size;
        qDebug()<<"progress"<<it.value()->progress;
        qDebug()<<"speed"<<it.value()->speed;
        qDebug()<<"remainTime"<<it.value()->remainTime;
        qDebug()<<"state"<<it.value()->state;
        qDebug()<<"url"<<it.value()->url;
        qDebug()<<"offlineChnlSpeed"<<it.value()->offlineChnlSpeed;
        qDebug()<<"highChnlSpeed"<<it.value()->highChnlSpeed;
        qDebug()<<"==========end=============";
    }
    qDebug()<<"/////////////////end/////////////////";
    qDebug();

    // debug
   qDebug()<<"************************************end***************************************************";

}

