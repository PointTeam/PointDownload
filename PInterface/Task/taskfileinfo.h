#ifndef TASKFILEINFO_H
#define TASKFILEINFO_H

#include <QObject>
#include <QString>
#include <QDataStream>
#include <QDebug>

class TaskFileInfo
{

public:
    explicit TaskFileInfo();

    friend QDataStream &operator >>(QDataStream &in, TaskFileInfo &what);
    friend QDataStream &operator <<(QDataStream &out, const TaskFileInfo &what);
    friend QDebug &operator <<(QDebug &out, const TaskFileInfo &what);

public:
    QString fileType;
    QString fileName;
    qint64 fileSize;
};

#endif // TASKFILEINFO_H
