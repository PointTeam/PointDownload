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

#include "xwarewebcontroller.h"

XwareWebController::XwareWebController(QObject *parent) :
    QObject(parent)
{
    webview = new MyWebView();
    isLogined = false;
    loginCtrlTimer = new QTimer();
    loginTimeCount = 0;
    isHasAutoLoginTask = false;

    // set default url
    webview->setUrl(QUrl(LOGIN_URL));

    // loading finish
    connect(webview, SIGNAL(loadFinished(bool)), this, SLOT(loadingFinished()));

    // populate Qt object to javascript
    connect(webview->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(populateQtObject()));

    // url change
    connect(webview, SIGNAL(urlChanged(QUrl)), this, SLOT(webUrlChanged(QUrl)), Qt::QueuedConnection);

    // login control timer
    connect(loginCtrlTimer, SIGNAL(timeout()), this, SLOT(startLoginCtrlTimer()));
}

void XwareWebController::startLoginCtrlTimer()
{
    if(loginTimeCount > LOGIN_MAX_TRY)
    {
        loginTimeCount = 0;
        loginCtrlTimer->stop();

        // emit this to javascript
        emit sLoginResult(x_LoginTimeOut);

        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<"xware login time out !!";
    }

    ++loginTimeCount;
    XwarePopulateObject::getInstance()->login(userName, userPwd);
}

XwareWebController * XwareWebController::xwareWebController = NULL;
XwareWebController::~XwareWebController()
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"~XwareWebController()  was be called !!";
}

XwareWebController * XwareWebController::getInstance()
{
    if (xwareWebController == NULL)
        xwareWebController = new XwareWebController();
    return xwareWebController;
}

void XwareWebController::executeJS(QString js)
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"execute js ==> "<<js;

    webview->page()->mainFrame()->evaluateJavaScript(js);
}

QString XwareWebController::setElemValueById(QString id, QString value)
{
    return QString("$(\"#"+ id + "\").val(\"" + value + "\");");
}

void XwareWebController::login(QString userName, QString pwd)
{
    this->userName = userName;
    this->userPwd = pwd;
//    startLoginCtrlTimer();
    loginCtrlTimer->start(LOGIN_DEFAULT_INTERVAL);
}

void XwareWebController::logout()
{
    XwarePopulateObject::getInstance()->logout();
}

QString XwareWebController::currentPageURL()
{
    return webview->url().toString();
}

void XwareWebController::reloadWebView()
{
    this->webview->reload();
}

void XwareWebController::tryAutomaticLogin(QString userName, QString pwd)
{
    this->userName = userName;
    this->userPwd = pwd;
    isHasAutoLoginTask = true;
}

void XwareWebController::loadingFinished()
{
    if(currentPageURL() == MAIN_URL_3 && !isLogined)
    {
        isLogined = true;
        isHasAutoLoginTask = false;
        emit sLoginResult(x_LoginSuccess);

        qDebug()<<"[info] finish login !";
    }
    else if(currentPageURL() == LOGIN_URL)
    {
        if(isLogined)
        {
            emit sLoginResult(x_Logout);  // logout xware
            isLogined = false;

            qDebug()<<"[info] logout ";
        }

        // 仅在程序刚启动并且有自动登录记录时调用
        if(isHasAutoLoginTask)
        {
            this->login(userName, userPwd);
        }
    }
}

void XwareWebController::populateQtObject()
{
    if ((currentPageURL() == MAIN_URL_3) || (currentPageURL() == LOGIN_URL))
    {
        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<"populate object to ==>" << currentPageURL();

        // (1) populate QT object into javascript
        webview->page()->mainFrame()->addToJavaScriptWindowObject("Point", XwarePopulateObject::getInstance());

        // (2) populate javascript file to javascript
        QString filePath = "";
        if(currentPageURL() == LOGIN_URL)
        {
            filePath = ":/xware/resources/xware/xware_login.js";
        }
        else if(currentPageURL() == MAIN_URL_3)
        {
            filePath = ":/xware/resources/xware/xware_main.js";
        }

        QFile file(filePath);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            if(XWARE_CONSTANTS_STRUCT.DEBUG)
                qDebug()<<"open error";
            return;
        }
        QTextStream textInput(&file);
        QString jsStr = textInput.readAll();
        webview->page()->mainFrame()->evaluateJavaScript(jsStr);
        file.close();
    }
}

void XwareWebController::webUrlChanged(QUrl url)
{
   if(XWARE_CONSTANTS_STRUCT.DEBUG)
       qDebug()<<"URL changed ==>" << url.toString() ;

   if(url.toString() == LOGIN_URL)
   {
       qDebug()<<"[xware info] login page ready ! ";
   }

   if(url.toString() == MAIN_URL_3)
   {
       loginTimeCount = 0;
       loginCtrlTimer->stop();
       qDebug()<<"[xware info] login success, initialise ...";
   }

    if(url.toString() != MAIN_URL_3 &&  currentPageURL() != LOGIN_URL)
    {
            webview->triggerPageAction(QWebPage::Stop);
            webview->page()->mainFrame()->load(QUrl(MAIN_URL_3));
    }

}

