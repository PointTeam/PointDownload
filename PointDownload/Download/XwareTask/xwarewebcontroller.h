#ifndef XWAREWEBCONTROLLER_H
#define XWAREWEBCONTROLLER_H

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

class XwareWebController : public QObject
{
    Q_OBJECT
public:
    ~XwareWebController();
    static XwareWebController *getInstance();

    // execute javascript
    void executeJS(QString js);
    QString setElemValueById(QString id, QString value);

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
    void webUrlChanged();
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
    bool isHasAutoLoginTask;   // 仅用在程序刚启动并且有记录到自动登录时
};

#endif // XWAREWEBCONTROLLER_H
