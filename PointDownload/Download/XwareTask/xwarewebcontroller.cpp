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
    webview = new MainWebView();
    isLogined = false;
    loginCtrlTimer = new QTimer();
    loginTimeCount = 1;
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

    isInitedJSConnection = false;
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


void XwareWebController::startLoginCtrlTimer()
{
    if(loginTimeCount == LOGIN_MAX_TRY)
    {
        loginTimeCount = 1;
        loginCtrlTimer->stop();

        // emit this to javascript
        emit sLoginResult(x_LoginTimeOut);

         qDebug()<<"[xware fail] login time out ";
         return;
    }

    ++loginTimeCount;
    XwarePopulateObject::getInstance()->login(userName, userPwd);
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
    qDebug()<<"[xware info] login ...";

    this->userName = userName;
    this->userPwd = pwd;
    startLoginCtrlTimer();
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
    // need to clear window object from webview before this action
    /*   ...  */

    this->webview->reload();
}

QWebView * XwareWebController::getWebView()
{
    return this->webview;
}

void XwareWebController::tryAutomaticLogin(QString userName, QString pwd)
{
    this->userName = userName;
    this->userPwd = pwd;
    isHasAutoLoginTask = true;
}

bool XwareWebController::getLoginState()
{
    if(currentPageURL() == MAIN_URL_3 || currentPageURL() == MAIN_URL_OLD)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void XwareWebController::loadingFinished()
{
    if(currentPageURL() == MAIN_URL_3 && !isLogined)
    {
        // populate javascript to webview
        populateJavascript();

        isLogined = true;
        isHasAutoLoginTask = false;

        qDebug()<<"[xware info] finish login !";
        qDebug()<<"[xware info] init competed webview !";
        CompletedListWebView::getInstance()->init();

        emit sLoginResult(x_LoginSuccess);
    }
    else if(currentPageURL().contains(LOGIN_URL))
    {
        // populate javascript to webview
        populateJavascript();

        if(isLogined)
        {
            emit sLoginResult(x_Logout);  // logout xware
            isLogined = false;

            qDebug()<<"[xware info] logout ";
        }

        qDebug()<<"[xware info] login page ready ! ";

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
        // populate QT object into javascript
        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<"populate qt object to ==>" << currentPageURL();

//        XwarePopulateObject::getInstance()->disconnect(SIGNAL(XwarePopulateObject::getInstance()->sJSLogin()));
        webview->page()->mainFrame()->addToJavaScriptWindowObject("Point", XwarePopulateObject::getInstance());
    }
}

void XwareWebController::populateJavascript()
{
    QString filePath = "";
    if(currentPageURL().contains(LOGIN_URL) && !isInitedJSConnection)
    {
        filePath = ":/xware/resources/xware/xware_login.js";



        // temp
//        if(!isInitedJSConnection)
//        {
//            QFile file(":/xware/resources/xware/xware_connection.js");
//            qDebug()<<"              populate xware_connection js              ";
//            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//            {
//                if(XWARE_CONSTANTS_STRUCT.DEBUG)
//                    qDebug()<<"open error";
//                return;
//            }
//            QTextStream textInput(&file);
//            QString jsStr = textInput.readAll();
//            webview->page()->mainFrame()->evaluateJavaScript(jsStr);
//            file.close();
//            isInitedJSConnection = true;
//        }




    }
    else if(currentPageURL() == MAIN_URL_3)
    {
        filePath = ":/xware/resources/xware/xware_main.js";
    }

    else
    {
        return;
    }

    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"populate "<<filePath<<" to ==>" << currentPageURL();

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


//    if(currentPageURL().contains(LOGIN_URL))
//    {
//        // temp
//        if(!isInitedJSConnection)
//        {
//            QFile file(":/xware/resources/xware/xware_connection.js");
//            qDebug()<<"              populate xware_connection js              ";
//            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//            {
//                if(XWARE_CONSTANTS_STRUCT.DEBUG)
//                    qDebug()<<"open error";
//                return;
//            }
//            QTextStream textInput(&file);
//            QString jsStr = textInput.readAll();
//            webview->page()->mainFrame()->evaluateJavaScript(jsStr);
//            file.close();
//            isInitedJSConnection = true;
//        }
//    }

}

void XwareWebController::webUrlChanged(QUrl url)
{
   if(XWARE_CONSTANTS_STRUCT.DEBUG)
       qDebug()<<"URL changed ==>" << url.toString() ;

   if(url.toString() == MAIN_URL_3)
   {
       loginTimeCount = 0;
       loginCtrlTimer->stop();
       qDebug()<<"[xware info] login success, initialise binding ...";
   }

    if(url.toString() != MAIN_URL_3 &&  !url.toString().contains(LOGIN_URL))
    {
            webview->triggerPageAction(QWebPage::Stop);
            webview->page()->mainFrame()->load(QUrl(MAIN_URL_3));
    }

}

