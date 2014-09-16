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

#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QTranslator>
#include <control/datacontroler.h>
#include "control/peventfilter.h"

QString getChromeURL()
{
    unsigned int length = 0;
    //read the first four bytes (=> Length)
    //getwchar: receive char from stdin
    //putwchar: write char to stdout
    QString headString = "";
    for (int i = 0; i < 4; i++)
    {
        char tmpChar = getwchar();
        headString += tmpChar;
        length += tmpChar;
    }

    //read the json-message
    QString fileURL = "";

    if (length > 200)
    {
        fileURL += headString;
        while(1)
        {
            char tmpChar = getwchar();
            if (tmpChar == WEOF)
                break;
            else
                fileURL += tmpChar;
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            fileURL += getwchar();
        }

        QString::number(length);
        //浏览器端传来的数据会有一个双引号引在两端
        fileURL = fileURL.mid(1,fileURL.length()-2);
    }

    return fileURL;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString local = QLocale::system().name();
    QTranslator translator;
    translator.load(QString(":/LANG/PointPopup_") + local);
    app.installTranslator(&translator);

//    QString fileURL = QString(argv[argc - 1]);
    QString fileURL = "";

    QStringList urlList = QString(argv[argc - 1]).split("#..#");

    if (urlList.at(0) == QString("FIREFOX"))//firefox
    {
        fileURL = QString(urlList.at(1));
    }
    else//chrome
    {
        fileURL = getChromeURL();
    }

    DataControler::getInstance()->getURLFromBrowser(fileURL);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    //    //添加全局事件过滤
    app.installEventFilter(PEventFilter::getInstance());

    return app.exec();
}

