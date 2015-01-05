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
    qint64 fileSize;  // altered int to qint64 (by Choldrim, 2015.1.5)
};

#endif // TASKFILEITEM_H
