#include "xwaresettingcontroler.h"

XwareSettingControler::XwareSettingControler(QObject *parent) :
    QObject(parent)
{
    initData();
}

void XwareSettingControler::enableXware()
{

}

void XwareSettingControler::disableXware()
{

}

void XwareSettingControler::signInXware(QString username, QString passwd)
{

}

void XwareSettingControler::signOutXware()
{

}

void XwareSettingControler::tryAutomaticLogin()
{
    if (!isSignIn && userName != "" & userPasswd != "" & automaticLogin)
        signInXware(userName,userPasswd);
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

void XwareSettingControler::initData()
{
    SettingXMLHandler tmpHandler;
    xwareEnable = tmpHandler.getChildElement(XwareSetting,"State") == "Enable"?true:false;
    isSignIn = tmpHandler.getChildElement(XwareSetting,"Logged") == "True"?true:false;
    userName = tmpHandler.getChildElement(XwareSetting,"UserName");
    userPasswd = QString(QByteArray::fromBase64(tmpHandler.getChildElement(XwareSetting,"UserPasswd").toLatin1()));
    automaticLogin = tmpHandler.getChildElement(XwareSetting,"AutomaticLogin") == "True"?true:false;
}
