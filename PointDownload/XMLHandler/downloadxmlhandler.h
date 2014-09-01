#ifndef DOWNLOADXMLHANDLER_H
#define DOWNLOADXMLHANDLER_H

#include <QObject>
#include <QDir>
#include <QList>
#include <QDomDocument>
#include <QTextStream>
#include <QStandardPaths>
#include <QSysInfo>
#include <QDebug>


//已下载项的结构体
struct SDownloaded
{
    QString name;                   //文件名
    QString completeDate;   //完成下载的时间，格式：2014：03：03：18：30
    QString Size;                       //文件大小，Byte
    QString savePath;           //文件的保存路径
    QString URL;                  //文件下载的URL
    QString dlToolsType;    //下载后端类型 2014.6.1add
    QString exist;                  //文件是否还存在
    QString iconPath;
};

//单个下载线程的结构体，一个文件被分成多个线程进行，每个线程负责某些块的下载
struct SDownloadThread
{
    QString startBlockIndex;            //起始块号
    QString endBlockIndex;              //结束块号
    QString completedBlockCount;    //已完成的块数
};

//正在下载项结构体，其中threadList包括该下载项的线程结构组
struct SDownloading
{
    QString name;                               //文件名
    QString jobMaxSpeed;                    //此任务能使用的最大 下载速度
    QString savePath;                           //此文件的保存路径
    QString enableUpload;                    //此文件是否允许上传共享
    QString URL;                                   //文件下载URL
    QString redirectRUL;
    QString dlToolsType;                        //下载后端类型 2014.6.1add
    QString blockCount;                         //这个文件被分解成的数据块数量
    QString blockSize;                            //每个数据块的大小，Byte
    QList<SDownloadThread> threadList;//包含下载线程节点的列表
    QString totalSize;                              //总大小，Byte
    QString readySize;                              //已完成的大小，Byte
    QString autoOpenFolder;                     //完成后是否自动打开文件夹
    QString state;                              //Suspend,Downloading,Ready,2014.4.7add
    QString averageSpeed;
    QString lastModifyTime;
    QString iconPath;
};

//垃圾箱结构体
struct SDownloadTrash
{
    QString name;       //文件名
    QString totalSize;  //总大小
    QString URL;        //文件下载的URL
    QString dlToolsType;                        //下载后端类型 2014.6.1add
    QString iconPath;
};


class DownloadXMLHandler : public QObject
{
    Q_OBJECT
public:
    explicit DownloadXMLHandler(QObject *parent = 0);


    bool writeDownloadingConfigFile(SDownloading downloading);    //修改正在下载项的配置文件

    bool insertDownloadedNode(SDownloaded tmpStruct);               //插入一个已完成下载项到下载完成配置文件中
    bool insertDownloadingNode(SDownloading tmpStruct);             //插入一个正在下载项到正在下载配置文件中
    bool insertDownloadTrash(SDownloadTrash tmpStruct);             //插入一个被删除的项到已删除配置文件中

    bool removeDownloadingFileNode(QString URL);                //移除下载链接为URL的正在下载项
    bool removeDownloadedFileNode(QString URL);                 //移除下载链接为URL的已下载项
    bool removeDownloadTrashFileNode(QString URL);              //移除下载链接为URL的回首站项

    bool urlExit(QString url, QString type);                    //type can be string "ing" or "ed"

    QList<SDownloaded> getDownloadedNodes();                    //返回所有已下载完成的项组成的结构体列表
    QList<SDownloading> getDownloadingNodes();                  //返回所有正在下载的项组成的结构体列表
    QList<SDownloadTrash> getDownloadTrashNodes();              //返回垃圾桶中所有项组成的结构体列表

    SDownloaded getDownloadedNode(QString URL);                 //返回下载链接为URL已下载的项的内容结构体
    SDownloading getDownloadingNode(QString URL);               //返回下载链接为URL正在下载项的内容结构体
    SDownloadTrash getDownloadTrashNode(QString URL);           //返回下载链接为URL垃圾桶项的内容结构体

signals:

public slots:

private:
    void touchAll();                         //从调用下面的探测函年数，被构造函数调用
    void touchConfigDir();                   //探测配置文件夹是否存在，不存在则创建
    void touchDownloadDir();
    void touchDownloadedConfigFile();        //探测已下载列表文件是否存在，不存在则创建
    void touchDownloadingConfigFile();       //探测正在下载列表文件是否存在，不存在则创建
    void touchDownloadTrashConfigFile();     //探测垃圾箱文件是否存在，不存在则创建

    QDomDocument getDocument(QString path);
    QDomNode getMatchFileNode(QDomDocument &domDoc, QString URL);   //将对应URL的节点取出，以便进行删除操作
    QDomElement createChildElement(QString tagName, QString tagValue);//创建相应的子Element并返回
    QDomElement createThreadElement(QList<SDownloadThread> threadList);//根据给出的threadList创建包含多个Thread子节点的Threads节点

    //设置文件的URL匹配并且tagName相同的节点的内容为nodeValue
    void setDownloadingNodeValue(QDomDocument &domDoc, QString URL, QString tagName, QString nodeValue);
    //设置Threads节点下的所有Thread节点的CompleteBlockCount值
    void setDownloadingThreadNodeValue(QDomDocument &domDoc, QString URL, QList<SDownloadThread> nodeValue);





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
