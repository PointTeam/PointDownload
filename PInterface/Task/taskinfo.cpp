/**
  Author: sbwtw <sbwtws@gmail.com>
  下载任务的信息结构，用于PointPopup到PointDownload之间的数据传输
*/

#include "task.h"

#include <QDebug>
#include <QRegExp>

TaskInfo::TaskInfo() :
    QObject(0)
{
    // added by Choldrim, give them init state
    toolType = TOOL_UNDEF;
    maxThreads = 0;
    maxSpeed = 0;
    downloadSpeedNow = 0;
}

TaskInfo::TaskInfo(QIODevice *in) :
    QObject(0)
{
    QDataStream ins(in);
    ins >> *this;
}

TaskInfo::TaskInfo(TaskInfo &&taskInfo)
{
    fileList = std::move(taskInfo.fileList);
    rawUrl = std::move(taskInfo.rawUrl);
    parseUrl = std::move(taskInfo.parseUrl);
    taskIconPath = std::move(taskInfo.taskIconPath);
    savePath = std::move(taskInfo.savePath);
    toolType = taskInfo.toolType;
    maxThreads = taskInfo.maxThreads;
    maxSpeed = taskInfo.maxSpeed;

    completeDate = std::move(taskInfo.completeDate);
    percentage = taskInfo.percentage;
    taskState = taskInfo.taskState;
}

TaskInfo::TaskInfo(const TaskInfo &taskInfo) :
    QObject(0)
{
    *this = taskInfo;
}

TaskInfo::~TaskInfo()
{

}

QByteArray TaskInfo::toQByteArray() const
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << *this;

    return std::move(data);
}

/*!
    获取当前任务的文件列表
*/
QStringList TaskInfo::fileStringList() const
{
    QStringList list;

    for (TaskFileItem i : fileList)
        list << i.fileName;

    return list;
}

/*!
    文件名列表大于1的时候以文件大小为-1的项作为文件名
*/
QString TaskInfo::name() const
{
    if (fileList.empty())
    {
        qWarning() << "task file list is empty !";
        return "Empty";
    }
    for (int i = 0; i < fileList.length(); i ++)
    {
        if (fileList.at(i).fileSize == -1)
            return fileList.at(i).fileName;
    }

    //if there is no item's size with -1,just return the first item
    return fileList.at(0).fileName;
}

/*!
    任务包含文件的大小总和作为任务的总大小
    altered int to qint64 ( by Choldrim )
*/
qint64 TaskInfo::size() const
{
    qint64 size(0);
    for (TaskFileItem i : fileList)
        size += i.fileSize;
    return size;
}

/*!
    注意序列化和反序列化时各个成员的顺序[必须]一致
*/
QDataStream &operator >>(QDataStream &in, TaskInfo &what)
{
    in >> what.toolType;
    in >> what.fileList;
    in >> what.rawUrl;
    in >> what.parseUrl;
    in >> what.taskIconPath;
    in >> what.savePath;
    in >> what.maxThreads;
    in >> what.maxSpeed;

    return in;
}

/*!
    注意序列化和反序列化时各个成员的顺序[必须]一致
*/
QDataStream &operator <<(QDataStream &out, const TaskInfo &what)
{
    out << what.toolType;
    out << what.fileList;
    out << what.rawUrl;
    out << what.parseUrl;
    out << what.taskIconPath;
    out << what.savePath;
    out << what.maxThreads;
    out << what.maxSpeed;

    return out;
}

QDebug operator <<(QDebug out, const TaskInfo &what)
{
    out << endl << "TaskInfo:" << endl;
    out << "toolType = "    << what.toolType << endl;
    out << what.fileList    << endl;
    out << "rawUrl = "      << what.rawUrl << endl;
    out << "parseUrl = "    << what.parseUrl << endl;
    out << "taskIconPath = " << what.taskIconPath << endl;
    out << "savePath = "    << what.savePath << endl;
    out << "maxThreads = "  << what.maxThreads << endl;
    out << "maxSpeed = "    << what.maxSpeed << endl;

    return out;
}

/*!
    请注意！ 此函数用于旧版本的数据到新数据的转换，以后设置toolType时最好以
    taskinfo.h文件中定义的类型来设置。
*/
void TaskInfo::setToolTypeFromString(const QString &tool)
{
    if (!tool.compare("Point", Qt::CaseInsensitive))
        toolType = TOOL_POINT;
    else if (!tool.compare("Aria2", Qt::CaseInsensitive))
        toolType = TOOL_ARIA2;
    else if (!tool.compare("Xware", Qt::CaseInsensitive))
        toolType = TOOL_XWARE;
    else if (!tool.compare("YouGet", Qt::CaseInsensitive))
        toolType = TOOL_YOUGET;
    else
    {
        qWarning() << "toolType not match any case At: void TaskInfo::setToolTypeFromString(const QString &tool)";
        toolType = TOOL_UNDEF;
    }
}

/*!
    请注意！ 此函数用于旧版本的数据到新数据的转换，以后设置taskState时最好以
    taskinfo.h文件中定义的类型来设置。
*/
void TaskInfo::setDownStateFromString(const QString &state)
{
    taskState = convertDownStateToInt(state);
}

int TaskInfo::convertDownStateToInt(const QString state)
{
    if (!state.compare("dlstate_suspend", Qt::CaseInsensitive))
        return DLSTATE_SUSPEND;
    else if (!state.compare("dlstate_downloading", Qt::CaseInsensitive))
        return DLSTATE_DOWNLOADING;
    else if (!state.compare("dlstate_ready", Qt::CaseInsensitive))
        return DLSTATE_READY;
    else if (!state.compare("dlstate_downloaded", Qt::CaseInsensitive))
        return DLSTATE_DOWNLOADED;
    else
    {
        qWarning() << "download state: " << state;
        qWarning() << "download state not match any case At: void TaskInfo::setDownStateFromString(const QString &state)";
        return DLSTATE_UNDEF;
    }
}

/*!
    旧C++代码中的速度直接以 xx KB/S 这样的格式保存，
    新代码统一转换成 int 型以 byte 为单位
*/
int TaskInfo::convertDownloadSpeedToInt(const QString speed)
{
    QRegExp reg("^(\\d+) KB/S$");
    if (reg.indexIn(speed) != -1)
        return reg.cap(1).toInt() * 1024;

    qDebug() << "Not match speed string: " << speed;
    return 0;
}

TaskInfo &TaskInfo::operator =(const TaskInfo &what)
{
    fileList = what.fileList;
    rawUrl = what.rawUrl;
    parseUrl = what.parseUrl;
    taskIconPath = what.taskIconPath;
    savePath = what.savePath;
    toolType = what.toolType;
    maxThreads = what.maxThreads;
    maxSpeed = what.maxSpeed;

    completeDate = what.completeDate;
    percentage = what.percentage;
    taskState = what.taskState;

    return *this;
}

QString TaskInfo::qml_getRawUrl()
{
    return rawUrl;
}

QString TaskInfo::qml_getParseUrl()
{
    return parseUrl;
}

QString TaskInfo::qml_getIconPath()
{
    return taskIconPath;
}

QString TaskInfo::qml_getSavePath()
{
    return savePath;
}

QDateTime TaskInfo::qml_getCompleteDate()
{
    return completeDate;
}

float TaskInfo::qml_getPercentage()
{
    return percentage;
}

int TaskInfo::qml_getToolType()
{
    return toolType;
}

int TaskInfo::qml_getMaxThreads()
{
    return maxThreads;
}

int TaskInfo::qml_getMaxSpeed()
{
    return maxSpeed;
}

int TaskInfo::qml_getTaskState()
{
    return taskState;
}

int TaskInfo::qml_getDownloadSpeedNow()
{
    return downloadSpeedNow;
}
