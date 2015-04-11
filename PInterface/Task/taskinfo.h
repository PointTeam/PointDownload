#ifndef TASKINFO_H
#define TASKINFO_H

#include <QString>
#include <QList>
#include <QUrl>
#include <QIcon>
#include <QDir>
#include <QDebug>
#include <QObject>

#include "taskfileinfo.h"
#include "pdatatype.h"

class TaskInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString fileID READ pGetFileID)
    Q_PROPERTY(QString url READ pGetUrl)
    Q_PROPERTY(QString taskIconPath READ pGetTaskIconPath)
    Q_PROPERTY(QString fileSavePath READ pGetFileSavePath)
    Q_PROPERTY(PDataType::ToolType toolType READ pGetToolType)
    Q_PROPERTY(int maxThreads READ pGetMaxThreads)
    Q_PROPERTY(int maxSpeed READ pGetMaxSpeed)

public:
    TaskInfo();
    TaskInfo(QIODevice *in);
    TaskInfo(TaskInfo &&taskInfo);
    TaskInfo(const TaskInfo &taskInfo);
    virtual ~TaskInfo();

public:
    QByteArray pToQByteArray() const;
    QString pFileListString() const;
    QString pTaskName() const;
    qint64 pTaskSize() const;

public:
    TaskInfo &operator =(const TaskInfo &what);
    friend QDebug operator <<(QDebug out, const TaskInfo &what);
private:
    friend QDataStream & operator >>(QDataStream &in, TaskInfo &what);
    friend QDataStream & operator <<(QDataStream &out, const TaskInfo &what);

public:
    // for qml
    QString pGetFileID();
    QString pGetUrl();
    QString pGetTaskIconPath();
    QString pGetFileSavePath();
    PDataType::ToolType pGetToolType();
    int pGetMaxThreads();
    int pGetMaxSpeed();

public:
    // 需要序列化/反序列化的成员
    QString fileID;
    QString url;
    QString taskIconPath;
    QString fileSavePath;
    PDataType::ToolType toolType;
    QList<TaskFileInfo> fileList;
    int maxThreads;
    int maxSpeed;

};


#endif // TASKINFO_H
