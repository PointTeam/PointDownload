#include "xwaresettingcontroler.h"
#include <QtQml>

XwareSettingControler::XwareSettingControler(QObject *parent) :
    QObject(parent)
{
    //import时使用Singleton.XwareSettingControler
    qmlRegisterSingletonType<XwareSettingControler>("Singleton.XwareSettingControler"
                                                    , 1, 0, "XwareSettingControler", xSCObj);

    // vertify code link update
    connect(XwarePopulateObject::getInstance(), SIGNAL(sVertifyCodeLink(QString)),
            this, SIGNAL(sVertifyCodeLinkChange(QString)));

    // downloading xware firmware finish
    connect(XwareController::getInstance(), SIGNAL(sAddXwareSupportResult(bool)),
                this, SLOT(slotEanbleXware(bool)));

    // login state changed
    connect(XwareWebController::getInstance(), SIGNAL(sLoginStateChanged(XwareLoginState)),
                    this, SLOT(loginStateChangedHandle(XwareLoginState)));

    initData();
}

XwareSettingControler * XwareSettingControler::xwareSettingControler = NULL;
XwareSettingControler * XwareSettingControler::getInstance()
{
    if (xwareSettingControler == NULL)
        xwareSettingControler = new XwareSettingControler();
    return xwareSettingControler;
}

QObject *XwareSettingControler::xSCObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return XwareSettingControler::getInstance();
}

void XwareSettingControler::enableXware()
{
    NormalNotice::getInstance()->showMessage(tr("Adding Thunder"),
                                             Notice_Color_Notice,
                                             tr("Please wait for the installation to complete"));
    XwareController::getInstance()->addXwareFirmware();
}

void XwareSettingControler::disableXware()
{
    NormalNotice::getInstance()->showMessage(tr("Thunder Removed"),
                                             Notice_Color_Notice,
                                             tr("Thunder now unavailable"));

    XwareController::getInstance()->removeXwareFirmware();
    setXwareEnable(false);
}

void XwareSettingControler::signInXware(QString username, QString passwd, QString vertifyCode)
{
    XwareController::getInstance()->login(username, passwd, vertifyCode);
}

void XwareSettingControler::signOutXware()
{
    // don't nothing temporiry
    NormalNotice::getInstance()->showMessage(tr("Logout Disable"), Notice_Color_Notice,
                                             tr("Sorry, logout dose not enable for now, you can close the Point to logout"));

//    XwareController::getInstance()->logout();
}

void XwareSettingControler::refreshVertifyCode()
{
    qDebug() << "refresh";
    emit XwarePopulateObject::getInstance()->sJSUpdateVertifyCode();
}

void XwareSettingControler::tryAutomaticLogin()
{
    setSignInFlag(1);

    if (!isSignIn && XwareSettingControler::getInstance()->getXwareEnable() &&
            userName != "" && userPasswd != "" && automaticLogin)
    {
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

void XwareSettingControler::setSignInFlag(int flag)
{
    if (flag == 0)
    {
        isSignIn = true;

        SettingXMLHandler tmpHandler;
        tmpHandler.setChildElement(XwareSetting,"Logged","True");
    }
    else if (flag == 1)
    {
        isSignIn = false;

        SettingXMLHandler tmpHandler;
        tmpHandler.setChildElement(XwareSetting,"Logged","False");
    }

    emit sSignInFlagChange(flag);
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


void XwareSettingControler::loginStateChangedHandle(XwareLoginState state)
{
    if(state == LoginNotReady || state == LoginReady)
    {
        setSignInFlag(1);
    }

    else if(state == Logining)
    {
        setSignInFlag(2);
    }

    else if(state == Logined)
    {
        setSignInFlag(3);
    }

    else if(state == LoginedAndBinded)
    {
        setSignInFlag(0);
    }

}

void XwareSettingControler::slotEanbleXware(bool result)
{
    if (result)
    {
        setXwareEnable(true);
        NormalNotice::getInstance()->showMessage(tr("Enable Thunder success"),
                                                 Notice_Color_Success,
                                                 tr("Thunder has been installed, you can log in Thunder now."));
    }
    else
    {
        NormalNotice::getInstance()->showMessage(tr("Enable Thunder error"),
                                                 Notice_Color_Error,
                                                 tr("Install Thunder failed, please check the network and try again later."));
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
