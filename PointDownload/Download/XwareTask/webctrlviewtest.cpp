#include "webctrlviewtest.h"


WebCtrlViewTest::WebCtrlViewTest()
{
    tabWG = new QTabWidget();
    tabWG->addTab(XwareWebController::getInstance()->getWebView(), QString("downloading"));
    tabWG->addTab(CompletedListWebView::getInstance(), QString("completed"));
    this->webview = CompletedListWebView::getInstance();
    connect(tabWG, SIGNAL(currentChanged(int)), this, SLOT(tabChangedHandle(int)));

    execJSLE = new QLineEdit();
//    execJSLE->show();
    connect(execJSLE, SIGNAL(returnPressed()), this, SLOT(lineEditReturnHandle()));

    mainLayout = new QGridLayout();

    mainLayout->addWidget(this->tabWG, 0, 0);
    mainLayout->addWidget(this->execJSLE, 1, 0);

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
    this->webview->page()->mainFrame()->evaluateJavaScript(js);
}

void WebCtrlViewTest::tabChangedHandle(int index)
{
    Q_UNUSED(index);
    this->webview = qobject_cast<QWebView*>(tabWG->currentWidget());

//    qDebug()<<this->webview->page()->mainFrame()->toHtml();
}

