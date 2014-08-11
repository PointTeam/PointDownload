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

#ifndef TOPCONTRL_H
#define TOPCONTRL_H

#include <QObject>
#include <QApplication>
#include <QProcess>
#include <QDesktopServices>
#include <QSystemTrayIcon>
#include <QQmlEngine>
#include <QMenu>
#include <QUrl>
#include <QDebug>
#include "XMLHandler/settingxmlhandler.h"

////for ubuntu only+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#undef signals
//extern "C" {
//  #include <libappindicator/app-indicator.h>
//  #include <gtk/gtk.h>

//  void quitIndicator(GtkMenu *, gpointer);

//}
//#define signals public
////for ubuntu only+++++++++++++++++++++++++++++++++++++++++++++++++++++++++


class TopContrl : public QObject
{
    Q_OBJECT
public:
    static TopContrl * getInstance();

    void initTrayIcon();

    //qml中能直接调用此方法
    Q_INVOKABLE void showSaveFolder(QString path);
    Q_INVOKABLE void showSaveFolder();
    Q_INVOKABLE void showTrayIcon();
    Q_INVOKABLE void updateShowState(bool isShow);

signals:
    void signalShowMainWindow();
    void signalHideMainWindow();
    void signalShowAboutPoint();

public slots:
    Q_INVOKABLE void showMainWindow();
    Q_INVOKABLE void hideMainWindow();
    Q_INVOKABLE void showAboutWindow();
    Q_INVOKABLE void checkUpdate();
    void completelyExit();

private slots:
    void getTrayAction(QSystemTrayIcon::ActivationReason reason);
private:
     QSystemTrayIcon * sysTrayIcon;
     QMenu * trayMenu;

     bool isMainWindowShowed;
private:
     explicit TopContrl(QObject *parent = 0);

     static TopContrl * topControl;

     void createTrayAction();
     void showUnityAppIndicator();
     void showQtTrayIcon();
};

//将单例对象注册到qml中使用的回调函数
static QObject * pTopContrlObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return TopContrl::getInstance();
}

#endif // TOPCONTRL_H
