#include "webctrlviewtest.h"


WebCtrlViewTest::WebCtrlViewTest()
{
    this->webview = XwareWebController::getInstance()->getWebView();
    execJSLE = new QLineEdit();
    execJSLE->show();
    connect(execJSLE, SIGNAL(returnPressed()), this, SLOT(lineEditReturnHandle()));

    mainLayout = new QGridLayout();

    mainLayout->addWidget(this->webview);

    this->setLayout(mainLayout);
}


WebCtrlViewTest * WebCtrlViewTest::webCtrlViewTestInstance = NULL;
WebCtrlViewTest *WebCtrlViewTest::getInstance()
{
    if(webCtrlViewTestInstance == NULL)
    {
        webCtrlViewTestInstance = new WebCtrlViewTest();
    }
    return webCtrlViewTestInstance;
}

void WebCtrlViewTest::lineEditReturnHandle()
{
    execJS(this->execJSLE->text().trimmed());
}

void WebCtrlViewTest::execJS(QString js)
{
    XwareWebController::getInstance()->executeJS(js);
}

