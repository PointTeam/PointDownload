/**
  Author: sbwtw <sbwtws@gmail.com>
  下载任务的信息结构，用于PointPopup到PointDownload之间的数据传输
*/

#include "task.h"

#include <QDebug>

TaskInfo::TaskInfo() :
    QObject(0)
{
    // added by Choldrim, give them init state
    toolType = TOOL_UNDEF;
    maxThreads = 0;
    maxSpeed = 0;
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
QString TaskInfo::taskName() const
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
qint64 TaskInfo::taskSize() const
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
    if (!state.compare("dlstate_suspend", Qt::CaseInsensitive))
        taskState = DLSTATE_SUSPEND;
    else if (!state.compare("dlstate_downloading", Qt::CaseInsensitive))
        taskState = DLSTATE_DOWNLOADING;
    else if (!state.compare("dlstate_ready", Qt::CaseInsensitive))
        taskState = DLSTATE_READY;
    else if (!state.compare("dlstate_downloaded", Qt::CaseInsensitive))
        taskState = DLSTATE_DOWNLOADED;
    else
    {
        qWarning() << "download state not match any case At: void TaskInfo::setDownStateFromString(const QString &state)";
        taskState = DLSTATE_UNDEF;
    }
}

/*!
    请注意！ 此函数用于代码重构时的兼容，以后应尽少使用
*/
QString TaskInfo::getToolTypeToString() const
{
    switch (toolType)
    {
    case TOOL_POINT:    return "Point";
    case TOOL_ARIA2:    return "Aria2";
    case TOOL_XWARE:    return "Xware";
    case TOOL_YOUGET:   return "YouGet";
    default:
        qWarning() << "ToolType Undefined!";
        return "Undefined";
    }
}

/*!
    请注意！ 此函数用于代码重构时的兼容，以后应尽少使用
*/
QString TaskInfo::getDownStateToString() const
{
    switch (taskState)
    {
    case DLSTATE_SUSPEND:       return "dlstate_suspend";
    case DLSTATE_DOWNLOADING:   return "dlstate_downloading";
    case DLSTATE_READY:         return "dlstate_ready";
    default:
        qWarning() << "DownState Undefined!";
        return "undefined";
    }
}

/*!
    请注意！ 此函数用于代码重构时的兼容，以后应尽少使用
*/
QString TaskInfo::getInfoToString() const
{
    const QString split("?:?");
    QString infoStr;
    infoStr += getToolTypeToString() + split;
    infoStr += taskName() + split;
    infoStr += rawUrl + split;
    infoStr += parseUrl + split;
    infoStr += taskIconPath + split;
    infoStr += QString::number(taskSize()) + split;
    infoStr += savePath + split;
    infoStr += QString::number(maxThreads) + split;
    infoStr += QString::number(percentage, 'f', 2);

    return std::move(infoStr);
}

/*!
    请注意！ 此函数用于代码重构时的兼容，以后应尽少使用
*/
QString TaskInfo::getDownloadedInfoToString() const
{
    //info: dlToolsType?:?fileName?:?URL?:?iconName?:?fileSize?:?completeDate
    const QString split("?:?");
    QString infoStr;
    infoStr += getToolTypeToString() + split;
    infoStr += taskName() + split;
    infoStr += rawUrl + split;
    infoStr += taskIconPath + split;
    infoStr += QString::number(taskSize()) + split;
    infoStr += completeDate;

    return std::move(infoStr);
}

QString TaskInfo::getDownloadingInfoToString() const
{
    //info: dlToolsType?:?fileName?:?URL?:?RedirectURL?:?iconName?:?fileSize?:?savePath?:?threadCount?:?maxSpeed?:?readyPercentage?:?state

    const QString split("?:?");
    QString infoStr;
    infoStr += getToolTypeToString() + split;
    infoStr += taskName() + split;
    infoStr += rawUrl + split;
    infoStr += parseUrl + split;
    infoStr += taskIconPath + split;
    infoStr += QString::number(taskSize()) + split;
    infoStr += savePath + split;
    infoStr += maxThreads + split;
    infoStr += maxSpeed + split;
    infoStr += QString::number(percentage, 'f', 2) + split;
    infoStr += getDownStateToString();

    return std::move(infoStr);
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

QString TaskInfo::qml_getCompleteDate()
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
