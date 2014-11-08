#ifndef TASKFILEITEM_H
#define TASKFILEITEM_H

#include <QString>
#include <QDataStream>
#include <QDebug>

class TaskFileItem
{
public:
    TaskFileItem();

    friend QDataStream &operator >>(QDataStream &in, TaskFileItem &what);
    friend QDataStream &operator <<(QDataStream &out, const TaskFileItem &what);
    friend QDebug &operator <<(QDebug &out, const TaskFileItem &what);

public:
    QString fileType;
    QString fileName;
    int fileSize;
};

#endif // TASKFILEITEM_H
