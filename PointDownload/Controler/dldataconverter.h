#ifndef DLDATACONVERTER_H
#define DLDATACONVERTER_H

#include <QObject>
#include <QTimer>
#include <QQmlEngine>
#include "Download/unifiedinterface.h"
#include "urlserver.h"

class DLDataConverter : public QObject
{
    Q_OBJECT
public:
    static DLDataConverter * getInstance();
    static QObject * dataObj(QQmlEngine *engine, QJSEngine *scriptEngine);
    //qml中能直接调用此方法
    Q_INVOKABLE void controlItem(const QString &dtype, const QString &otype, QString URL);//dtype:DownloadType otype:OperationType
    Q_INVOKABLE void suspendAllDownloading();
    Q_INVOKABLE void resumeAllDownloading();

signals:
    void taskAdded(TaskInfo *taskInfo);                 // 添加任务到列表
    void taskInfoChange(TaskInfo *taskInfo);            // 任务信息改变，下载速度等
    void taskComplete(TaskInfo *taskInfo);              // 任务完成
    void taskMoveToTrash(TaskInfo *taskInfo);           // 移动到垃圾箱
    void taskDelete(TaskInfo *taskInfo);                // 删除任务
    void taskRestart(TaskInfo *taskInfo);

    void taskCompleted(const QString& infoString);
    void taskRemoved(const QString& infoString);
    //dlState,文件状态 , "dlstate_downloading" 或者是 "dlstate_suspend",经常更新
    void sDLStateChange(QString dlURL, int dlState);
    void sThunderOfflineSpeedChange(QString dlURL, QString offlineSpeed);
    void sThunderHightSpeedChange(QString dlURL, QString hightSpeed);

    //控制反馈
    void sControlFeedback(QString dlType, QString dlURL, QString operationType, bool result);


    //通知界面更新下载项列表的排列
    void sRefreshDownloadingItem();
public slots:
    //用于接收统一接口类信号的接收
    //为列表面板添加项
    void addTaskItem(TaskInfo *taskInfo);

    void slotGetDownloadingInfo(DownloadingItemInfo infoList);
    //操作返回值
    void slotGetContrlFeedback(DownloadType dtype,OperationType otype, QString URL,bool result);

    void initURLServer();

    TaskInfo *tmp_searchTaskByUrl(const QString &url);

    void stopTask(const QString &url);
    void startTask(const QString &url);
    void moveToTrashTask(const QString &url);
    void removeTask(const QString &url);
    void restartTask(const QString &url);

private:
    explicit DLDataConverter(QObject *parent = 0);

    void initConnection();
private:
    static DLDataConverter * dlDataConverter;

private:
    QList<TaskInfo*> taskList;      // 当前下载任务列表
};
#endif // DLDATACONVERTER_H
