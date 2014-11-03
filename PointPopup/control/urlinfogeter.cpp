#include "urlinfogeter.h"

URLInfoGeter::URLInfoGeter(QLocalSocket * socket, QString &url, QObject *parent) :
    QThread(parent)
{
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

    mURL = xwareParseURLHander + mURL;
    // send this url or bt file to main window, and let it is parsed by xware
    mLocalSocket->write(mURL.toStdString().c_str());
    mLocalSocket->flush();

    // restore URL
    mURL = mURL.split(xwareParseURLHander).at(1);
    mLocalSocket->waitForReadyRead();
}

void URLInfoGeter::slotGetInfoFromServer()
{
    QTextStream stream(mLocalSocket);
    QString msg = stream.readAll();
    msg = msg.trimmed();

    if(msg.startsWith("XwareMsgType"))
    {
        if(msg.split(xwareSpliterBtwData).at(1) == "XwareNotStart")
        {
            qDebug()<<"[info]xware doesn't start now, you need to login thunder and try again later";
            emit sGetInfoFaild(false);
            return;
        }
    }

    QStringList files = msg.split(xwareSpliterEnd);
    QString allFileInfo = "";
    foreach (QString file, files)
    {
        if(file.length() == 0)continue;

        // format: fileName #..# fileSize
        QStringList fileInfoList = file.split(xwareSpliterBtwData);

        // get mine type by name
        QString fileType = getFileTypeByName(fileInfoList.at(0));

        QString fileSize = convertToByteUnit(fileInfoList.at(1));

        // changed to type@:@size@:@name#:#
        QString singleFileInfo = fileType + ITEM_INFO_SPLIT_CHAR
                + fileSize + ITEM_INFO_SPLIT_CHAR
                + fileInfoList.at(0) + "#:#";
        allFileInfo += singleFileInfo;
    }

    emit sGetAllFileInfo(allFileInfo);

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
    if(size.contains("G"))
    {
        double num = size.split("G").at(0).toDouble();
        return QString::number((long long)(num * 1024 * 1024 * 1024));
    }

    if(size.contains("M"))
    {
        double num = size.split("M").at(0).toDouble();
        return QString::number((long long)(num * 1024 * 1024));
    }

    if(size.contains("K"))
    {
        double num = size.split("K").at(0).toDouble();
        return QString::number((long long)(num * 1024));
    }

    return size.split("B").at(0);
}

