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
    spliterBtwData = XWARE_CONSTANTS_STRUCT.spliterBtwData;
    spliterEnd =  XWARE_CONSTANTS_STRUCT.spliterEnd;
    defaultPara = XWARE_CONSTANTS_STRUCT.defaultPara;
//    taskInfoMap = new QMap<QString, XwareTaskInfo*>;
//    taskInfoMapLocker = new QMutex;
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
        qDebug()<<"recv sReturnAllBindedPeerIds !!" << ids;

    QStringList list;
    if(! ids.contains(spliterBtwData))
    {
        // debug
        qDebug()<<"ids is empty, return ~~~";
        return;
    }
    else
    {
        list = ids.split(spliterBtwData);
        list.removeLast(); // remove the last empty element
    }

    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<< list << " .....";
    emit sReturnAllBindedPeerIds(list);
}

// emit the singal to javascript to start feedbacking tasks information
void XwarePopulateObject::startFeedbackDloadList()
{
    emit sJSReflashDownloadList();
}

void XwarePopulateObject::login(QString userName, QString pwd)
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"======== XwarePopulateObject::login ===========";

    // emit this to javascript
    emit sLogin(userName, pwd);
}

void XwarePopulateObject::logout()
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"======== XwarePopulateObject::logout ===========";
    
    // emit this to javascript
    emit sLogout();
}

void XwarePopulateObject::getAllBindedPeerIds()
{
    // emit this to javascript
    emit sJSGetAllBindedPeerIds();
}

void XwarePopulateObject::justForJSTest(QString testStr)
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<" ************* javascript test !!  ==>" << testStr;
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

void XwarePopulateObject::finishDownload(QString tid)
{
    emit sFinishDownload(tid);
}

QString XwarePopulateObject::getDefaultTaskPara()
{
    return this->defaultPara;
}

QString XwarePopulateObject::getSpliterEnd()
{
    return this->spliterEnd;
}

QString XwarePopulateObject::getSpliterBtwData()
{
    return this->spliterBtwData;
}

