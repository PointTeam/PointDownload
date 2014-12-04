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
    // init the web view
    initWebView();

    // bind login state changed
    connect(this, SIGNAL(sLoginStateChanged(XwareLoginState)), this, SLOT(loginStateChanged(XwareLoginState)));
    connect(XwareController::getInstance(), SIGNAL(sBindRouterCodeResult(int)), this, SLOT(bindRouterCodeResultHandle(int)));
    connect(XwarePopulateObject::getInstance(), SIGNAL(sLoginError(QString, QString)), this, SLOT(loginErrorHandle(QString, QString)));

    // init login state
    emit sLoginStateChanged(LoginNotReady);

    loginCtrlTimer = new QTimer();
    loginCtrlTimer->setInterval(LOGIN_DEFAULT_INTERVAL);
    loginTimeCount = 0;
    isHasAutoLoginTask = false;

    // login control timer
    connect(loginCtrlTimer, SIGNAL(timeout()), this, SLOT(startLoginCtrlTimer()));

    initLoginJsState = false;
    showLoginReadyHint = true;
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
    if(loginTimeCount < LOGIN_MAX_TIMEOUT)
    {
        ++loginTimeCount;
    }

    else
    {
        loginTimeCount = 0;
        loginCtrlTimer->stop();

        // emit this to javascript
        emit sLoginResult(x_LoginTimeOut);

        emit sLoginStateChanged(LoginReady);

        NormalNotice::getInstance()->showMessage(tr("Login timeout"), Notice_Color_Error,
                  tr("Please check the network or restart the Point to try again"));
    }

}

void XwareWebController::loginStateChanged(XwareLoginState state)
{
    this->loginState = state;
}

void XwareWebController::bindRouterCodeResultHandle(int rs)
{
    if(rs == 1)
    {
        emit sLoginStateChanged(LoginedAndBinded);

        NormalNotice::getInstance()->showMessage(tr("Login successful"), Notice_Color_Success,
                                                 tr("Thunder is available now!"));

        qDebug()<<"[xware info] Binding successful! => Login successful ";
    }
    else if(rs == 0)
    {
        emit sLoginStateChanged(LoginReady);
    }
}

void XwareWebController::loginErrorHandle(QString, QString)
{
    loginTimeCount = 0;
    loginCtrlTimer->stop();

    // emit this to javascript
    emit sLoginResult(x_UserOrPwdError);

    emit sLoginStateChanged(LoginReady);
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

void XwareWebController::login(QString userName, QString pwd, QString vertifyCode)
{
    if(loginState == LoginNotReady)
    {
        NormalNotice::getInstance()->showMessage(tr("Login service not ready"), Notice_Color_Notice,
                                                 tr("Please check the network and try again later!"));
        return;
    }

    this->userName = userName;
    this->userPwd = pwd;
    this->vertifyCode = vertifyCode;

    // login action
    XwarePopulateObject::getInstance()->login(this->userName, this->userPwd, this->vertifyCode);

    // show hints
    NormalNotice::getInstance()->showMessage(tr("Logining"), Notice_Color_Notice,
                                             tr("Logining to Thunder, please wait..."));

    // changed login state
    emit sLoginStateChanged(Logining);

    startLoginCtrlTimer();
    loginCtrlTimer->start();
}

void XwareWebController::logout()
{
    XwarePopulateObject::getInstance()->logout();
}

void XwareWebController::initWebView()
{
    webview = new MainWebView();

    // set default url
    webview->setUrl(QUrl(LOGIN_URL));

    // loading finish
    connect(webview, SIGNAL(loadFinished(bool)), this, SLOT(loadingFinished(bool)));

    // populate Qt object to javascript
    connect(webview->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(populateQtObject()));

    // url change
    connect(webview, SIGNAL(urlChanged(QUrl)), this, SLOT(webUrlChanged(QUrl)), Qt::QueuedConnection);
}

QWebView *XwareWebController::reInitWebView()
{
    if(webview != NULL)
    {
        webview->disconnect();
        delete webview;
        webview = NULL;
    }

    initWebView();

    return webview;
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

XwareLoginState XwareWebController::getLoginState()
{
    return loginState;
}

void XwareWebController::loadingFinished(bool noError)
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<" loading Finished:"<<currentPageURL();

    // catch error
    if(!noError)
    {
        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<" catch an error when loading page:"<<currentPageURL();
    }

    // http://yuancheng.xunlei.com/3/
    if(currentPageURL() == MAIN_URL_3 && loginState < Logined)
    {
        // populate javascript to MAIN_URL_3
        populateJavascript();

        // init completed task webview
        CompletedListWebView::getInstance()->init();

        isHasAutoLoginTask = false;

        qDebug()<<"[xware info] login completed, initialise binding ...";

        emit sLoginStateChanged(Logined);
        emit sLoginResult(x_LoginSuccess);

        // wait for get the binded peer ids
        QTimer::singleShot(2000, XwarePopulateObject::getInstance(), SLOT(getAllBindedPeerIds()));
    }

    // http://yuancheng.xunlei.com/login.html
    else if(currentPageURL().contains(LOGIN_URL))
    {
        // populate javascript to LOGIN_URL
        populateJavascript();

        if(loginState == Logined)
        {
            //  show the hints
            NormalNotice::getInstance()->showMessage(tr("Logout"), Notice_Color_Success,
                                                     tr("Thunder is unavailable now."));

            XwareController::getInstance()->stopETM();

            // re init the webview
            reInitWebView();

            emit sLoginResult(x_Logout);
        }

        if(loginState != Logining)
        {
            // changed login state
            emit sLoginStateChanged(LoginReady);

            // 仅在程序刚启动并且有自动登录记录时调用
            if(isHasAutoLoginTask)
            {
                QEventLoop loop;
                QTimer::singleShot(1000, &loop, SLOT(quit()));
                loop.exec();
                this->login(this->userName, this->userPwd);
            }
            else
            {
                SettingXMLHandler xml;
                if(xml.getChildElement(XwareSetting, "State") == "Enable")
                {
                    if (showLoginReadyHint)
                    {
                        NormalNotice::getInstance()->showMessage(tr("Login ready"), Notice_Color_Success,
                                                                 tr("You can login to Thunder now"));
                        showLoginReadyHint = false;
                    }
                }
            }
        }
    }
}

void XwareWebController::populateQtObject()
{
    if ((currentPageURL() == MAIN_URL_3) || (currentPageURL() == LOGIN_URL))
    {
        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<"populate qt object to ==>" << currentPageURL();

        // populate QT object into javascript
        webview->page()->mainFrame()->addToJavaScriptWindowObject("Point", XwarePopulateObject::getInstance());
    }
}

void XwareWebController::populateJavascript()
{
    QString filePath = "";
    if(currentPageURL().contains(LOGIN_URL))
    {
        if(initLoginJsState)return;
        initLoginJsState = true;
        filePath = ":/xware/resources/xware/xware_login.js";
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
}

void XwareWebController::webUrlChanged(QUrl url)
{
   if(XWARE_CONSTANTS_STRUCT.DEBUG)
       qDebug()<<"URL changed ==>" << url.toString() ;

   if(url.toString().contains(LOGIN_URL))
   {
       if(url.toString().startsWith(LOGIN_URL + QString("#")))
       {
           webview->triggerPageAction(QWebPage::Stop);
           webview->page()->mainFrame()->load(QUrl(LOGIN_URL));
       }
   }

   else if(url.toString() == MAIN_URL_3)
   {
       loginTimeCount = 0;
       loginCtrlTimer->stop();
   }

    else
    {
            webview->triggerPageAction(QWebPage::Stop);
            webview->page()->mainFrame()->load(QUrl(MAIN_URL_3));
    }


}

