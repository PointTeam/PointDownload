/***********************************************************************
*PointDownload
*Copyright (C) 2014~2015  PointTeam
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
#include <QImage>

#include "XwareDataType.h"
#include "xwarewebcontroller.h"
#include "Download/DataType.h"
#include "xwaretaskentity.h"
#include "taskinfo.h"

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

    void setDefaultDownloader(QString pid);

signals:
    void sReturnAllBindedPeerIds(QStringList);
    void sFeedbackURLParse(TaskInfo);  // QString: all URL parse result, include fileName and fileSize
    void sFinishDownload(QString);  // QString: URL
    void sFeedbackDownloadList(QString);

    // hints and errors
    void sHint(QString, QString);
    void sError(QString, QString);
    // login hints and errors
    void sLoginHint(QString, QString);
    void sLoginError(QString, QString);

    // emit to the login pannel for updating the vertify code
    void sVertifyCodeLink(QString);

    // ============================>  emit to javascript <================================= //
    void sJSLogin(QString, QString, QString);
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

    // login vertify code
    void sJSUpdateVertifyCode();

    void sSetDefaultDownloader(QString);
    // ================================================================================== //

public slots:
    void login(QString userName, QString pwd, QString vertifyCode = QString(""));  // called by web controller
    void logout();
    void getAllBindedPeerIds();  // called by controller
    void startFeedbackDloadList();  // called by controller

    // =============================>  called by javascript <================================== //
    // debugger
    void justForJSTest(QString testStr);
    void setAllBindedPeerIds(QString ids);  //  return all bind peer ids
    void feedbackDownloadList(QString tasksInfo);
    void feedbackURLParse(QString taskInfoList);

    // login error
    void loginError(short type, QString errorMsg);  // type: 1 => userName, 2 => passwd, 3 => vertify code

    // feedback the msg from xware
    void feedbackMsgboxMessage(QString msg);
    // ================================================================================== //

private slots:
    // show the error or hint
    void handleErrorEmit(QString title, QString msg);
    void handleHintEmit(QString title, QString msg);
    void handleLoginErrorEmit(QString title, QString msg);
    void handleLoginHintEmit(QString title, QString msg);

private:
    explicit XwarePopulateObject(QObject *parent = 0);
    QString saveVertifyImg(QString link);

    //  将大单位（如：GB）转换成小单元B，返回值是不带单位的纯数字字符串, eg: 2KB ==> 2048
    QString convertToByteUnit(QString size);

private:
    static XwarePopulateObject *xwarePopulateObject;
    QString spliterBtwData;
    QString spliterEnd;
    QString defaultPara;
};

#endif // XWAREPOPULATEOBJECT_H
