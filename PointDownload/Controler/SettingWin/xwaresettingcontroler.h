#ifndef XWARESETTINGCONTROLER_H
#define XWARESETTINGCONTROLER_H

#include <QObject>
#include <QQmlEngine>
#include "XMLHandler/settingxmlhandler.h"
#include "Download/XwareTask/xwarecontroller.h"

class XwareSettingControler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool xwareEnable READ getXwareEnable WRITE setXwareEnable NOTIFY sXwareEnableChange)
    Q_PROPERTY(bool isSignIn READ getIsSignIn WRITE setIsSignIn NOTIFY sIsSignInChange)
    Q_PROPERTY(bool automaticLogin READ getAutomaticLogin WRITE setAutomaticLogin NOTIFY sAutomaticLoginChange)
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName NOTIFY sUserNameChange)
    Q_PROPERTY(QString userPasswd READ getUserPasswd WRITE setUserPasswd NOTIFY sUserPasswdChange)
public:
    static XwareSettingControler * getInstance();

    Q_INVOKABLE void enableXware();
    Q_INVOKABLE void disableXware();
    Q_INVOKABLE void signInXware(QString username, QString passwd, QString vertifyCode);
    Q_INVOKABLE void signOutXware();
    Q_INVOKABLE void refreshVertifyCode();

    //在main函数调用
    void tryAutomaticLogin();

public:
    bool getXwareEnable();
    bool getIsSignIn();
    bool getAutomaticLogin();
    QString getUserName();
    QString getUserPasswd();

    void setXwareEnable(bool flag);
    void setIsSignIn(bool flag);
    void setAutomaticLogin(bool flag);
    void setUserName(QString tmpName);
    void setUserPasswd(QString tmpPasswd);

signals:
    void sXwareEnableChange();
    void sIsSignInChange();
    void sUserNameChange();
    void sUserPasswdChange();
    void sAutomaticLoginChange();
    void sSignInFlagChange(bool flag);
    void sVertifyCodeLinkChange(QString codeLink);

    void sInstallFinish();
    void sInstallError();
    void sSignInFinish();
    void sSignInError();
    void sSignOutFinish();
    void sSignOutError();

private slots:
    void loginResultHandle(XwareLoginResultType rs);
    void bindRouterCodeResultHandle(int rs);

private:
    explicit XwareSettingControler(QObject *parent = 0);

    void initData();

private:
    static XwareSettingControler * xwareSettingControler;

    bool xwareEnable;
    bool isSignIn;
    bool automaticLogin;
    QString userName;
    QString userPasswd;

};


//将单例对象注册到qml中使用的回调函数
static QObject * xSCObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return XwareSettingControler::getInstance();
}

#endif // XWARESETTINGCONTROLER_H
