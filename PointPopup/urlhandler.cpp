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

    qDebug() << outPut << "===";
//    QStringList tmpList;
//    if (outPut.contains("streams"))
//        tmpList = getMovieYouGetFeedBackInfo(outPut);
//    else
//        tmpList = getNormalYouGetFeedBackInfo(outPut);

//    if (tmpList.count() != 3)
//        return;

//     setFileNameList(tmpList.at(0) + ITEM_INFO_SPLIT_CHAR + tmpList.at(1) + ITEM_INFO_SPLIT_CHAR + tmpList.at(2));
//     emit sFnishGetAllInfo();
}

void URLHandler::getFileInfoList(const QString &url)
{

}

void URLHandler::getYouGetProcessError()
{

}

URLHandler::~URLHandler()
{

}

