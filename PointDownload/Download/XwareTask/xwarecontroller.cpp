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


#include "xwarecontroller.h"

XwareController::XwareController(QObject *parent) :
    QObject(parent)
{
    // login result
    connect(XwareWebController::getInstance(), SIGNAL(sLoginResult(XwareLoginResultType)),
            this, SLOT(loginResult(XwareLoginResultType)));

    // all peer ids
    connect(XwarePopulateObject::getInstance(), SIGNAL(sReturnAllBindedPeerIds(QStringList)),
            this, SLOT(tryToStartAndBindXware(QStringList)));

    // real data time
//    connect(XwarePopulateObject::getInstance(), SIGNAL(sRealTimeDataChanged(DownloadingItemInfo)),
//            this, SIGNAL(sRealTimeDataChanged(DownloadingItemInfo)));

    // finish a downloading task
    connect(XwarePopulateObject::getInstance(), SIGNAL(sFinishDownload(QString)),
            this, SLOT(finishDownloadHandle(QString)));
}

XwareController * XwareController::xwareController = NULL;
XwareController::~XwareController()
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"~XwareController()  was be called !!";
}

XwareController * XwareController::getInstance()
{
    if (xwareController == NULL)
        xwareController = new XwareController();
    return xwareController;
}

QString XwareController::getValueFromEtmcfg(QString key)
{
    QString value = "";
    QFile file(XWARE_CONSTANTS_STRUCT.XWARE_ETM_CFG);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"[error]open xware etm.cfg file error !!";
        return value;
    }
    QTextStream ts(&file);
    QString line;
    while((line = ts.readLine()) != "")
    {
        if(line.startsWith(key))
        {
            value = line.split("=").at(1).trimmed();
        }
    }
    ts.flush();
    file.close();
    return value;
}

bool XwareController::startETM()
{
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"kill all ETM process";

    // kill all ETM process
    system("pkill Embed");

    ETMProcess = new QProcess();
    QStringList args;
    args<<"--verbose";
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<< "start ETM ==>"<<XWARE_CONSTANTS_STRUCT.XWARE_ETM_PATH;
    ETMProcess->setWorkingDirectory(XWARE_CONSTANTS_STRUCT.XWARE_WORK_DIR); // set work directory
    ETMProcess->setProgram(XWARE_CONSTANTS_STRUCT.XWARE_ETM_PATH);
    ETMProcess->setArguments(args);
    ETMProcess->start();

    QEventLoop loop;
    QTimer::singleShot(3000, &loop, SLOT(quit()));
    connect(ETMProcess, SIGNAL(started()), &loop, SLOT(quit()));
    loop.exec();

    if(ETMProcess->state() == QProcess::Running)
    {
        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<"ETM has been started successfully!!";
        return true;
    }

    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"fail to start ETM successfully!!";
    return false;
}

/**
 * try to delete the Xware config files
 * return true if it is deleted successfully or doesn't exit
 * otherwise returns false
 */
bool XwareController::tryToClearXwareCfg(QString cfgPath)
{
    QDir xwareCfgDir(cfgPath);
    bool tag = true;
    if(xwareCfgDir.exists())
    {
        QStringList list =  xwareCfgDir.entryList();
        foreach(QString file , list)
        {
            // romve all file (not include dir)
            if(file != "\." && file != "\..")
            {
                tag = xwareCfgDir.remove(file);
                if(!tag)break;
            }
        }
    }
    return tag;
}

QString XwareController::getCodeFromJson()
{
    QUrl url(XWARE_CONSTANTS_STRUCT.URLSTR + "getsysinfo");

    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<url.toString();

    QEventLoop loop;
    QNetworkAccessManager manager;

    // request
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    // wait for message
    loop.exec();
    reply->disconnect();

    // 读到的信息
    QString jsonStr = reply->readAll();
    QJsonDocument jsd = QJsonDocument::fromJson(jsonStr.toLatin1());
    QJsonArray jary = jsd.array();

    delete reply;
    reply = NULL;
    return jary.at(4).toString();
}

void XwareController::bindCodeToXware(QString code)
{
    XwareWebController::getInstance()->executeJS("pointBindNewMachine(\""+ code +"\");");
}

bool XwareController::tryToMakeDir(QString dirPath)
{
    QDir dir;
    return dir.mkpath(dirPath);
}

void XwareController::login(QString userName, QString pwd)
{
    XwareWebController::getInstance()->login(userName, pwd);
}

void XwareController::logout()
{
//    emit sLoginResult(x_Logout);
    XwareWebController::getInstance()->logout();
}

void XwareController::startFeedbackDloadList()
{
    XwarePopulateObject::getInstance()->startFeedbackDloadList();
}

void XwareController::addXwareFirmware()
{
    tryToMakeDir(XWARE_CONSTANTS_STRUCT.XWARE_WORK_DIR);

    // changed work dir
    QDir::setCurrent(XWARE_CONSTANTS_STRUCT.XWARE_WORK_DIR);

    QProcess *pro = new QProcess();
    pro->setProgram(QString("wget"));
    pro->setWorkingDirectory(XWARE_CONSTANTS_STRUCT.XWARE_WORK_DIR);
    QStringList arg;
    arg<<XWARE_CONSTANTS_STRUCT.XWARE_FIRMWARE_LOCATION;
    pro->setArguments(arg);
    pro->start();

    connect(pro, SIGNAL(finished(int,QProcess::ExitStatus)),
            this, SLOT(getXwareFirmwareFinishHandle(int,QProcess::ExitStatus)));

    // timer out @choldrim
}

void XwareController::removeXwareFirmware()
{
    // remove xware firmware
    QDir xwareCfgDir(XWARE_CONSTANTS_STRUCT.XWARE_HOME);
    bool tag = true;
    if(xwareCfgDir.exists())
    {
        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<"remove xware home";
         xwareCfgDir.removeRecursively();
    }

}

void XwareController::tryAutomaticLogin(QString userName, QString pwd)
{
    XwareWebController::getInstance()->tryAutomaticLogin(userName, pwd);
}

void XwareController::loginResult(XwareLoginResultType rs)
{
    if(rs == x_LoginSuccess)
    {
        QTimer::singleShot(2000, XwarePopulateObject::getInstance(), SLOT(getAllBindedPeerIds()));
    }

    emit sLoginResult(rs);
}


void XwareController::tryToStartAndBindXware(QStringList allPeerList)
{
    // (1) get all peer IDs of current user
    // this step has been ellipsised

    // (2) get local machine peer id
    QString id = getLocalPeerId();

    // (3) compare
    bool isMatch = false;
    if(id != "")
    {
        foreach(QString idTmp , allPeerList)
        {
            if(idTmp == id)
            {
                isMatch = true;
            }
        }
    }

    // (4.1) matched the peerid in the web peer list
    if(isMatch)
    {
        // set this machine to default download machine
        XwareWebController::getInstance()->executeJS("pointSetDefaultMachine("+ id +");");

        // (5) start ETM
        if(!startETM())
        {
            qDebug()<<"[fail] fail to start ETM !!";
            return;
        }
    }

    // (4.2) dosen't matched
    else
    {
        //  try to delete local xware config
        if (!tryToClearXwareCfg(XWARE_CONSTANTS_STRUCT.XWARE_CFG_DIR))
        {
            qDebug()<<"[error] occur a failure error when delete xware config !!";
        }

        // (5) start ETM
        if(!startETM())
        {
            qDebug()<<"[fail] fail to start ETM !!";
            return;
        }

        // wait a minute for the ETM process
        QEventLoop loop;
        QTimer::singleShot(5000, &loop, SLOT(quit()));
        loop.exec();

        // (6) bind code
        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<"binding code !!";
        QString jsonCode = getCodeFromJson(); // peer id
        if(jsonCode == "")
        {
            qDebug()<<"[error]empty, get code from json unsuccessfully , return";
            return;
        }
        bindCodeToXware(jsonCode);
    }

//    XwareWebController::getInstance()->reloadWebView();
    QTimer::singleShot(2000, XwarePopulateObject::getInstance(),
                       SLOT(startFeedbackDloadList()));
}

void XwareController::getXwareFirmwareFinishHandle(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(exitStatus == QProcess::NormalExit)
    {
        // unzip
        system("unzip -o XwareFirmxware.zip");

        system("rm -f XwareFirmxware.zip");

        // reflash the
        XwareWebController::getInstance()->reloadWebView();

        emit sAddXwareSupportResult(1);
    }
    else
    {
        emit sAddXwareSupportResult(0);
    }

    QProcess *pro = static_cast<QProcess*>(sender());
    delete pro;
    pro = NULL;
}

void XwareController::finishDownloadHandle(QString URL)
{
    emit sFinishDownload(URL);
}

QString XwareController::getLocalPeerId()
{
    QString peerId = "";
    peerId = getValueFromEtmcfg("rc.peerid");
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"get local machine peer id: "<<peerId;
    return peerId;
}

