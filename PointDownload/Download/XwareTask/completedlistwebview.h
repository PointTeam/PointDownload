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
    void sNewCompletedTask(QString url);

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
    QMap<QString, QString> getAllCompletedTaskFromJson();

    // check whether there is new completed tasks, if there is, emit sNewCompletedTask signal
    void checkNewCompletedTask(QMap<QString, QString> map);

private:
    static CompletedListWebView * completedListWebView;
    QNetworkAccessManager manager;
    QNetworkReply * reply;
    QTimer * autoClearTimer;
    QMap<QString, QString> completedTaskMap; // <QString, QString> : <tid, url>

//    QStringList completedTasksIdList;
    bool firstCheckNewCompletedTask;
};

#endif // COMPLETEDLISTWEBVIEW_H
