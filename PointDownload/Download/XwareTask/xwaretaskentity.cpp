#include "xwaretaskentity.h"

#define UPDATE_XML_INTERVAL 4

XwareTaskEntity * XwareTaskEntity::xwareTaskEntityInstance = NULL;
XwareTaskEntity::XwareTaskEntity(QObject *parent) :
    QObject(parent)
{
    spliterBtwData = XWARE_CONSTANTS_STRUCT.spliterBtwData;
    spliterEnd =  XWARE_CONSTANTS_STRUCT.spliterEnd;
    defaultPara = XWARE_CONSTANTS_STRUCT.defaultPara;
    taskInfoMap = new QMap<QString, XwareTaskInfo*>();
    taskInfoMapLocker = new QMutex();
    isUpdateXML = false;
    updateXMLCounter = 1;

    connect(XwarePopulateObject::getInstance(), SIGNAL(sFeedbackDownloadList(QString)),
            this, SLOT(feedbackDownloadList(QString)));
}

XwareTaskEntity *XwareTaskEntity::getInstance()
{
    if (xwareTaskEntityInstance == NULL)
        xwareTaskEntityInstance = new XwareTaskEntity();
    return xwareTaskEntityInstance;
}

QString XwareTaskEntity::getTaskIdByUrl(QString url)
{
    // lock and prevent the task map from being change.
    taskInfoMapLocker->lock();
    QString tid = "-1";

    QMap<QString, XwareTaskInfo*>::Iterator it;
    for(it = taskInfoMap->begin(); it != taskInfoMap->end(); it++)
    {
        if(it.value()->url == url)
        {
             tid = it.value()->tid;
        }
    }

    taskInfoMapLocker->unlock();
    return tid;
}


void debugMap(QMap<QString, XwareTaskInfo *> *taskInfoMap);  // temp
void XwareTaskEntity::feedbackDownloadList(QString tasksInfo)
{
   if(tasksInfo.trimmed().length() == 0)
    {
        // debug
        //qDebug()<<"it dose not contain any  downloading task information!!";
        return;
    }

   //update xml file
   if (updateXMLCounter == UPDATE_XML_INTERVAL)
   {
       isUpdateXML = true;
       updateXMLCounter = 1;
   }
   else
   {
       isUpdateXML = false;
       ++updateXMLCounter;
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
    //debugMap(taskInfoMap);
}

void XwareTaskEntity::insertTask(QStringList taskInfoStr)
{
    // the format of "taskInfoStr": tid  taskName  size progress speed  remain  state highChannelSpeed offlineChannelSpeed;

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

    // the format of "taskInfoStr": tid + taskName + size + progress + speed + remain + state + highChannelSpeed + offlineChannelSpeed;
    XwareTaskInfo* taskInfoStruct = new XwareTaskInfo{taskInfoStr.at(0), taskInfoStr.at(1), taskInfoStr.at(2),
            taskInfoStr.at(3), taskInfoStr.at(4), taskInfoStr.at(5), taskState, taskInfoStr.at(7), taskInfoStr.at(8), taskInfoStr.at(9)};

    // insert task map
    taskInfoMap->insert(taskInfoStr.at(0), taskInfoStruct);

    constructAndEmitRealTimeData(taskInfoStruct);
}


// free all items of task map to prevent memory leaks
void XwareTaskEntity::clearTaskMap(QMap<QString, XwareTaskInfo *> *taskInfoMap)
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


void XwareTaskEntity::constructAndEmitRealTimeData(XwareTaskInfo * taskInfo)
{
    DownloadingItemInfo itemInfo;
    itemInfo.downloadURL = taskInfo->url;
    itemInfo.downloadSpeed = taskInfo->speed;
    itemInfo.uploadSpeed = "0 KB";
    itemInfo.thunderOfflineSpeed = taskInfo->offlineChnlSpeed;
    itemInfo.thunderHightSpeed = taskInfo->highChnlSpeed;
    itemInfo.downloadState = taskInfo->state == x_dload?dlstate_downloading:dlstate_suspend;
    itemInfo.downloadPercent = taskInfo->progress.split("%").at(0).toDouble();

    if(isUpdateXML)
    {
        updateXMLFile(itemInfo);
    }

    // emit signal to xware task
    emit sRealTimeDataChanged(itemInfo);
}

void XwareTaskEntity::updateXMLFile(DownloadingItemInfo info)
{
    DownloadXMLHandler tmpOpera;
    SDownloading tmpStruct = tmpOpera.getDownloadingNode(info.downloadURL);
    //计算平均速度，用作优先下载的判断条件
    tmpStruct.averageSpeed = QString::number(qint64((info.downloadPercent / 100 * tmpStruct.totalSize.toDouble()//当前完成大小
                                                    - tmpStruct.readySize.toDouble()//上次完成大小
                                                    ) / UPDATE_XML_INTERVAL));
    tmpStruct.readySize = QString::number(qint64(info.downloadPercent / 100 * tmpStruct.totalSize.toLongLong()));

    tmpOpera.writeDownloadingConfigFile(tmpStruct);
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



