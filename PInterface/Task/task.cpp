#include "task.h"

Task::Task(QObject *parent) :
    QObject(parent)
{
}

const QString Task::downloadBytesSpeedString()
{
    return "0 B/s";
}
