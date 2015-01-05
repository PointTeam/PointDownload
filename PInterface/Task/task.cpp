#include "task.h"

Task::Task(QObject *parent) :
    QObject(parent)
{
}

float Task::completePercent() const
{
    return infomation.percentage;
}

const QString Task::completePercentString() const
{
    return QString::number(completePercent(), 'f', 2);
}

const QString Task::downloadBytesSpeedString()
{
    return "0 B/s";
}

void Task::dumpErrorMessage(const QString &errorStr) const
{
    qDebug() << errorStr;
}
