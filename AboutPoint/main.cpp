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
#include <QTranslator>
#include <QQmlApplicationEngine>

#include "qtsinglecoreapplication.h"
int main(int argc, char *argv[])
{
//    QGuiApplication app(argc, argv);

    QtSingleCoreApplication app(argc, argv);
    if (app.isRunning())
    {
        return 0;
    }

    QString local = QLocale::system().name();
    QTranslator translator;
    translator.load(QString(":/languages/resources/LANG/AboutPoint_") + local + ".qm");
    app.installTranslator(&translator);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/AboutPoint/main.qml")));

    return app.exec();
}
