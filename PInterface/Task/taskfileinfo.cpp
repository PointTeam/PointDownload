
#include "taskfileinfo.h"

#include <QDebug>

TaskFileInfo::TaskFileInfo()
{
}

QDebug &operator <<(QDebug &out, const TaskFileInfo &what)
{
    out << endl << "TaskFileInfo:" << endl;
    out << "fileType = " << what.fileType << endl;
    out << "fileName = " << what.fileName << endl;
    out << "fileSize = " << what.fileSize << endl;

    return out;
}

QDataStream &operator >>(QDataStream &in, TaskFileInfo &what)
{
    in >> what.fileType;
    in >> what.fileName;
    in >> what.fileSize;

    return in;
}

QDataStream &operator <<(QDataStream &out, const TaskFileInfo &what)
{
    out << what.fileType;
    out << what.fileName;
    out << what.fileSize;

    return out;
}
