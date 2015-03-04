/***********************************************************************
*PointDownload
*Copyright (C) 2014~2015  PointTeam
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
#include "peventfilter.h"
#include "Controler/SettingWin/settingcontroler.h"
#include "Controler/SettingWin/dropzonesettingcontroler.h"
#include "Controler/SettingWin/yougetsettingcontroler.h"
#include "Controler/SettingWin/xwaresettingcontroler.h"
#include "Controler/topcontrl.h"

#include "qtsinglecoreapplication.h"
#include "Controler/monitorClipBoard.h"
#include "Controler/dldataconverter.h"
#include "Download/XwareTask/XwareConstants.h"
#include "Download/XwareTask/webctrlviewtest.h"
#include "normalnotice.h"

#include "taskinfo.h"

int main(int argc, char *argv[])
{
    QtSingleCoreApplication app(argc, argv);

    if (app.isRunning())
        return 0;
    QLocalSocket socket;
    socket.connectToServer("PointURLServer");
    if (socket.waitForConnected(100))
        return 0;

    QString local = QLocale::system().name();
    QTranslator translator;
    translator.load(QString(":/languages/:/languages/resources/LANG/PointDownload_") + local);
    app.installTranslator(&translator);

    // 为程序设置一个Icon
    app.setWindowIcon(QIcon(QPixmap(":/images/main/point-32-b")));

    //这样能保证系统托盘类的初始化在qml初始化之前完成，避免造 成gtk的一些错误
    NormalNotice::getInstance();
    TopContrl::getInstance()->initTrayIcon();
    DLDataConverter::getInstance();
    PEventFilter::getInstance();
    MonitorClipBoard::getInstance();
    DropzoneSettingControler::getInstance();
    MiddleSender::getInstance();
    XwareTaskEntity::getInstance();
    XwareTask::getInstance();
    //如果符合条件，则自动登陆xware
    XwareSettingControler::getInstance()->tryAutomaticLogin();

    //注册的参数格式：import settingControler 1.0
    qmlRegisterType<SettingControler>("settingControler", 1, 0, "SettingControler");
    qmlRegisterType<YouGetSettingControler>("youGetSettingControler", 1, 0, "YouGetSettingControler");

    QQmlApplicationEngine engin(QUrl("qrc:/qml/qml/PointDownload/main.qml"));
    Q_UNUSED(engin);

   //添加全局事件过滤
   app.installEventFilter(PEventFilter::getInstance());

   // Xware Test View
   if(XWARE_CONSTANTS_STRUCT.DEBUG_2)
   {
       WebCtrlViewTest::getInstance()->show();
   }

   return app.exec();
}

