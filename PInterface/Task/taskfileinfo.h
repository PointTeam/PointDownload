#ifndef TASKFILEINFO_H
#define TASKFILEINFO_H

#include <QObject>
#include <QString>
#include <QDataStream>
#include <QDebug>

class TaskFileInfo
{

    Q_PROPERTY(QString fileName READ getFileName WRITE setFileName NOTIFY fileNameChanged)
public:
    explicit TaskFileInfo();

    friend QDataStream &operator >>(QDataStream &in, TaskFileInfo &what);
    friend QDataStream &operator <<(QDataStream &out, const TaskFileInfo &what);
    friend QDebug &operator <<(QDebug &out, const TaskFileInfo &what);

    QString getFileName(){return fileName;}
    void setFileName(QString name){fileName = name;}
public:
    QString fileType;
    QString fileName;
    qint64 fileSize;
    Q_SIGNAL void fileNameChanged();
};

Q_DECLARE_METATYPE(TaskFileInfo)
#endif // TASKFILEINFO_H
