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

#include <QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <qquickitem.h>
#include <QQuickWindow>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include "Controler/middlesender.h"
#include "Controler/peventfilter.h"
#include "Controler/SettingWin/settingcontroler.h"
#include "Controler/SettingWin/dropzonesettingcontroler.h"
#include "Controler/SettingWin/yougetsettingcontroler.h"
#include "Controler/SettingWin/xwaresettingcontroler.h"
#include "Controler/topcontrl.h"

#include "Controler/monitorClipBoard.h"
#include "Controler/downloaddatasender.h"
#include "qtsinglecoreapplication.h"


int main(int argc, char *argv[])
{
    QtSingleCoreApplication app(argc, argv);
    if (app.isRunning())
    {
        return 0;
    }

    QString local = QLocale::system().name();
    QTranslator translator;
    translator.load(QString(":/languages/:/languages/resources/LANG/PointDownload_") + local);
    app.installTranslator(&translator);

    //这样能保证系统托盘类的初始化在qml初始化之前完成，避免造 成gtk的一些错误
    TopContrl::getInstance()->initTrayIcon();
    DownloadDataSender::getInstance();
    PEventFilter::getInstance();
    MonitorClipBoard::getInstance();
    DropzoneSettingControler::getInstance();
    MiddleSender::getInstance();
    //如果符合条件，则自动登陆xware
    XwareSettingControler * xCtrl = new XwareSettingControler;
    xCtrl->tryAutomaticLogin();
    delete xCtrl;
    xCtrl = NULL;

    //注册的参数格式：import settingControler 1.0
    qmlRegisterType<SettingControler>("settingControler", 1, 0, "SettingControler");
    qmlRegisterType<YouGetSettingControler>("youGetSettingControler", 1, 0, "YouGetSettingControler");
    qmlRegisterType<XwareSettingControler>("xwareSettingControler", 1, 0, "XwareSettingControler");

    QQmlApplicationEngine engin(QUrl("qrc:/qml/qml/PointDownload/main.qml"));

   //添加全局事件过滤
   app.installEventFilter(PEventFilter::getInstance());

    return app.exec();
}

