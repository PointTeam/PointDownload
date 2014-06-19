/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Match <2696627729@qq.com>
* Maintainer: Match <2696627729@qq.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/
/************************************************************************************************
Date:   2014.3.19~
Description:
    这个类负责读写，修改系统配置使用的xml文件（包括：PointMainConf.xml，PointDownloaded.xml，
PointDownloading.xml，PointDownloadTrash.xml），其中这些配置文件在软件启动时都会检查是否存在，不存在则
新建配置文件。
Others:
Function list:

History:
*************************************************************************************************/
#ifndef XMLOPERATIONS_H
#define XMLOPERATIONS_H

#include <QObject>
#include <QDir>
#include <QList>
#include <QDomDocument>
#include <QTextStream>
#include <QStandardPaths>
#include <QSysInfo>
#include <QDebug>

//以下是各个配置文件的路径
const QString MAINCONFIGFILE_PATH =
        QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.PointConfig/PointMainConf.xml";
const QString DOWNLOADEDFILE_PATH =
        QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.PointConfig/PointDownloaded.xml";
const QString DOWNLOADINGFILE_PATH =
        QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.PointConfig/PointDownloading.xml";
const QString DOWNLOADTRASHFILE_PATH =
        QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.PointConfig/PointDownloadTrash.xml";

//主配置文件结构体，xml文件的读写都需要通过该结构体进行
struct SMainConfig
{
    QString operatingSysType;
    QString version;
    QString downloadSpeed;          //最大下载速度
    QString uploadSpeed;            //最大上传速度
    QString windowsSavePath;        //windows下的文件默认保存路径
    QString linuxSavePath;          //linux下的文件默认保存的路径
    QString beep;                   //下载完成后是否有提示音
    QString enableUpload;           //是否允许下载项上传共享
    QString defaultThreadCount;     //默认的线程数量
    QString videoDetectType;        //默认的饰品探测类型
    QString audioDetectType;        //默认的音频探测类型
    QString maxJobCount;            //可以同时进行的下载项数量
    QString clipboard;              //监控剪切板
    QString exitOnClose;            //关闭立即退出
    QString aria2Path;              //aria2可执行文件路径
    QString yougetPath;             //youget可执行文件路径
};

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

class XMLOperations : public QObject
{
    Q_OBJECT
public:
    explicit XMLOperations(QObject *parent = 0);

private:
    QString configPath;
private:
    void touchAll();                                    //从调用下面的探测函年数，被构造函数调用
    void touchConfigDir();                          //探测配置文件夹是否存在，不存在则创建
    void touchDownloadDir();
    void touchMainConfigFile();                  //探测主配置文件是否存在，不存在则创建
    void touchDownloadedConfigFile();        //探测已下载列表文件是否存在，不存在则创建
    void touchDownloadingConfigFile();        //探测正在下载列表文件是否存在，不存在则创建
    void touchDownloadTrashConfigFile();    //探测垃圾箱文件是否存在，不存在则创建
    //设置主配置文件中对应tagName的节点的内容
    void setConfigDomNodeValue(QDomDocument &domDoc, QString tagName, QString nodeValue);
    //设置文件的URL匹配并且tagName相同的节点的内容为nodeValue
    void setDownloadingNodeValue(QDomDocument &domDoc, QString URL, QString tagName, QString nodeValue);
    //设置Threads节点下的所有Thread节点的CompleteBlockCount值
    void setDownloadingThreadNodeValue(QDomDocument &domDoc, QString URL, QList<SDownloadThread> nodeValue);

    //创建相应的子Element并返回
    QDomElement createChildElement(QString tagName, QString tagValue);
    //根据给出的threadList创建包含多个Thread子节点的Threads节点
    QDomElement createThreadElement(QList<SDownloadThread> threadList);

    //将对应URL的节点取出，以便进行删除操作
    QDomNode getMatchFileNode(QDomDocument &domDoc, QString URL);


    QDomDocument getDocument(QString path);
public:
    bool writeMainConfigFile(SMainConfig mainConfig);             //修改主配置文件的某些内容
    bool writeDownloadingConfigFile(SDownloading downloading);    //修改正在下载项的配置文件

    void insertDownloadedNode(SDownloaded tmpStruct);               //插入一个已完成下载项到下载完成配置文件中
    void insertDownloadingNode(SDownloading tmpStruct);             //插入一个正在下载项到正在下载配置文件中
    void insertDownloadTrash(SDownloadTrash tmpStruct);             //插入一个被删除的项到已删除配置文件中

    void removeDownloadingFileNode(QString URL);                //移除下载链接为URL的正在下载项
    void removeDownloadedFileNode(QString URL);                 //移除下载链接为URL的已下载项
    void removeDownloadTrashFileNode(QString URL);              //移除下载链接为URL的回首站项

    bool urlExit(QString url, QString type);                    //type can be string "ing" or "ed"

    QList<SDownloaded> getDownloadedNodes();                    //返回所有已下载完成的项组成的结构体列表
    QList<SDownloading> getDownloadingNodes();                  //返回所有正在下载的项组成的结构体列表
    QList<SDownloadTrash> getDownloadTrashNodes();              //返回垃圾桶中所有项组成的结构体列表


    SMainConfig getMainConfig();                                //将主配置文件的所有内容以结构体的方式返回
    SDownloaded getDownloadedNode(QString URL);                 //返回下载链接为URL已下载的项的内容结构体
    SDownloading getDownloadingNode(QString URL);               //返回下载链接为URL正在下载项的内容结构体
    SDownloadTrash getDownloadTrashNode(QString URL);           //返回下载链接为URL垃圾桶项的内容结构体

signals:

public slots:

};

#endif // XMLOPERATIONS_H
