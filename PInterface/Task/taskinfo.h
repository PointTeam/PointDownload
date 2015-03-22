#ifndef TASKINFO_H
#define TASKINFO_H

#include <QString>
#include <QList>
#include <QUrl>
#include <QIcon>
#include <QDir>
#include <QDebug>
#include <QObject>

#include "taskfileitem.h"
#include "pdatatype.h"

// 任务状态
#define DLSTATE_UNDEF       0
#define DLSTATE_SUSPEND     1   // 暂停
#define DLSTATE_DOWNLOADING 2   // 正在下载
#define DLSTATE_READY       3   // 就绪，当前任务允许下载但总下载任务数已经达到设定上限时，此任务就为就绪状态
#define DLSTATE_DOWNLOADED  4   // 下载完成
#define DLSTATE_CANCELD     5   // 取消下载，当前任务下载了一段时间，或还未开始，但用户点击了“取消下载”，此任务即为取消状态

class TaskInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ taskName)
    Q_PROPERTY(QString rawUrl READ qml_getRawUrl)
    Q_PROPERTY(QString parseUrl READ qml_getRawUrl)
    Q_PROPERTY(QString iconPath READ qml_getIconPath)
    Q_PROPERTY(QString savePath READ qml_getSavePath)
    Q_PROPERTY(PDataType::ToolType toolType READ qml_getToolType)
    Q_PROPERTY(int maxThreads READ qml_getMaxThreads)
    Q_PROPERTY(int maxSpeed READ qml_getMaxSpeed)

public:
    TaskInfo();
    TaskInfo(QIODevice *in);
    TaskInfo(TaskInfo &&taskInfo);
    TaskInfo(const TaskInfo &taskInfo);
    virtual ~TaskInfo();

public:
    QByteArray toQByteArray() const;
    QString fileListString() const;
    QString taskName() const;
    qint64 taskSize() const;

public:
    TaskInfo &operator =(const TaskInfo &what);
    friend QDebug operator <<(QDebug out, const TaskInfo &what);
private:
    friend QDataStream & operator >>(QDataStream &in, TaskInfo &what);
    friend QDataStream & operator <<(QDataStream &out, const TaskInfo &what);

public:
    // for qml
    QString qml_getRawUrl();
    QString qml_getParseUrl();
    QString qml_getIconPath();
    QString qml_getSavePath();
    PDataType::ToolType qml_getToolType();
    int qml_getMaxThreads();
    int qml_getMaxSpeed();

public:
    // 需要序列化/反序列化的成员
    QList<TaskFileItem> fileList;
    QString rawUrl;
    QString parseUrl;
    QString taskIconPath;
    QString savePath;
    PDataType::ToolType toolType;
    int maxThreads;
    int maxSpeed;
};

#endif // TASKINFO_H
