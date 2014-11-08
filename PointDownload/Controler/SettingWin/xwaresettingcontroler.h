#ifndef XWARESETTINGCONTROLER_H
#define XWARESETTINGCONTROLER_H

#include <QObject>
#include <QQmlEngine>
#include "settingxmlhandler.h"
#include "normalnotice.h"
#include "Download/XwareTask/xwarecontroller.h"
#include "Download/XwareTask/xwarewebcontroller.h"


class XwareSettingControler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool xwareEnable READ getXwareEnable WRITE setXwareEnable NOTIFY sXwareEnableChange)
    Q_PROPERTY(bool isSignIn READ getIsSignIn WRITE setSignInFlag NOTIFY sIsSignInChange)
    Q_PROPERTY(bool automaticLogin READ getAutomaticLogin WRITE setAutomaticLogin NOTIFY sAutomaticLoginChange)
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName NOTIFY sUserNameChange)
    Q_PROPERTY(QString userPasswd READ getUserPasswd WRITE setUserPasswd NOTIFY sUserPasswdChange)
public:
    static XwareSettingControler * getInstance();
    static QObject * xSCObj(QQmlEngine *engine, QJSEngine *scriptEngine);

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
    void setSignInFlag(int flag);//每个数字对应按钮会显示得文字:0="Sign out";1="Sign in";2="Signing...";3="Binding..."
    void setAutomaticLogin(bool flag);
    void setUserName(QString tmpName);
    void setUserPasswd(QString tmpPasswd);

signals:
    void sXwareEnableChange();
    void sIsSignInChange();
    void sUserNameChange();
    void sUserPasswdChange();
    void sAutomaticLoginChange();
    void sSignInFlagChange(int flag);//每个数字对应按钮会显示得文字:0="Sign out";1="Sign in";2="Signing...";3="Binding..."
    void sVertifyCodeLinkChange(QString codeLink);

private slots:
    void loginStateChangedHandle(XwareLoginState state);

public slots:
    void slotEanbleXware(bool result);

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
#endif // XWARESETTINGCONTROLER_H
