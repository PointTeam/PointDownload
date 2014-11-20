
#include "taskinfo.h"
#include "taskfileitem.h"

#include <QDebug>

/**
    下载任务的信息结构，用于PointPopup到PointDownload之间的数据传输
*/

TaskInfo::TaskInfo() :
    QObject(0)
{

}

TaskInfo::TaskInfo(QIODevice *in) :
    QObject(0)
{
    QDataStream ins(in);
    ins >> *this;
}

TaskInfo::TaskInfo(const TaskInfo &taskInfo) :
    QObject(0)
{
    *this = taskInfo;
}

TaskInfo::TaskInfo(const int toolType, const QList<TaskFileItem> &fileNameList, const QUrl &rawUrl, const QUrl &parseUrl, const QString &taskIconPath, const QString &savePath, const int maxThreads, const int maxSpeed) :
    QObject(0)
{
    this->toolType = toolType;
    this->fileList = fileNameList;
    this->rawUrl = rawUrl;
    this->parseUrl = parseUrl;
    this->taskIconPath = taskIconPath;
    this->savePath = savePath;
    this->maxThreads = maxThreads;
    this->maxSpeed = maxSpeed;
}

TaskInfo::~TaskInfo()
{

}

QByteArray TaskInfo::toQByteArray() const
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << *this;

    return data;
}

/*!
    获取当前任务的文件列表
*/
QString TaskInfo::fileListString() const
{
    QString str;

    for (TaskFileItem i : fileList)
        str += i.fileName + "\n";

    if (!str.isEmpty())
        return str.left(str.size() - 1);
    return str;
}

/*!
    虽然一个任务中可能包含多个文件但代码中一直以第一个文件做为任务名称
*/
QString TaskInfo::taskName() const
{
    if (fileList.empty())
    {
        qWarning() << "task file list is empty !";
        return "Empty";
    }
    return fileList.at(0).fileName;
}

/*!
    任务包含文件的大小总和作为任务的总大小
*/
int TaskInfo::taskSize() const
{
    int size(0);
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
    out << "rawUrl = "      << what.rawUrl.toString() << endl;
    out << "parseUrl = "    << what.parseUrl.toString() << endl;
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
    default:            return "Undefined";
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
    default:                    return "undefined";
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
    infoStr += rawUrl.toString() + split;
    infoStr += parseUrl.toString() + split;
    infoStr += taskIconPath + split;
    infoStr += QString::number(taskSize()) + split;
    infoStr += savePath + split;
    infoStr += QString::number(maxThreads) + split;
    infoStr += QString::number(percentage, 'f', 1);
    return infoStr;
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
