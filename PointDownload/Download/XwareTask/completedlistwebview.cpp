#include "completedlistwebview.h"

#define AUTO_CLEAR_INTERVAL 5000


CompletedListWebView::CompletedListWebView(QObject *parent)
{
}

void CompletedListWebView::initConnection()
{
    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(loadFinishHandle()));

    connect(autoClearTimer, SIGNAL(timeout()), this, SLOT(clearAllCompletedTask()));
}

void CompletedListWebView::init()
{
    this->page()->setNetworkAccessManager(XwareWebController::getInstance()->
                                          getWebView()->page()->networkAccessManager());

    // direct to the downloading URL
    this->setUrl(XwareWebController::getInstance()->getWebView()->url());

    autoClearTimer = new QTimer();
    autoClearTimer->setInterval(AUTO_CLEAR_INTERVAL);
    autoClearTimer->start();

    initConnection();
}

void CompletedListWebView::evaluateDefaultJS()
{

}

void CompletedListWebView::evaluateJS(QString js)
{
    qDebug()<<"completed webview js : "<<js;
    this->page()->mainFrame()->evaluateJavaScript(js);
}

CompletedListWebView * CompletedListWebView::completedListWebView = NULL;
CompletedListWebView * CompletedListWebView::getInstance()
{
    if(completedListWebView == NULL)
    {
        completedListWebView = new CompletedListWebView();
    }
    return completedListWebView;
}

void CompletedListWebView::clearAllCompletedTask(bool deleteFile)
{
    QStringList list = getAllCompletedTaskFromJson();
    if(list.length() == 0)return;

    if(deleteFile)
    {
        QString js;
        foreach(QString id, list)
        {
            js += QString("if(App.get(\"task.type\") == 1){");
            js += QString("App.set(\"task.remove\", "+ id +");");
            js += QString("App.set(\"dialogs.removeTasks.checked\", 1);");
            js += QString("App.set(\"dialogs.removeTasks.confirmEVT\", 1);");
            js += QString("}");
        }
        evaluateJS(js);
    }
    else
    {
        QString js;
        foreach(QString id, list)
        {
            js += QString("if(App.get(\"task.type\") == 1){");
            js += QString("App.set(\"task.remove\", "+ id +");");
            js += QString("App.set(\"dialogs.removeTasks.confirmEVT\", 1);");
            js += QString("}");
        }
        evaluateJS(js);
    }

    this->reload();
}

void CompletedListWebView::changeToCompletedList()
{
     evaluateJS("App.set(\"task.type\", 1);");
}

void CompletedListWebView::loadFinishHandle()
{
   QTimer::singleShot(1000, this, SLOT(changeToCompletedList()));
}

void CompletedListWebView::removeComletedTask(QString taskId, bool deleteFile)
{
    if(deleteFile)
    {
        evaluateJS("pointRmAddDelItem("+ taskId +")");
    }
    else
    {
        evaluateJS("pointRmItem("+ taskId +")");
    }
}


QStringList CompletedListWebView::getAllCompletedTaskFromJson()
{
    QUrl url(XWARE_CONSTANTS_STRUCT.URLSTR + "list?v=2&type=1&pos=0&number=99999&needUrl=1");

    QEventLoop loop;

    // request
    reply = manager.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec(); // wait for message
    reply->disconnect();

    // 读到的信息
    QString jsonStr = QUrl::fromPercentEncoding(reply->readAll());
    QJsonDocument jsd = QJsonDocument::fromJson(jsonStr.toUtf8());
    QMap<QString, QVariant> jsonMap = jsd.toVariant().toMap();

    QList<QVariant> completedTaskList = jsonMap.value("tasks").toList();

    QStringList list;
    for(int i = 0; i < completedTaskList.length(); ++i )
    {
        QString id = completedTaskList.at(i).toMap().value("id").toString();
        list<<id;
    }

    return list;
}
