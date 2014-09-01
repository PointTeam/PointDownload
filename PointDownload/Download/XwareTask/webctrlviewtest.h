#ifndef WEBCTRLVIEWTEST_H
#define WEBCTRLVIEWTEST_H

#include <QtWebKitWidgets/QWebView>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>

#include "xwarewebcontroller.h"


class WebCtrlViewTest : public QWidget
{
    Q_OBJECT
public:
    static WebCtrlViewTest *getInstance();

signals:

public slots:
    void lineEditReturnHandle();
    void execJS(QString js);

private:
    explicit WebCtrlViewTest();

private:
    static WebCtrlViewTest * webCtrlViewTestInstance;
    QWebView * webview;
    QGridLayout * mainLayout;
    QLineEdit * execJSLE;
};

#endif // WEBCTRLVIEWTEST_H
