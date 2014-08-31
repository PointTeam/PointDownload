#ifndef XWAREWEBCONTROLLER_H
#define XWAREWEBCONTROLLER_H

#define MAIN_URL_3 "http://yuancheng.xunlei.com/3/"
#define LOGIN_URL  "http://yuancheng.xunlei.com/login.html"
#define LOGIN_MAX_TRY 5
#define LOGIN_DEFAULT_INTERVAL 1500

#include <QObject>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>
#include <QUrl>
#include <QTimer>
#include <QFile>
#include <QTextStream>

#include "XwareDataType.h"
#include "xwarepopulateobject.h"
#include "mywebview.h"
#include "XwareConstants.h"

class XwareWebController : public QObject
{
    Q_OBJECT
public:
    ~XwareWebController();
    static XwareWebController *getInstance();

    void executeJS(QString js); // execute javascript
    QString setElemValueById(QString id, QString value); //

    void login(QString userName, QString pwd);
    void logout();
    QString currentPageURL();
    void reloadWebView();

    void tryAutomaticLogin(QString userName, QString pwd);

signals:
    void sLoginResult(XwareLoginResultType);

public slots:

private slots:
    void loadingFinished();
    void populateQtObject();
    void webUrlChanged(QUrl url);
    void startLoginCtrlTimer();  // try to login, a slot of login-timer

private:
    explicit XwareWebController(QObject *parent = 0);
    
private:
    static XwareWebController * xwareWebController;

    QWebView * webview;

    QString URL3;
    bool isLogined;
    QString userName;
    QString userPwd;
    QTimer * loginCtrlTimer;
    int loginTimeCount;
    bool isHasAutoLoginTask;   // 仅在程序刚启动并且有自动登录记录时置true
};

#endif // XWAREWEBCONTROLLER_H
