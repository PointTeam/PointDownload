#include "urlhandler.h"

URLHandler::URLHandler(QObject *parent) : QObject(parent)
{

}

//HTTP(S)
bool URLHandler::isPointSupportURL(const QString &url)
{
    if (getProtocolType(url) == URLHandler::HTTP)
        return true;
    else
        return false;
}

bool URLHandler::isYouGetSupportURL(const QString &url)
{
    if (getProtocolType(url) == URLHandler::YouGet)
        return true;
    else
        return false;
}

//HTTP(S), FTP, BitTorrent, and Metalink
bool URLHandler::isAria2SupportURL(const QString &url)
{
    if (getProtocolType(url) == URLHandler::HTTP ||
            getProtocolType(url) == URLHandler::HTTPS ||
            getProtocolType(url) == URLHandler::FTP ||
            getProtocolType(url) == URLHandler::BitTorrent ||
            getProtocolType(url) == URLHandler::Metalink)
        return true;
    else
        return false;
}

bool URLHandler::isXwareSupportURL(const QString &url)
{
    if (getProtocolType(url) == URLHandler::HTTP ||
            getProtocolType(url) == URLHandler::HTTPS ||
            getProtocolType(url) == URLHandler::FTP ||
            getProtocolType(url) == URLHandler::BitTorrent ||
            getProtocolType(url) == URLHandler::Metalink ||
            getProtocolType(url) == URLHandler::Magnet ||
            getProtocolType(url) == URLHandler::Ed2k)
        return true;
    else
        return false;
}

URLHandler::ProtocolType URLHandler::getProtocolType(const QString &url)
{
    if (isYouGetSupportSite(url))
        return URLHandler::YouGet;
    else if (url.startsWith("http://"))
        return URLHandler::HTTP;
    else if (url.startsWith("https://"))
        return URLHandler::HTTPS;
    else if (url.startsWith("ftp://"))
        return URLHandler::FTP;
    else if (url.endsWith(".torrent"))//url is file path
        return URLHandler::BitTorrent;
    else if (url.endsWith(".meta4"))//url is file path
        return URLHandler::Metalink;
    else if (url.startsWith("magnet:?xt"))
        return URLHandler::Magnet;
    else if (url.startsWith("ed2k://"))
        return URLHandler::Ed2k;
}

bool URLHandler::isYouGetSupportSite(const QString &url)
{
    QString videoURLRegex =
            QString("^(http://www\\.tudou\\.com/|") +
            QString("http://v\\.yinyuetai\\.com/|") +
            QString("http://v\\.youku\\.com/| ")+
            QString("http://v\\.ku6\\.com/|")+
            QString("http://v\\.163\\.com/|") +
            QString("http://v\\.qq\\.com/|") +
            QString("http://www\\.acfun\\.com/v/|")+
            QString("http://bilibili\\.kankanews\\.com/video/av|")+
            QString("http://www\\.bilibili.com/video/av|")+
            QString("http://www\\.jpopsuki\\.tv/video/|")+
            QString("http://video\\.sina\\.com\\.cn/|")+
            QString("http://tv\\.sohu\\.com/|")+
            QString("http://www\\.56\\.com/[wu]{1}|")+
            QString("http://www\\.songtaste\\.com/song/).+");

    QRegExp rex(videoURLRegex);
    return rex.exactMatch(url);
}

void URLHandler::getHTTPFileList(const QString &url)
{
    qint64 fileTotalSize = -1;
    QString fileMIMEType = "";
    QNetworkAccessManager * tmpManager = new QNetworkAccessManager;
    QNetworkReply*  headReply = NULL;
    QNetworkRequest headReq(url);
    headReq.setRawHeader("User-Agent", "");  //Content-Length

    headReply =  tmpManager->head(headReq);

    if(!headReply)
    {
        emit analyzeError();
        return;
    }

    QEventLoop loop;
    connect(headReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(headReply->error() != QNetworkReply::NoError)
    {
        qWarning() << "[Error]: Get url info error:" << headReply->errorString();
        emit analyzeError();
        return;
    }

    int statusCode = headReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qWarning() << "[Info] Status code:" << statusCode;
    qWarning()<< "[Info] File type:" << headReply->header(QNetworkRequest::ContentTypeHeader).toString();

    if(statusCode == 302)
    {
        QUrl redirectUrl = headReply->header(QNetworkRequest::LocationHeader).toUrl();
        if(redirectUrl.isValid())
        {
            qWarning()<<"Redirect："<<redirectUrl;
            delete tmpManager;
            return getHTTPFileList(redirectUrl.toString());
        }
    }
    else if (statusCode == 200)
    {
        fileTotalSize = headReply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
        fileMIMEType =  headReply->header(QNetworkRequest::ContentTypeHeader).toString();
        delete tmpManager;
    }
    else
    {
        qWarning() << "[Error]: Get url info error:" << headReply->errorString();
        emit analyzeError();
        return;
    }

    const QString fileName(QUrl(url).fileName());
    QList<TaskFileInfo> tmpList;
    TaskFileInfo tmpinfo;
    tmpinfo.fileName = fileName.isEmpty() ? "UnknownName" : fileName;
    tmpinfo.fileSize = fileTotalSize;
    tmpinfo.fileType = "File";//fileMIMEType;
    tmpList.append(tmpinfo);

    emit getFileInfoListDone(tmpList);
}

void URLHandler::getHTTPSFileList(const QString &url)
{

}

void URLHandler::getFTPFileList(const QString &url)
{

}

void URLHandler::getBTFileList(const QString &url)
{

}

void URLHandler::getMetaLinkFileList(const QString &url)
{

}

void URLHandler::getMagnetFileList(const QString &url)
{

}

void URLHandler::getEd2kFileList(const QString &url)
{

}

void URLHandler::getYouGetFileList(const QString &url)
{
    //该指针指向另外一个被启动的程序，所以 绝对不能被delete
    yougetProcess = new QProcess(this);
    connect(yougetProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(getYouGetProcessFeedback()));
    connect(yougetProcess,SIGNAL(readyReadStandardError()),this,SLOT(getYouGetProcessError()));

    SettingXMLHandler tmpHandler;

    QStringList arguments;
    arguments << tmpHandler.getChildElement(SettingXMLHandler::YouGetSetting,"ExecutePath");
    arguments << "-i";
    arguments << url;
    yougetProcess->start("python3",arguments);
}

void URLHandler::getYouGetProcessFeedback()
{
    QString outPut = QString(yougetProcess->readAllStandardOutput());
    if (outPut == "")
        return;

    QList<TaskFileInfo> tmpList;
    if (outPut.contains("streams"))
        tmpList = getMultiFileInfo(outPut);
    else
        tmpList = getYouGetSingleFileInfo(outPut);

    emit getFileInfoListDone(tmpList);
}

QList<TaskFileInfo> URLHandler::getYouGetSingleFileInfo(const QString &data)
{
    int siteIndex = data.indexOf("Video Site:");
    int titleIndex = data.indexOf("Title:");
    int typeIndex = data.indexOf("Type:");
    int sizeIndex = data.indexOf("Size:");

    QString tmpSite = data.mid(siteIndex + 11, titleIndex - siteIndex - 11);
    QString tmpTitle = data.mid(titleIndex + 12,typeIndex - titleIndex - 13);
    QString tmpSize = data.mid(sizeIndex + 12,data.lastIndexOf("(") - sizeIndex - 17);

    TaskFileInfo tmpinfo;
    tmpinfo.fileName = tmpTitle;
    tmpinfo.fileType = "Videos";
    tmpinfo.fileSize = qint64(tmpSize.toDouble() * 1024 * 1024);//youget返回大小都以MiB计算,要转换成B

    QList<TaskFileInfo> infoList;
    infoList.append(tmpinfo);

    return infoList;
}

QList<TaskFileInfo> URLHandler::getMultiFileInfo(const QString &data)
{
    QString tmpSite = data.mid(data.indexOf("site:") + 20, data.indexOf("title:") - data.indexOf("site") - 21);
    QString tmpTitle = data.mid(data.indexOf("title:") + 20,data.indexOf("streams:") - data.indexOf("title:") - 21);
    QString tmpSize = data.mid(data.indexOf("size:") + 15,data.indexOf("MiB") - data.indexOf("size:") - 16);

    TaskFileInfo tmpinfo;
    tmpinfo.fileName = tmpTitle;
    tmpinfo.fileType = "Videos";
    tmpinfo.fileSize = qint64(tmpSize.toDouble() * 1024 * 1024);//youget返回大小都以MiB计算,要转换成B

    QList<TaskFileInfo> infoList;
    infoList.append(tmpinfo);

    return infoList;
}

void URLHandler::analyzeURL(const QString &url)
{
    URLHandler::ProtocolType tmpType = getProtocolType(url);
    switch(tmpType)
    {
    case URLHandler::YouGet:
        getYouGetFileList(url);
        break;
    case URLHandler::HTTP:
        getHTTPFileList(url);
        break;
    case URLHandler::HTTPS:
        getHTTPSFileList(url);
        break;
    case URLHandler::FTP:
        getFTPFileList(url);
        break;
    case URLHandler::BitTorrent:
        getBTFileList(url);
        break;
    case URLHandler::Metalink:
        getMetaLinkFileList(url);
        break;
    case URLHandler::Magnet:
        getMagnetFileList(url);
        break;
    case URLHandler::Ed2k:
        getEd2kFileList(url);
        break;
    default:
        break;
    }
}

void URLHandler::getYouGetProcessError()
{
    qDebug() << "error..."<<yougetProcess->readAllStandardError();
}

URLHandler::~URLHandler()
{

}

