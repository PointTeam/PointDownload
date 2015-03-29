#ifndef TASK_H
#define TASK_H

/*!
    任务抽象类，提供各个任务的接口。
    所有的下载任务类应该继承于此类并实现相应的函数，
    所有对于下载任务的操作都由本类定义，各个地方不应该再调用各个任务的具体方法，
    各种下载任务的实现细节只由对应的下载类内部访问，其它模块只通过本类的方法访问某个任务。
*/

#include <QObject>
#include "pdatatype.h"
#include "taskinfo.h"

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = 0);

public slots:
    // 各个任务自己实现的任务控制函数
    virtual void start(const TaskInfo & taskInfo) = 0;  // 开始下载
    virtual void stop(const QString & fileID) = 0;      // 停止下载
    virtual void suspend(const QString & fileID) = 0;
    virtual void resume(const QString & fileID) = 0;
    virtual void finishDownload(const QString & fileID) = 0;
    virtual void deleteTask(const QString & fileID, const bool removeFile) = 0;
    virtual void trashTask(const QString & fileID, const bool removeFile) = 0;

signals:
    void taskItemInfoUpdate(const TaskItemInfo & info);
    void getError(const QString & fileID, const QString & error, PDataType::ToolType toolType);

protected:
    TaskInfo infomation;
};

#endif // TASK_H
