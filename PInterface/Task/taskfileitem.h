/**
  Author: sbwtw <sbwtws@gmail.com>
  用于表示一个下载任务中的各个文件列表（大多数下载任务只有一个文件，但BT等任务含有多个文件）
*/

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
