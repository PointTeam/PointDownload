#ifndef URLHANDLER_H
#define URLHANDLER_H

#include <QDebug>
#include <QObject>
#include <QStringList>
#include <QProcess>
#include "pdatatype.h"
#include "settingxmlhandler.h"
#include "taskfileinfo.h"

class URLHandler : public QObject
{
    Q_OBJECT
public:
    enum ProtocolType{
        HTTP,
        HTTPS,
        FTP,
        BitTorrent,
        Metalink,
        Magnet,
        Ed2k,
        YouGet
    };

    explicit URLHandler(QObject *parent = 0);
    ~URLHandler();

    bool isPointSupportURL(const QString &url);
    bool isYouGetSupportURL(const QString &url);
    bool isAria2SupportURL(const QString &url);
    bool isXwareSupportURL(const QString &url);

    URLHandler::ProtocolType getProtocolType(const QString &url);

    //目前使用其他程序分析bt文件等其他信息，所以不能马上返回，
    //即使后面使用线程自行分析也不能马上返回，所以以信号形式返回
    void getHTTPFileList(const QString &url);
    void getHTTPSFileList(const QString &url);
    void getFTPFileList(const QString &url);
    void getBTFileList(const QString &url);
    void getMetaLinkFileList(const QString &url);
    void getMagnetFileList(const QString &url);
    void getEd2kFileList(const QString &url);
    void getYouGetFileList(const QString &url);

    void getFileInfoList(const QString &url);
signals:
    void finish();
    void getFileInfoListDone(QList<TaskFileInfo> infoList);

public slots:

private slots:
    void getYouGetProcessFeedback();
    void getYouGetProcessError();

private:
    bool isYouGetSupportSite(const QString &url);

private:
    QProcess * yougetProcess;
};

#endif // URLHANDLER_H
