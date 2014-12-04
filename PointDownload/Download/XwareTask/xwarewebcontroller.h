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
#define LOGIN_MAX_TRY 1
#define LOGIN_MAX_TIMEOUT 5
#define LOGIN_DEFAULT_INTERVAL 1000

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

    // javascript
    void executeJS(QString js); // execute javascript
    QString setElemValueById(QString id, QString value);

    void login(QString userName, QString pwd, QString vertifyCode = QString(""));
    void logout();

    void initWebView();
    QWebView * reInitWebView();
    QString currentPageURL();
    QWebView *getWebView();

    // reload/reflash
    void reloadWebView();

    // auto login
    void tryAutomaticLogin(QString userName, QString pwd);

    // return whether the login state is login
    XwareLoginState getLoginState();


signals:
    void sLoginResult(XwareLoginResultType);
    void sLoginStateChanged(XwareLoginState);

public slots:

private slots:
    void loadingFinished(bool noError);
    void populateQtObject();
    void populateJavascript();  // populate default javascript to webview
    void webUrlChanged(QUrl url);
    void startLoginCtrlTimer();  // try to login, a slot of login-timer
    void loginStateChanged(XwareLoginState state);
    void bindRouterCodeResultHandle(int rs);
    void loginErrorHandle(QString, QString);

private:
    explicit XwareWebController(QObject *parent = 0);
    
private:
    static XwareWebController * xwareWebController;

    QWebView * webview;

    // login state
    XwareLoginState loginState;

    // login param
    QString userName;
    QString userPwd;
    QString vertifyCode;

    QTimer * loginCtrlTimer;
    int loginTimeCount;
    bool isHasAutoLoginTask;   // 仅在程序刚启动并且有自动登录记录时置true

    bool initLoginJsState;
    bool showLoginReadyHint;
};

#endif // XWAREWEBCONTROLLER_H
