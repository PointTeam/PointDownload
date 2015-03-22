
#include "task.h"

#include <QDebug>

/**
    下载任务的信息结构，用于PointPopup到PointDownload之间的数据传输
*/

TaskInfo::TaskInfo() :
    QObject(0)
{
    // added by Choldrim, give them init state
    toolType = PDataType::PToolTypeUndefined;
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
    toolType = std::move(taskInfo.toolType);
    maxThreads = taskInfo.maxThreads;
    maxSpeed = taskInfo.maxSpeed;
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

// define the stream operators for the enum classes before  define them for TaskInfo class.
QDataStream & operator >> (QDataStream& in, PDataType::ToolType& tooltype)
{
    unsigned u = 0;
    in >> u;
    //TODO: check that u is a valid PDataType::ToolType value
    tooltype = static_cast<PDataType::ToolType>(u);
    return in;
}

QDataStream & operator << (QDataStream& out,  PDataType::ToolType& tooltype)
{
    //TODO: check that tooltype is a valid PDataType::ToolType value
    unsigned u = tooltype;
    out << u;
    return out;
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

PDataType::ToolType TaskInfo::qml_getToolType()
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
