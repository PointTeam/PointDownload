
#include "taskfileitem.h"

#include <QDebug>

TaskFileItem::TaskFileItem()
{
}

QDebug &operator <<(QDebug &out, const TaskFileItem &what)
{
    out << endl << "TaskFileItem:" << endl;
    out << "fileType = " << what.fileType << endl;
    out << "fileName = " << what.fileName << endl;
    out << "fileSize = " << what.fileSize << endl;

    return out;
}

QDataStream &operator >>(QDataStream &in, TaskFileItem &what)
{
    in >> what.fileType;
    in >> what.fileName;
    in >> what.fileSize;

    return in;
}

QDataStream &operator <<(QDataStream &out, const TaskFileItem &what)
{
    out << what.fileType;
    out << what.fileName;
    out << what.fileSize;

    return out;
}
