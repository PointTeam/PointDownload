#ifndef URLHANDLER_H
#define URLHANDLER_H

#include <QDebug>
#include <QObject>
#include <QStringList>
#include <QProcess>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include "pdatatype.h"
#include "settingxmlhandler.h"
#include "taskfileinfo.h"

class URLHandler : public QObject
{
    Q_OBJECT
public:
    explicit URLHandler(QObject *parent = 0);
    ~URLHandler();

    bool isPointSupportURL(const QString &url);
    bool isYouGetSupportURL(const QString &url);
    bool isAria2SupportURL(const QString &url);
    bool isXwareSupportURL(const QString &url);

    PDataType::ProtocolType getProtocolType(const QString &url);

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

    void analyzeURL(const QString &url);
signals:
    void finish();
    void getFileInfoListDone(QList<TaskFileInfo> infoList);
    void analyzeError();

public slots:

private slots:
    void getYouGetProcessFeedback();
    void getYouGetProcessError();

private:
    bool isYouGetSupportSite(const QString &url);
    QList<TaskFileInfo> getYouGetSingleFileInfo(const QString &data);
    QList<TaskFileInfo> getMultiFileInfo(const QString &data);

private:
    QProcess * yougetProcess;
};

#endif // URLHANDLER_H
