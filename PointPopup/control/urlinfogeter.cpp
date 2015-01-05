#include "urlinfogeter.h"

URLInfoGeter::URLInfoGeter(QLocalSocket * socket, QString url, QObject *parent) :
    QThread(parent)
{
    Q_UNUSED(socket);
    mURL = url;
}

void URLInfoGeter::run()
{
    mLocalSocket = new QLocalSocket();
    connect(mLocalSocket, SIGNAL(readyRead()),  this ,SLOT(slotGetInfoFromServer()));
    // 服务端的serverNewConnectionHandler成员方法将被调用
    mLocalSocket->connectToServer("PointURLServer");
    if (mLocalSocket->waitForConnected())
    {
        qDebug() << "connect to main program success...";
        // TODO:
    }
    else
    {
        qDebug() << "connect faild...";
        emit sGetInfoFaild(true);
        return;
    }

    TaskInfo taskInfo;
    taskInfo.toolType = TOOL_XWARE_PARSE;
//    taskInfo.rawUrl = QUrl(mURL);    // altered by choldrim
    taskInfo.rawUrl = mURL;

    mLocalSocket->write(taskInfo.toQByteArray());
    mLocalSocket->flush();

    mLocalSocket->waitForReadyRead();
}

void URLInfoGeter::slotGetInfoFromServer()
{
    TaskInfo taskInfo(mLocalSocket);

    QList<TaskFileItem> tmpList = taskInfo.fileList;
    QString allFileInfos = "";
    for (int i = 0; i < tmpList.length(); i ++)
    {
        allFileInfos += i > 0 ? "#:#" : "";
        allFileInfos += getFileTypeByName(tmpList.at(i).fileName) + "@:@"
                + QString::number(tmpList.at(i).fileSize) + "@:@"
                + tmpList.at(i).fileName;
    }

    emit sGetAllFileInfo(allFileInfos);
}


QString URLInfoGeter::getFileTypeByName(QString fileName)
{
    QString vidioRexStr = QString(".*\\.(asf|avi|wm|wmp|wmv|ram|rm|rmvb|rp|rt|")
            + QString("smil|scm|dat|m1v|m2v|m2p|m2ts|mp2v|mpe|mpeg|")
            + QString("mpeg1|mpeg2|mpg|mpv2|pss|pva|tp|tpr|ts|m4b|")
            + QString("m4p|m4v|mp4|mpeg4|3g2|3gp|3gp2|3gpp|mov|qt|")
            + QString("flv|f4v|hlv|ifo|vob|amv|csf|divx|evo|mkv|mod|")
            + QString("pmp|vp6|vik|mts|xvx|xv|xlmv|ogm|ogv|ogx|dvd)$");
    QRegExp rex(vidioRexStr);
    if(rex.exactMatch(fileName))
    {
//        QString suffix = fileName.section("\.", -1);
        return "video/mp4";
    }

    // tmp
    return "application/x-gzip";
}

QString URLInfoGeter::convertToByteUnit(QString size)
{
    if(size.contains("G", Qt::CaseInsensitive))
    {
        double num = size.split("G", QString::SkipEmptyParts, Qt::CaseInsensitive).at(0).toDouble();
        return QString::number((long long)(num * 1024 * 1024 * 1024));
    }

    if(size.contains("M", Qt::CaseInsensitive))
    {
        double num = size.split("M", QString::SkipEmptyParts, Qt::CaseInsensitive ).at(0).toDouble();
        return QString::number((long long)(num * 1024 * 1024));
    }

    if(size.contains("K", Qt::CaseInsensitive))
    {
        double num = size.split("K", QString::SkipEmptyParts, Qt::CaseInsensitive).at(0).toDouble();
        return QString::number((long long)(num * 1024));
    }

    return size.split("B", QString::SkipEmptyParts, Qt::CaseInsensitive).at(0);
}

