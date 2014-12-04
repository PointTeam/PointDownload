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

#include "xwarepopulateobject.h"

XwarePopulateObject::XwarePopulateObject(QObject *parent) :
    QObject(parent)
{
    spliterBtwData = XWARE_CONSTANTS_STRUCT.SPLITER_BTWN_DATA;
    spliterEnd =  XWARE_CONSTANTS_STRUCT.SPLITER_END;
    defaultPara = XWARE_CONSTANTS_STRUCT.SPLITER_DEFAULT_PARAM;

    // show the hints or error
    connect(this, SIGNAL(sHint(QString,QString)), this, SLOT(handleHintEmit(QString,QString)));
    connect(this, SIGNAL(sError(QString,QString)), this, SLOT(handleErrorEmit(QString,QString)));
    connect(this, SIGNAL(sLoginHint(QString,QString)), this, SLOT(handleLoginHintEmit(QString,QString)));
    connect(this, SIGNAL(sLoginError(QString,QString)), this, SLOT(handleLoginErrorEmit(QString,QString)));
}

QString XwarePopulateObject::saveVertifyImg(QString link)
{

    qDebug()<<"XwarePopulateObject::saveVertifyImg , link: "<<link;

    QUrl url(link);

    QEventLoop loop;
    QNetworkReply *reply = MyNetworkAccessManager::getInstance()->get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QImage img;
    img = img.fromData(reply->readAll());
    QString cmd = QString("rm -rf ") + XWARE_CONSTANTS_STRUCT.XWARE_TMP_DIR + QString("vertifyCode*");
    system(cmd.toLatin1().data());
    QString savePath = XWARE_CONSTANTS_STRUCT.XWARE_TMP_DIR + QString("vertifyCode")
            + QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch()) +QString(".jpg");

    if(!img.save(savePath))
    {
        qDebug()<<"[xware error] eccur an error when save vertify code !";
        qDebug() << savePath;
    }

    qDebug()<<"save login vertify code success, path:"<<savePath;

    return savePath;
}

XwarePopulateObject * XwarePopulateObject::xwarePopulateObject = NULL;
XwarePopulateObject * XwarePopulateObject::getInstance()
{
    if (xwarePopulateObject == NULL)
        xwarePopulateObject = new XwarePopulateObject();
    return xwarePopulateObject;
}

XwarePopulateObject::~XwarePopulateObject()
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"~XwarePopulateObject()  was be called !!";
}

void XwarePopulateObject::addNewDownloadTask(QString url, QString storage, QStringList fileList)
{
    emit sJSAddNewDownloadTask(url, storage, fileList);
}

void XwarePopulateObject::addNewBTDownloadTask(QString btFilePath, QString storage, QStringList fileList)
{
    emit addNewBTDownloadTask(btFilePath, storage, fileList);
}

void XwarePopulateObject::suspendDownloadingTask(QString tid)
{
    emit sJSSuspendDownloadingTask(tid);
}

void XwarePopulateObject::resumeDownloadingTask(QString tid)
{
    emit sJSResumeDownloadingTask(tid);
}

void XwarePopulateObject::removeDownloadingTask(QString tid)
{
    emit sJSRemoveDownloadingTask(tid);
}

void XwarePopulateObject::entryOfflineChannel(QString tid)
{
    emit sJSEntryOfflineChannel(tid);
}

void XwarePopulateObject::entryHighSpeedChannel(QString tid)
{
    emit sJSEntryHighSpeedChannel(tid);
}

// called by javascript
void XwarePopulateObject::setAllBindedPeerIds(QString ids)
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"recv sReturnAllBindedPeerIds => " << ids;

    QStringList list;
    if(! ids.contains(spliterBtwData))
    {
        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<"AllBindedPeerIds from web is empty, it may be an error or first time to bind to your pc~~~";
    }
    else
    {
        list = ids.split(spliterBtwData);
        list.removeLast(); // remove the last empty element
    }

    emit sReturnAllBindedPeerIds(list);
}

// emit the singal to javascript to start feedbacking tasks information
void XwarePopulateObject::startFeedbackDloadList()
{
    emit sJSReflashDownloadList();
}

void XwarePopulateObject::login(QString userName, QString pwd, QString vertifyCode)
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"======== XwarePopulateObject::login ===========";

    // emit this to javascript
    emit sJSLogin(userName, pwd, vertifyCode);
}

void XwarePopulateObject::logout()
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"======== XwarePopulateObject::logout ===========";
    
    // emit this to javascript
    emit sJSLogout();
}

void XwarePopulateObject::getAllBindedPeerIds()
{
    // emit this to javascript
    emit sJSGetAllBindedPeerIds();
}

void XwarePopulateObject::justForJSTest(QString testStr)
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<" ************* javascript feedback test !!  ==>" << testStr;
}

void XwarePopulateObject::urlParse(QString url)
{
    emit sJSUrlParse(url);
}

void XwarePopulateObject::btParse(QString btFilePath)
{
    emit sJSBTParse(btFilePath);
}

void XwarePopulateObject::feedbackDownloadList(QString tasksInfo)
{
    emit sFeedbackDownloadList(tasksInfo);
}

void XwarePopulateObject::feedbackURLParse(QString taskInfoList)
{
    emit sFeedbackURLParse(taskInfoList);
}

void XwarePopulateObject::loginError(short type, QString errorMsg)
{
    switch (type)
    {
    // username & password
    case 1:
        emit sLoginError(tr("Login  failed"), errorMsg);
        break;

    // password
//    case 2:
//        emit sError(tr("User password error"), errorMsg);
//        break;

    // vertify code
    case 2:
        // emit vertify code link
        QString vertifyCodeUrl = errorMsg;
        emit sVertifyCodeLink(saveVertifyImg(vertifyCodeUrl));

        errorMsg = errorMsg.split(this->spliterBtwData).at(0);

        // emit hint
//        if(errorMsg.startsWith("请"))
//        {
//            // let it do nothing!!
//        }

        // emit error
//        else
//        {
//            emit sError(tr("Vertify code error"), errorMsg);
//            qDebug()<<" login vertify code error =>"<<errorMsg;
//        }
        break;
    }
}

void XwarePopulateObject::feedbackMsgboxMessage(QString msg)
{
    // just handle one msg now
    if(msg.startsWith("您所选择的下载器没有连接到网络"))
    {
        NormalNotice::getInstance()->showMessage(tr("Operation wait"), Notice_Color_Notice,
                  tr("Please wait for the response of Thunder"));
    }
    else
    {
        //NormalNotice::getInstance()->showMessage(tr("Xware message"), Notice_Color_Notice, msg);
    }

}

void XwarePopulateObject::handleErrorEmit(QString title, QString msg)
{
    NormalNotice::getInstance()->showMessage(title, Notice_Color_Error, msg);
}

void XwarePopulateObject::handleHintEmit(QString title, QString msg)
{
    NormalNotice::getInstance()->showMessage(title, Notice_Color_Warning, msg);
}

void XwarePopulateObject::handleLoginErrorEmit(QString title, QString msg)
{
    emit sError(title, msg);
}

void XwarePopulateObject::handleLoginHintEmit(QString title, QString msg)
{
    emit sHint(title, msg);
}

QString XwarePopulateObject::getDefaultTaskPara()
{
    return this->defaultPara;
}

QString XwarePopulateObject::getSpliterEnd()
{
    return this->spliterEnd;
}

void XwarePopulateObject::setDefaultDownloader(QString pid)
{
    emit sSetDefaultDownloader(pid);
}

QString XwarePopulateObject::getSpliterBtwData()
{
    return this->spliterBtwData;
}

