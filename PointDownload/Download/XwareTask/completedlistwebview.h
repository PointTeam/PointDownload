#ifndef COMPLETEDLISTWEBVIEW_H
#define COMPLETEDLISTWEBVIEW_H

#include <QWebView>
#include <QTimer>

#include "xwarewebcontroller.h"

class CompletedListWebView : public QWebView
{
    Q_OBJECT
public:
    static CompletedListWebView * getInstance();
    void init();

signals:

public slots:
    void loadFinishHandle();
    void removeComletedTask(QString taskId, bool deleteFile = false);
    void clearAllCompletedTask(bool deleteFile = false);

private slots:
    void changeToCompletedList();

private:
    explicit CompletedListWebView(QObject *parent = 0);
    void initConnection();
    void evaluateDefaultJS();
    void evaluateJS(QString js);
    QStringList getAllCompletedTaskFromJson();

private:
    static CompletedListWebView * completedListWebView;
    QNetworkAccessManager manager;
    QNetworkReply * reply;
    QTimer * autoClearTimer;
};

#endif // COMPLETEDLISTWEBVIEW_H
