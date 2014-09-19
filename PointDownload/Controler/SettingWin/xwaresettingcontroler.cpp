#include "xwaresettingcontroler.h"
#include <QtQml>

XwareSettingControler::XwareSettingControler(QObject *parent) :
    QObject(parent)
{
    //import时使用Singleton.XwareSettingControler
    qmlRegisterSingletonType<XwareSettingControler>("Singleton.XwareSettingControler"
                                                    , 1, 0, "XwareSettingControler", xSCObj);

    // login result
    connect(XwareController::getInstance(), SIGNAL(sLoginResult(XwareLoginResultType)),
            this, SLOT(loginResultHandle(XwareLoginResultType)));

    // vertify code link update
    connect(XwarePopulateObject::getInstance(), SIGNAL(sVertifyCodeLink(QString)),
            this, SIGNAL(sVertifyCodeLinkChange(QString)));

    initData();
}

XwareSettingControler * XwareSettingControler::xwareSettingControler = NULL;
XwareSettingControler * XwareSettingControler::getInstance()
{
    if (xwareSettingControler == NULL)
        xwareSettingControler = new XwareSettingControler();
    return xwareSettingControler;
}

void XwareSettingControler::enableXware()
{
    XwareController::getInstance()->addXwareFirmware();
    setXwareEnable(true);
}

void XwareSettingControler::disableXware()
{
    XwareController::getInstance()->removeXwareFirmware();
    setXwareEnable(false);
}

void XwareSettingControler::signInXware(QString username, QString passwd, QString vertifyCode)
{
    XwareController::getInstance()->login(username, passwd, vertifyCode);
}

void XwareSettingControler::signOutXware()
{
    XwareController::getInstance()->logout();
}

void XwareSettingControler::tryAutomaticLogin()
{
//    qDebug()<<isSignIn<<userName<<userPasswd<<automaticLogin;

    setIsSignIn(false);   // added by Choldrim

    if (!isSignIn && userName != "" & userPasswd != "" & automaticLogin)
    {
        //signInXware(userName,userPasswd);
        XwareController::getInstance()->tryAutomaticLogin(userName, userPasswd);
    }
}

bool XwareSettingControler::getXwareEnable()
{
    return xwareEnable;
}

bool XwareSettingControler::getIsSignIn()
{
    return isSignIn;
}

bool XwareSettingControler::getAutomaticLogin()
{
    return automaticLogin;
}

QString XwareSettingControler::getUserName()
{
    return userName;
}

QString XwareSettingControler::getUserPasswd()
{
    return userPasswd;
}

void XwareSettingControler::setXwareEnable(bool flag)
{
    xwareEnable = flag;
    SettingXMLHandler tmpHandler;

    if (flag)
        tmpHandler.setChildElement(XwareSetting,"State","Enable");
    else
        tmpHandler.setChildElement(XwareSetting,"State","Disable");

    emit sXwareEnableChange();
}

void XwareSettingControler::setIsSignIn(bool flag)
{
    isSignIn = flag;

    SettingXMLHandler tmpHandler;

    if (flag)
        tmpHandler.setChildElement(XwareSetting,"Logged","True");
    else
        tmpHandler.setChildElement(XwareSetting,"Logged","False");

    emit sIsSignInChange();
    emit sSignInFlagChange(flag);
    emit sSignInFinish();
}

void XwareSettingControler::setAutomaticLogin(bool flag)
{
    automaticLogin = flag;

    SettingXMLHandler tmpHandler;

    if (flag)
        tmpHandler.setChildElement(XwareSetting,"AutomaticLogin","True");
    else
        tmpHandler.setChildElement(XwareSetting,"AutomaticLogin","False");

    emit sAutomaticLoginChange();
}

void XwareSettingControler::setUserName(QString tmpName)
{
    userName = tmpName;
    SettingXMLHandler tmpHandler;

    tmpHandler.setChildElement(XwareSetting,"UserName",tmpName);

    emit sUserNameChange();
}

void XwareSettingControler::setUserPasswd(QString tmpPasswd)
{
    SettingXMLHandler tmpHandler;
    tmpHandler.setChildElement(XwareSetting,"UserPasswd",QString(tmpPasswd.toLatin1().toBase64()));

    userPasswd = tmpPasswd;

    emit sUserPasswdChange();
}

void XwareSettingControler::loginResultHandle(XwareLoginResultType rs)
{
    if(rs == x_LoginSuccess)
    {
        // save state
        setIsSignIn(true);
    }
    else if(rs == x_Logout)
    {
        // save state
        setIsSignIn(false);
    }
    else if(rs == x_LoginTimeOut)
    {
        // time out
        setIsSignIn(false);
    }
}

void XwareSettingControler::initData()
{
    SettingXMLHandler tmpHandler;
    xwareEnable = tmpHandler.getChildElement(XwareSetting,"State") == "Enable"?true:false;
    isSignIn = tmpHandler.getChildElement(XwareSetting,"Logged") == "True"?true:false;
    userName = tmpHandler.getChildElement(XwareSetting,"UserName");
    userPasswd = QString(QByteArray::fromBase64(tmpHandler.getChildElement(XwareSetting,"UserPasswd").toLatin1()));
    automaticLogin = tmpHandler.getChildElement(XwareSetting,"AutomaticLogin") == "True"?true:false;
}
