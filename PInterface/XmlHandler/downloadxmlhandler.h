#ifndef DOWNLOADXMLHANDLER_H
#define DOWNLOADXMLHANDLER_H

#include <QObject>
#include <QDir>
#include <QList>
#include <QDomDocument>
#include <QTextStream>
#include <QStandardPaths>
#include <QSysInfo>
#include <QJsonObject>
#include <QDebug>
#include "pdatatype.h"

//单个下载线程的结构体，一个文件被分成多个线程进行，每个线程负责某些块的下载
struct SDownloadThread
{
    qint64 startBlockIndex;            //起始块号
    qint64 endBlockIndex;              //结束块号
    qint64 completedBlockCount;        //已完成的块数
};

//正在下载项结构体，其中threadList包括该下载项的线程结构组
struct SDownloading
{
    QString fileID;
    QString fileName;                       //文件名
    qint64 fileTotalSize;                   //总大小，Byte
    qint64 fileReadySize;                   //已完成的大小，Byte
    QString fileSavePath;                   //此文件的保存路径
    QString url;                            //文件下载URL
    PDataType::ToolType toolType;
    PDataType::TaskState taskState;
    int taskMaxSpeed;                       //此任务能使用的最大 下载速度
    int averageSpeed;
    QList<SDownloadThread> threadList;      //包含下载线程节点的列表
    qint64 blockCount;                      //这个文件被分解成的数据块数量
    qint64 blockSize;                       //每个数据块的大小，Byte
    bool enableUpload;                      //此文件是否允许上传共享
};

//已下载项的结构体
struct SDownloaded
{
    QString fileID;
    QString fileName;                   //文件名
    qint64 fileTotalSize;               //文件大小，Byte
    QString fileSavePath;               //文件的保存路径
    QString completeDate;               //完成下载的时间，格式：2014：03：03：18：30
    bool fileExist;                     //文件是否还存在
    QString url;                        //文件下载的URL
    PDataType::ToolType toolType;       //下载后端类型 2014.6.1add
};

//垃圾箱结构体
struct SDownloadTrash
{
    QString fileID;
    QString fileName;               //文件名
    qint64 fileTotalSize;           //总大小
    QString url;                    //文件下载的URL
    PDataType::ToolType toolType;   //下载后端类型 2014.6.1add
};


class DownloadXMLHandler : public QObject
{
    Q_OBJECT
public:
    explicit DownloadXMLHandler(QObject *parent = 0);


    bool updateDLingNode(const SDownloading & tmpStruct);       //修改正在下载项的配置文件

    bool insertDLedNode(const SDownloaded & tmpStruct);         //插入一个已完成下载项到下载完成配置文件中
    bool insertDLingNode(const SDownloading & tmpStruct);       //插入一个正在下载项到正在下载配置文件中
    bool insertDLtrashNode(const SDownloadTrash & tmpStruct);   //插入一个被删除的项到已删除配置文件中

    bool removeDLingFileNode(const QString & fileID);                //移除id为fileID的正在下载项
    bool removeDLedFileNode(const QString & fileID);                 //移除id为fileID的已下载项
    bool removeDLtrashFileNode(const QString & fileID);              //移除id为fileID的回首站项

    bool fileIDExist(const QString & fileID, PDataType::DownloadType dlType);

    QJsonObject getJsonObjFromSDownloaded(const SDownloaded & data);
    QJsonObject getJsonObjFromSDownloading(const SDownloading & data);
    QJsonObject getJsonObjFromSDownloadTrash(const SDownloadTrash & data);

    QList<SDownloading> getDLingNodes();                  //返回所有正在下载的项组成的结构体列表
    QList<SDownloaded> getDLedNodes();                    //返回所有已下载完成的项组成的结构体列表
    QList<SDownloadTrash> getDLtrashNodes();              //返回垃圾桶中所有项组成的结构体列表

    SDownloading getDLingNode(const QString & fileID);               //返回id为fileID正在下载项的内容结构体
    SDownloaded getDLedNode(const QString & fileID);                 //返回id为fileID已下载的项的内容结构体
    SDownloadTrash getDLtrashNode(const QString & fileID);           //返回id为fileID垃圾桶项的内容结构体

private:
    void touchAll();                         //从调用下面的探测函年数，被构造函数调用
    void touchConfigDir();                   //探测配置文件夹是否存在，不存在则创建
    void touchDownloadDir();
    void touchDLedConfigFile();        //探测已下载列表文件是否存在，不存在则创建
    void touchDLingConfigFile();       //探测正在下载列表文件是否存在，不存在则创建
    void touchDLtrashConfigFile();     //探测垃圾箱文件是否存在，不存在则创建

    QDomDocument getDocument(const QString & path);
    QDomNode getMatchFileNode(const QDomDocument &domDoc, const QString & fileID);   //将对应fileID的节点取出，以便进行删除操作
    QDomElement createChildElement(QString tagName, QString tagValue);//创建相应的子Element并返回
    QDomElement createThreadElement(QList<SDownloadThread> threadList);//根据给出的threadList创建包含多个Thread子节点的Threads节点

    //设置文件的URL匹配并且tagName相同的节点的内容为nodeValue
    void setDownloadingNodeValue(QDomDocument &domDoc, const QString & fileID, QString tagName, QString nodeValue);
    //设置Threads节点下的所有Thread节点的CompleteBlockCount值
    void setDownloadingThreadNodeValue(QDomDocument &domDoc, const QString & fileID, QList<SDownloadThread> nodeValue);

private:
    //以下是各个配置文件的路径
    const QString CONFIG_DIR_PATH =
            QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.PointConfig";
    const QString DOWNLOAD_SAVE_PATH =
            QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).at(0) + "/PointDownload";
    const QString DOWNLOADEDFILE_PATH =
            QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.PointConfig/PointDownloaded.xml";
    const QString DOWNLOADINGFILE_PATH =
            QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.PointConfig/PointDownloading.xml";
    const QString DOWNLOADTRASHFILE_PATH =
            QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.PointConfig/PointDownloadTrash.xml";
};

#endif // DOWNLOADXMLHANDLER_H
