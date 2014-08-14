#ifndef XWARESETTINGCONTROLER_H
#define XWARESETTINGCONTROLER_H

#include <QObject>
#include "XMLHandler/settingxmlhandler.h"

class XwareSettingControler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool xwareEnable READ getXwareEnable WRITE setXwareEnable NOTIFY sXwareEnableChange)
    Q_PROPERTY(bool isSignIn READ getIsSignIn WRITE setIsSignIn NOTIFY sIsSignInChange)
    Q_PROPERTY(bool automaticLogin READ getAutomaticLogin WRITE setAutomaticLogin NOTIFY sAutomaticLoginChange)
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName NOTIFY sUserNameChange)
    Q_PROPERTY(QString userPasswd READ getUserPasswd WRITE setUserPasswd NOTIFY sUserPasswdChange)
public:
    explicit XwareSettingControler(QObject *parent = 0);

    Q_INVOKABLE void enableXware();
    Q_INVOKABLE void disableXware();
    Q_INVOKABLE void signInXware(QString username, QString passwd);
    Q_INVOKABLE void signOutXware();

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

    void sInstallFinish();
    void sInstallError();
    void sSignInFinish();
    void sSignInError();
    void sSignOutFinish();
    void sSignOutError();
private:
    void initData();

private:
    bool xwareEnable;
    bool isSignIn;
    bool automaticLogin;
    QString userName;
    QString userPasswd;
};

#endif // XWARESETTINGCONTROLER_H
