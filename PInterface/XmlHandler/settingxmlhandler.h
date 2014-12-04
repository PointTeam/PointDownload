#ifndef SETTINGXMLHANDLER_H
#define SETTINGXMLHANDLER_H

#include <QObject>
#include <QDir>
#include <QList>
#include <QDomDocument>
#include <QTextStream>
#include <QStandardPaths>
#include <QSysInfo>
#include <QDebug>

enum RootTagName
{
    GeneralSettings,
    DropzoneSetting,
    Aria2Setting,
    XwareSetting,
    YouGetSetting
};

class SettingXMLHandler : public QObject
{
    Q_OBJECT
public:
    explicit SettingXMLHandler(QObject *parent = 0);

    QString getChildElement(RootTagName rootTagName, QString childTagName);
    void setChildElement(RootTagName rootTagName, QString childTagName, QString value);

private:
    void touchAll();                                 //从调用下面的探测函年数，被构造函数调用
    void touchConfigDir();                          //探测配置文件夹是否存在，不存在则创建
    void touchDownloadDir();
    void touchPointSettingFile();                  //探测主配置文件是否存在，不存在则创建

    QDomNodeList getDomNodeList(QDomDocument &domDocument,RootTagName rootTagName);
    //创建相应的子Element并返回
    QDomElement createChildElement(QString tagName, QString tagValue);
private:
    //以下是各个配置文件的路径
    const QString SETTING_CONFIG_FILE =
            QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.PointConfig/PointSetting.xml";
    const QString CONFIG_DIR_PATH =
            QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.PointConfig";
    const QString DOWNLOAD_SAVE_PATH =
            QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).at(0) + "/PointDownload";
};

#endif // SETTINGXMLHANDLER_H
