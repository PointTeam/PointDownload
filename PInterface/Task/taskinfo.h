/**
  Author: sbwtw <sbwtws@gmail.com>
  下载任务的信息结构，用于PointPopup到PointDownload之间的数据传输
*/

#ifndef TASKINFO_H
#define TASKINFO_H

#include <QString>
#include <QList>
#include <QUrl>
#include <QIcon>
#include <QDir>
#include <QDebug>
#include <QDateTime>

#include "taskfileitem.h"

// 使用的下载后端类型
#define TOOL_UNDEF  0   // 未定义
#define TOOL_POINT  1   // Point自己的下载后端，目前支持http协议
#define TOOL_ARIA2  2   // 目前支持大部分下载协议，支持断电续传，支持多线程下载
#define TOOL_XWARE  3   // 迅雷路由固件
#define TOOL_YOUGET 4   // 在线视频下载工具，支持断点续传，下载完成后自动合并视频,支持大部分主流在线视频音乐网站

#define TOOL_XWARE_PARSE 5 // added by Choldrim, used to parse magnet, ftp, ed2k, thunder URL, etc.

// 任务状态
#define DLSTATE_UNDEF       0
#define DLSTATE_SUSPEND     1   // 暂停
#define DLSTATE_DOWNLOADING 2   // 正在下载
#define DLSTATE_READY       3   // 就绪，当前任务允许下载但总下载任务数已经达到设定上限时，此任务就为就绪状态
#define DLSTATE_DOWNLOADED  4   // 下载完成
#define DLSTATE_TRASH       5   // 移动到垃圾箱的下载任务

class TaskInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString rawUrl READ qml_getRawUrl)
    Q_PROPERTY(QString parseUrl READ qml_getParseUrl)
    Q_PROPERTY(QString iconPath READ qml_getIconPath)
    Q_PROPERTY(QString savePath READ qml_getSavePath)
    Q_PROPERTY(QDateTime completeDate READ qml_getCompleteDate)
    Q_PROPERTY(float percentage READ qml_getPercentage)
    Q_PROPERTY(int toolType READ qml_getToolType)
    Q_PROPERTY(int maxThreads READ qml_getMaxThreads)
    Q_PROPERTY(int maxSpeed READ qml_getMaxSpeed)
    Q_PROPERTY(int status READ qml_getTaskState)
    Q_PROPERTY(int size READ size)
    Q_PROPERTY(int speed READ qml_getDownloadSpeedNow NOTIFY downloadSpeedChanged)

public:
    TaskInfo();
    TaskInfo(QIODevice *in);
    TaskInfo(TaskInfo &&taskInfo);
    TaskInfo(const TaskInfo &taskInfo);
    virtual ~TaskInfo();

public:
    QByteArray toQByteArray() const;
    QStringList fileStringList() const;
    QString name() const;
    qint64 size() const;

    // 这些方法是为了代码重构时兼容所用，应该尽量不要使用
    void setToolTypeFromString(const QString &tool);
    void setDownStateFromString(const QString &state);
    Q_INVOKABLE static int convertDownStateToInt(const QString state);
    Q_INVOKABLE static int convertDownloadSpeedToInt(const QString speed);

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
    QDateTime qml_getCompleteDate();
    float qml_getPercentage();
    int qml_getToolType();
    int qml_getMaxThreads();
    int qml_getMaxSpeed();
    int qml_getTaskState();
    int qml_getDownloadSpeedNow();

signals:
    void downloadSpeedChanged();

public:
    // 需要序列化/反序列化的成员
    QList<TaskFileItem> fileList;
    /*
     * because QUrl can not store ed2k, thunder.. protocol
     *  altered QUrl to QString (by Choldrim, 2015.1.2)
    */
    QString rawUrl;
    QString parseUrl;
    QString taskIconPath;
    QString savePath;
    int toolType;
    int maxThreads;
    int maxSpeed;

public:
    // 这些属性应该是属于“下载任务”类的，为了兼容旧代码先写在这里
    QDateTime completeDate;
    float percentage; // ready percentage
    int taskState;
    int downloadSpeedNow;

private:
};

#endif // TASKINFO_H
