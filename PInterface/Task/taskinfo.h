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

// 使用的下载后端类型
#define TOOL_UNDEF  0   // 未定义
#define TOOL_POINT  1   // Point自己的下载后端，目前支持http协议
#define TOOL_ARIA2  2   // 目前支持大部分下载协议，支持断电续传，支持多线程下载
#define TOOL_XWARE  3   // 迅雷路由固件
#define TOOL_YOUGET 4   // 在线视频下载工具，支持断点续传，下载完成后自动合并视频,支持大部分主流在线视频音乐网站

class TaskInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ taskName)
    Q_PROPERTY(QString rawUrl READ qml_getRawUrl)
    Q_PROPERTY(QString parseUrl READ qml_getRawUrl)
    Q_PROPERTY(QString iconPath READ qml_getIconPath)
    Q_PROPERTY(QString savePath READ qml_getSavePath)
    Q_PROPERTY(QString completeDate READ qml_getCompleteDate)
    Q_PROPERTY(float percentage READ qml_getPercentage)
    Q_PROPERTY(int toolType READ qml_getToolType)
    Q_PROPERTY(int maxThreads READ qml_getMaxThreads)
    Q_PROPERTY(int maxSpeed READ qml_getMaxSpeed)
    Q_PROPERTY(int taskState READ qml_getTaskState)

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
    int taskSize() const;

    // 这些方法是为了代码重构时兼容所用，应该尽量不要使用
    void setToolTypeFromString(const QString &tool);
    void setDownStateFromString(const QString &state);
    QString getToolTypeToString() const;
    QString getDownStateToString() const;
    QString getInfoToString() const;
    QString getDownloadedInfoToString() const;

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
    QString qml_getCompleteDate();
    float qml_getPercentage();
    int qml_getToolType();
    int qml_getMaxThreads();
    int qml_getMaxSpeed();
    int qml_getTaskState();

public:
    // 需要序列化/反序列化的成员
    QList<TaskFileItem> fileList;
    QUrl rawUrl;
    QUrl parseUrl;
    QString taskIconPath;
    QString savePath;
    int toolType;
    int maxThreads;
    int maxSpeed;

public:
    QString completeDate;
    float percentage; // ready percentage
    int taskState;

private:
};

#endif // TASKINFO_H
