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

#include "topcontrl.h"
#include <QtQml>

//构建单例对象
TopContrl * TopContrl::topControl = NULL;
TopContrl * TopContrl::getInstance()
{
    if (topControl == NULL)
    {
        topControl = new TopContrl();
    }
    return topControl;
}


//for ubuntu only+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef DESKTOP_ENV_UBUNTU
void gtkShowMainWindow(GtkMenu *menu, gpointer data)
{
    TopContrl::getInstance()->showMainWindow();
}

void gtkShowAboutWindow(GtkMenu *menu, gpointer data)
{
    TopContrl::getInstance()->showAboutWindow();
}

void gtkCheckUpdate(GtkMenu *menu, gpointer data)
{
    TopContrl::getInstance()->checkUpdate();
}

void gtkCompletelyExit(GtkMenu *menu, gpointer data)
{
    Q_UNUSED(menu);
    //做相应的数据保存处理后再退出
    qApp->quit();
}
#endif
//for ubuntu only+++++++++++++++++++++++++++++++++++++++++++++++++++++++++


TopContrl::TopContrl(QObject *parent) :
    QObject(parent)
{
    //import时使用Singleton.TopContrl，在获取内容或调用函数时使用PEventFilter
    qmlRegisterSingletonType<TopContrl>("Singleton.TopContrl", 1, 0, "TopContrl", pTopContrlObj);

    //initTrayIcon(); 改为由main函数调用，以保证此类初始化在qml初始化之前
    updateShowState(true);
}

void TopContrl::showSaveFolder(QString path)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void TopContrl::showSaveFolder()
{
    SettingXMLHandler tmpHandler;
    //fromLocalFile:解决中文路径无法打开问题
    QDesktopServices::openUrl(QUrl::fromLocalFile(tmpHandler.getChildElement(GeneralSettings,"SavePath")));
}

void TopContrl::showTrayIcon()
{
    if (sysTrayIcon)
    {

    }
}

void TopContrl::updateShowState(bool isShow)
{
    isMainWindowShowed = isShow;
}

void TopContrl::destroyAll()
{
    //做相应的数据保存处理后再退出
    emit signalAllDestroy();

    qApp->quit();
}

void TopContrl::initTrayIcon()
{
    if (QSystemTrayIcon::isSystemTrayAvailable())
    {
#ifdef DESKTOP_ENV_UBUNTU
        showUnityAppIndicator();
#else
        showQtTrayIcon();
#endif
    }
}

void TopContrl::createTrayAction()
{
    QAction * showMainAction = new QAction(0);
    showMainAction->setText(tr("Open Main Windown"));//"打开程序主界面"
    showMainAction->setIcon(QIcon(":/images/trayicon/home"));

    QAction * showAboutAction = new QAction(0);
    showAboutAction->setText(tr("About"));//"关于"
    showAboutAction->setIcon(QIcon(":/images/trayicon/about"));

    QAction * showCheckUpdate = new QAction(0);
    showCheckUpdate->setText(tr("Check Update"));//"检查更新"
    showCheckUpdate->setIcon(QIcon(":/images/trayicon/update"));

    QAction * quitAction = new QAction(0);
    quitAction->setText(tr("Quit"));//"退出"
    quitAction->setIcon(QIcon(":/images/trayicon/quit"));

    trayMenu->addAction(showMainAction);
    trayMenu->addAction(showAboutAction);
    trayMenu->addAction(showCheckUpdate);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);

    connect(showMainAction, SIGNAL(triggered()),this, SLOT(showMainWindow()));
    connect(showAboutAction, SIGNAL(triggered()), this, SLOT(showAboutWindow()));
    connect(showCheckUpdate, SIGNAL(triggered()), this, SLOT(checkUpdate()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(completelyExit()));
}


//for ubuntu only+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef DESKTOP_ENV_UBUNTU
void TopContrl::showUnityAppIndicator()
{
    AppIndicator *indicator;
    GtkWidget *menu;

    //action
    GtkWidget * showMainWinAction = gtk_menu_item_new_with_label("Open Main Windown");
    GtkWidget * aboutAction = gtk_menu_item_new_with_label("About");
    GtkWidget * checkUpdateAction = gtk_menu_item_new_with_label("Check Update");
    GtkWidget * separator = gtk_separator_menu_item_new();
    GtkWidget * exitAction = gtk_menu_item_new_with_label("Quit");

    menu = gtk_menu_new();

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), showMainWinAction);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), aboutAction);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), checkUpdateAction);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), separator);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), exitAction);

    //connect signal
    g_signal_connect(showMainWinAction, "activate", G_CALLBACK(gtkShowMainWindow), qApp);
    g_signal_connect(aboutAction, "activate", G_CALLBACK(gtkShowAboutWindow), qApp);
    g_signal_connect(checkUpdateAction, "activate", G_CALLBACK(gtkCheckUpdate), qApp);
    g_signal_connect(exitAction, "activate", G_CALLBACK(gtkCompletelyExit), qApp);

    gtk_widget_show(showMainWinAction);
    gtk_widget_show(aboutAction);
    gtk_widget_show(checkUpdateAction);
    gtk_widget_show(separator);
    gtk_widget_show(exitAction);

    indicator = app_indicator_new(
    "unique-application-name",
        "/opt/Point/PointDownload/point.png",
      APP_INDICATOR_CATEGORY_APPLICATION_STATUS
    );

    app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
    app_indicator_set_menu(indicator, GTK_MENU(menu));
}
#endif
//for ubuntu only+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void TopContrl::showQtTrayIcon()
{
    //Show the SystemTrayIcon the Qt way
    trayMenu = new QMenu();
    createTrayAction();

    sysTrayIcon = new QSystemTrayIcon(0);
    sysTrayIcon->setContextMenu(trayMenu);
    sysTrayIcon->setIcon(QIcon(":/images/main/point-32-b"));
    sysTrayIcon->setVisible(true);
    sysTrayIcon->show();

    connect(sysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(getTrayAction(QSystemTrayIcon::ActivationReason)));
}

void TopContrl::showMainWindow()
{
    isMainWindowShowed = true;
    emit signalShowMainWindow();
}

void TopContrl::hideMainWindow()
{
    isMainWindowShowed = false;
    emit signalHideMainWindow();
}

void TopContrl::showAboutWindow()
{
    emit signalShowAboutPoint();
}

void TopContrl::checkUpdate()
{
    QDesktopServices::openUrl(QUrl("http://www.linuxdeepin.com/forum/23/21124"));
}

void TopContrl::completelyExit()
{
    //做相应的数据保存处理后再退出
    emit signalAllDestroy();

    qApp->quit();
}

void TopContrl::getTrayAction(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        if (!isMainWindowShowed)
        {
            emit signalShowMainWindow();
            updateShowState(true);
        }
        else
        {
            emit signalHideMainWindow();
            updateShowState(false);
        }
    }
}


