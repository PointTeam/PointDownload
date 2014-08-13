#ifndef XWARESETTINGCONTROLER_H
#define XWARESETTINGCONTROLER_H

#include <QObject>
#include "XMLHandler/settingxmlhandler.h"

class XwareSettingControler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool xwareEnable READ getXwareEnable WRITE setXwareEnable NOTIFY sXwareEnableChange)
    Q_PROPERTY(bool isSignIn READ getIsSignIn WRITE setIsSignIn NOTIFY sIsSignInChange)
public:
    explicit XwareSettingControler(QObject *parent = 0);

    Q_INVOKABLE void enableXware();
    Q_INVOKABLE void disableXware();
    Q_INVOKABLE void signInXware(QString username, QString passwd);
    Q_INVOKABLE void signOutXware();
public:
    bool getXwareEnable();
    bool getIsSignIn();

    void setXwareEnable(bool flag);
    void setIsSignIn(bool flag);
signals:
    void sXwareEnableChange();
    void sIsSignInChange();

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
};

#endif // XWARESETTINGCONTROLER_H
