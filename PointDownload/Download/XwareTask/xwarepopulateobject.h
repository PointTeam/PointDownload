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

#ifndef XWAREPOPULATEOBJECT_H
#define XWAREPOPULATEOBJECT_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QDebug>
#include <QThread>
#include <QMutex>

#include "XwareDataType.h"
#include "xwarewebcontroller.h"
#include "Download/DataType.h"
#include "xwaretaskentity.h"

class XwarePopulateObject : public QObject
{
    Q_OBJECT
public:
    static XwarePopulateObject *getInstance();
    ~XwarePopulateObject();

    // add new task
    void addNewDownloadTask(QString url, QString storage, QStringList fileList);
    void addNewBTDownloadTask(QString btFilePath, QString storage, QStringList fileList);

    // task controller
    void suspendDownloadingTask(QString tid);
    void resumeDownloadingTask(QString tid);
    void removeDownloadingTask(QString tid);
    void entryOfflineChannel(QString tid);
    void entryHighSpeedChannel(QString tid);

    void urlParse(QString url);
    void btParse(QString btFilePath);

    QString getDefaultTaskPara();
    QString getSpliterBtwData();
    QString getSpliterEnd();

signals:
    void sReturnAllBindedPeerIds(QStringList);
    void sFeedbackURLParse(QString);  // QString: all URL parse result, include fileName and fileSize
    void sFinishDownload(QString);  // QString: URL
    void sFeedbackDownloadList(QString);

    // ============================>  emit to javascript <================================= //
    void sJSLogin(QString, QString);
    void sJSLogout();

    // get all binded machine code(peer id)
    void sJSGetAllBindedPeerIds();

    // reflash the task list
    void sJSReflashDownloadList();

    // add new task
    void sJSAddNewDownloadTask(QString, QString, QStringList);  // param: url, storage, fileList

    // task controller
    void sJSSuspendDownloadingTask(QString);  // param: task id
    void sJSResumeDownloadingTask(QString);  // param: task id
    void sJSRemoveDownloadingTask(QString);  // param: task id
    void sJSEntryOfflineChannel(QString);  // param: task id
    void sJSEntryHighSpeedChannel(QString);  // param: task id

    // parse url , and then js will feedback the url parsed info
    void sJSUrlParse(QString);
    void sJSBTParse(QString);
    // ================================================================================== //

public slots:
    void login(QString userName, QString pwd);  // called by web controller
    void logout();
    void getAllBindedPeerIds();  // called by controller
    void startFeedbackDloadList();  // called by controller

    // =============================>  called by javascript <================================== //
    void justForJSTest(QString testStr);      // tmp js debugger //
    void setAllBindedPeerIds(QString ids);  //  return all bind peer ids
    void feedbackDownloadList(QString tasksInfo);
    void feedbackURLParse(QString taskInfoList);
    void finishDownload(QString tid);
    // ================================================================================== //

private slots:

private:
    explicit XwarePopulateObject(QObject *parent = 0);
    static XwarePopulateObject *xwarePopulateObject;

    QString spliterBtwData;
    QString spliterEnd;
    QString defaultPara;
};

#endif // XWAREPOPULATEOBJECT_H
