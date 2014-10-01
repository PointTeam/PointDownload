/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Choldrim <choldrim@foxmail.com>
* Maintainer: Choldrim <choldrim@foxmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

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
