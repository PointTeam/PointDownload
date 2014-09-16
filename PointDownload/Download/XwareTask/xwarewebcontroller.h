/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Choldrim <choldrim@foxmail.com>
* Maintainer: Choldrim <choldrim@foxmail.com>
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

#ifndef XWAREWEBCONTROLLER_H
#define XWAREWEBCONTROLLER_H

#define MAIN_URL_3 "http://yuancheng.xunlei.com/3/"
#define MAIN_URL_OLD "http://yuancheng.xunlei.com/"
#define LOGIN_URL  "http://yuancheng.xunlei.com/login.html"
#define LOGIN_MAX_TRY 5
#define LOGIN_DEFAULT_INTERVAL 2000

#include <QObject>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>
#include <QUrl>
#include <QTimer>
#include <QFile>
#include <QTextStream>

#include "XwareDataType.h"
#include "xwarepopulateobject.h"
#include "mywebview.h"
#include "XwareConstants.h"
#include "completedlistwebview.h"
#include "xwaresetting.h"

class XwareWebController : public QObject
{
    Q_OBJECT
public:
    ~XwareWebController();
    static XwareWebController *getInstance();

    void executeJS(QString js); // execute javascript
    QString setElemValueById(QString id, QString value); //

    void login(QString userName, QString pwd);
    void logout();
    QString currentPageURL();
    void reloadWebView();
    QWebView *getWebView();
    void tryAutomaticLogin(QString userName, QString pwd);
    bool getLoginState();

signals:
    void sLoginResult(XwareLoginResultType);

public slots:

private slots:
    void loadingFinished();
    void populateQtObject();
    void populateJavascript();  // populate default javascript to webview
    void webUrlChanged(QUrl url);
    void startLoginCtrlTimer();  // try to login, a slot of login-timer

private:
    explicit XwareWebController(QObject *parent = 0);
    
private:
    static XwareWebController * xwareWebController;

    QWebView * webview;

    QString URL3;
    bool isLogined;
    QString userName;
    QString userPwd;
    QTimer * loginCtrlTimer;
    int loginTimeCount;
    bool isHasAutoLoginTask;   // 仅在程序刚启动并且有自动登录记录时置true
};

#endif // XWAREWEBCONTROLLER_H
