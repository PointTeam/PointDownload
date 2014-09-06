#ifndef WEBCTRLVIEWTEST_H
#define WEBCTRLVIEWTEST_H

#include <QtWebKitWidgets/QWebView>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QTabWidget>

#include "xwarewebcontroller.h"

// 这个类仅做测试使用，除了调用显示本类窗口的函数show()外，不得调用其它函数
class WebCtrlViewTest : public QWidget
{
    Q_OBJECT
public:
    static WebCtrlViewTest *getInstance();

signals:

private slots:
    void lineEditReturnHandle();
    void execJS(QString js);
    void tabChangedHandle(int index);

private:
    explicit WebCtrlViewTest();

private:
    static WebCtrlViewTest * webCtrlViewTestInstance;
    QWebView * webview;
    QGridLayout * mainLayout;
    QLineEdit * execJSLE;
    QTabWidget * tabWG;
};

#endif // WEBCTRLVIEWTEST_H
