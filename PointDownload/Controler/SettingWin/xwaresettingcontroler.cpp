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

bool XwareSettingControler::getXwareEnable()
{
    return xwareEnable;
}

bool XwareSettingControler::getIsSignIn()
{
    return isSignIn;
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

    emit sIsSignInChange();
}

void XwareSettingControler::initData()
{
    SettingXMLHandler tmpHandler;
    xwareEnable = tmpHandler.getChildElement(XwareSetting,"State") == "Enable"?true:false;
    isSignIn = tmpHandler.getChildElement(XwareSetting,"Logged") == "True"?true:false;
}
