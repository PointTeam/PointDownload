#ifndef COMPLETEDLISTWEBVIEW_H
#define COMPLETEDLISTWEBVIEW_H

#include <QWebView>
#include <QTimer>

#include "xwarewebcontroller.h"

/*
 * 此类为保存完成的下载任务的webview
主要用于
  1、扫描已下载完成的任务并发出完成信号
  2、对下载完成的列表进行清除操作（去除新建下载的任务与完成的任务之间的冲突）
*/
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

    bool firstCheckNewCompletedTask;

    short checkCompletedTaskIntervalCounter;
};

#endif // COMPLETEDLISTWEBVIEW_H
