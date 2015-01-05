/***********************************************************************
*PointDownload
*Copyright (C) 2014~2015  PointTeam
*
* Author:     起点 <88231398@qq.com>
* Maintainer: 起点 <88231398@qq.com>
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
#include "monitorClipBoard.h"
#include <QtQml>
#include "qdebug.h"

MonitorClipBoard::MonitorClipBoard()
{
    //import时使用Singleton.MonitorClipBoard
    qmlRegisterSingletonType<MonitorClipBoard>("Singleton.MonitorClipBoard", 1, 0, "MonitorClipBoard", clipboardObj);

    setTmpURL(tr("Download URL"));
    clipBoard = QApplication::clipboard();
    connect( clipBoard, SIGNAL( dataChanged() ), this, SLOT( slot_clipDataChange() ) );
}

MonitorClipBoard * MonitorClipBoard::monitorClipBord = NULL;
MonitorClipBoard * MonitorClipBoard::getInstance()
{
    if (monitorClipBord == NULL)
        monitorClipBord = new MonitorClipBoard();
    return monitorClipBord;
}

QObject *MonitorClipBoard::clipboardObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return MonitorClipBoard::getInstance();
}

void MonitorClipBoard::slot_clipDataChange()
{
    setTmpURL(clipBoard->text());
}


QString MonitorClipBoard::getTmpURL()
{
    return tmpURL;
}

void MonitorClipBoard::setTmpURL(QString URL)
{
    if (!isLegalURL(URL))
        return;

    tmpURL = QString(URL.toUtf8());
    emit tmpURLChange();
}

bool MonitorClipBoard::isLegalURL(QString URL)
{
    QRegExp rx;
    rx.setPatternSyntax(QRegExp::RegExp);

    QString normalURLRegex = QString("^((https|http|chrome)://)?")
            + QString(".*\\.(exe|asf|avi|exe|iso|mp3|mpeg|mpg|mpga|ra|rar|rm|rmvb|tar|wma|wmp|wmv|mov|zip|3gp|")
            + QString("chm|mdf|torrent|jar|msi|arj|bin|dll|psd|hqx|sit|lzh|gz|tgz|xlsx|xls|doc|docx|ppt|pptx|flv|swf|mkv|")
            + QString("tp|ts|flac|ape|wav|aac|txt|dat|7z|ttf|bat|xv|xvx|pdf|mp4|apk|ipa|epub|mobi|deb|sisx|cab|pxl|run|rpm|deb|dmg)")
            + QString("($|\\?.*$)");

    QString videoURLRegex = QString("^(http://www\\.tudou\\.com/|") +
            QString("http://v\\.yinyuetai\\.com/|") +
            QString("http://v\\.youku\\.com/| ")+
            QString("http://v\\.ku6\\.com/|")+
            QString("http://v\\.163\\.com/|") +
            QString("http://v\\.qq\\.com/|") +
            QString("http://www\\.acfun\\.com/v/|")+
            QString("http://bilibili\\.kankanews\\.com/video/av|")+
            QString("http://www\\.jpopsuki\\.tv/video/|")+
            QString("http://video\\.sina\\.com\\.cn/|")+
            QString("http://tv\\.sohu\\.com/|")+
            QString("http://www\\.56\\.com/w|")+
            QString("http://www\\.56\\.com/u|")+
            QString("http://www\\.songtaste\\.com/song/).+");

    rx.setPattern(normalURLRegex);
    int normalPos = URL.indexOf(rx);

    if (normalPos >= 0)
        return true;

    rx.setPattern(videoURLRegex);
    int videoPos = URL.indexOf(rx);

    if (videoPos >= 0)
        return true;

    if(isXwareParseType(URL))
    {
        return true;
    }

    return false;                  //排除两种可能性外,就是不合法的链接
}

bool MonitorClipBoard::isXwareParseType(QString URL)
{
    QString str = QString("^(ftp|magnet|ed2k|thunder|mms|rtsp)?:.*");
    QRegExp rex(str);
    return rex.exactMatch(URL);
}
