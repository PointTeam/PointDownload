#ifndef TASK_H
#define TASK_H

/*!
    任务抽象类，提供各个任务的接口。
    所有的下载任务类应该继承于此类并实现相应的函数，
    所有对于下载任务的操作都由本类定义，各个地方不应该再调用各个任务的具体方法，
    各种下载任务的实现细节只由对应的下载类内部访问，其它模块只通过本类的方法访问某个任务。
*/

#include <QObject>

#include "taskinfo.h"

// 定义下载任务可能出错的错误号
#define TERROR_UNDEF        0
#define TERROR_UGET_UDEF    1       // youget任务的未定义错误

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = 0);

public slots:
    // 各个任务自己实现的任务控制函数
    virtual void start() = 0;                   // 开始下载
    virtual void stop() = 0;                    // 停止下载
    virtual void remove(bool removeFile) = 0;   // 删除任务 removeFile 是否删除文件

public:
    // 完成百分比
    float completePercent() const;
    // 完成百分比，返回 [xx.xx%] 这样的字串
    const QString completePercentString() const;
    // 当前下载速度，以字节数计
    virtual int downloadBytesSpeed() const = 0;
    // 当前下载速度， xxB/s xxxKB/s xx.xxMB/s
    const QString downloadBytesSpeedString();
    // 输出/显示错误信息
    void dumpErrorMessage(const QString &errorStr) const;

signals:
    void onTaskCompleted();
    void onTaskError(int taskErrorCode);

protected:
    TaskInfo infomation;
};

#endif // TASK_H
