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
    getRouterCodeCounter = 0;

    // login result
    connect(XwareWebController::getInstance(), SIGNAL(sLoginResult(XwareLoginResultType)),
            this, SLOT(loginResult(XwareLoginResultType)));

    // all peer ids
    connect(XwarePopulateObject::getInstance(), SIGNAL(sReturnAllBindedPeerIds(QStringList)),
            this, SLOT(tryToStartAndBindXware(QStringList)));

    // destroy
    connect(TopContrl::getInstance(), SIGNAL(signalAllDestroy()), this, SLOT(allDestroyHandle()));

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

void XwareController::allDestroyHandle()
{
    qDebug()<<"[xware info] xware exit and stop ETM";
    system("pkill Embed");
}

QString XwareController::getValueFromEtmcfg(QString key)
{
    QString value = "";
    QFile file(XWARE_CONSTANTS_STRUCT.XWARE_ETM_CFG);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"[xware error]open xware etm.cfg file error or it doesn't exist !!";
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


    SettingXMLHandler xmlHandle;
    QString defaultDloadPath = xmlHandle.getChildElement(GeneralSettings, "SavePath");

    ETMProcess = new QProcess();
    QStringList args;
    args<<defaultDloadPath;
    args<<XWARE_CONSTANTS_STRUCT.XWARE_ETM_PATH;
    args<<"--verbose";
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<< "start XwareStartUp to start ETM ==>"<<XWARE_CONSTANTS_STRUCT.XWARE_START_UP_PATH;
    ETMProcess->setProgram(XWARE_CONSTANTS_STRUCT.XWARE_START_UP_PATH);
    ETMProcess->setArguments(args);
    ETMProcess->start();


    /*
    ETMProcess = new QProcess();
    QStringList args;
    args<<"--verbose";
    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<< "start ETM ==>"<<XWARE_CONSTANTS_STRUCT.XWARE_ETM_PATH;
    ETMProcess->setWorkingDirectory(XWARE_CONSTANTS_STRUCT.XWARE_WORK_DIR); // set work directory
    ETMProcess->setProgram(XWARE_CONSTANTS_STRUCT.XWARE_ETM_PATH);
    ETMProcess->setArguments(args);
    ETMProcess->start();
    */

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
    QString code = "";
    QUrl url(XWARE_CONSTANTS_STRUCT.URLSTR + "getsysinfo");

    while(getRouterCodeCounter < GET_R_CODE_MAX_TRY)
    {
        // interval : 3 => 6 => 9 seconds
        ++getRouterCodeCounter;
        int interval = GET_R_DEFAULT_INTERVAL * getRouterCodeCounter;

        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<"get code from json interval: "<<interval << " s";

        QEventLoop loop;
        QTimer::singleShot(interval, &loop, SLOT(quit()));
        loop.exec();

        QNetworkAccessManager manager;
        // request
        QNetworkReply *reply = manager.get(QNetworkRequest(url));
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        // wait for message
        loop.exec();
        reply->disconnect();

        // 读到的信息
        QString jsonStr = reply->readAll();
        QJsonDocument jsd = QJsonDocument::fromJson(jsonStr.toUtf8());
        QJsonArray jary = jsd.array();

        code = jary.at(4).toString().trimmed();

        if(code.length() != 0)
        {
            break;
        }
        else
        {
//            NormalNotice::getInstance()->showMessage(tr("Fail to Get Router Code"), Notice_Color_Error,
//                                                     tr("Fail to Get Router Code, Try to Get It Again"));
        }
    }

    if(XWARE_CONSTANTS_STRUCT.DEBUG)
        qDebug()<<"Router Code: "<<code;

    return code;
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

void XwareController::login(QString userName, QString pwd, QString vertifyCode)
{
    XwareWebController::getInstance()->login(userName, pwd, vertifyCode);
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

    // ------------------- temp ----------------------------- //

    tryToMakeDir(XWARE_CONSTANTS_STRUCT.XWARE_MOUNTS_DIR + "PointXDownloads");
    tryToMakeDir(XWARE_CONSTANTS_STRUCT.XWARE_TMP_DIR);

    // ----------------------------------------------------- //


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
    // stop etm
    system("pkill Embed");

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
        // this need to be improved
        QTimer::singleShot(2000, XwarePopulateObject::getInstance(), SLOT(getAllBindedPeerIds()));
    }

    emit sLoginResult(rs);
}


void XwareController::tryToStartAndBindXware(QStringList allPeerList)
{
    // (1) get all peer IDs of current user
    // this step has been excuted before

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
        // set this machine as default downloader
        XwarePopulateObject::getInstance()->setDefaultDownloader(id);

        // (5) start ETM
        if(!startETM())
        {
            NormalNotice::getInstance()->showMessage(tr("Fail to Start ETM"), Notice_Color_Error,
                                                     tr("Please check whether there is anything in ~/.PointConfig/XwarePlugin/Xware"));
            return;
        }
    }

    // (4.2) dosen't matched
    else
    {
        //  try to delete local xware config
        if (!tryToClearXwareCfg(XWARE_CONSTANTS_STRUCT.XWARE_CFG_DIR))
        {
            NormalNotice::getInstance()->showMessage(tr("Error"), Notice_Color_Error,
                                                     tr("occur a failure error when deleting xware config"));
            emit sBindRouterCodeResult(0);
            return;
        }

        // (5) start ETM
        if(!startETM())
        {
            NormalNotice::getInstance()->showMessage(tr("Fail to Start ETM"), Notice_Color_Error,
                                                     tr("Please check whether there is anything in ~/.PointConfig/XwarePlugin/Xware"));
            emit sBindRouterCodeResult(0);
            return;
        }

        // (6) bind code
        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<"binding code !!";

        QString jsonCode = getCodeFromJson(); // peer id


        if(jsonCode == "")
        {
            NormalNotice::getInstance()->showMessage(tr("Router Code Error"), Notice_Color_Error,
                                                     tr("Get Router Code Timeout, Code is Empty!"));
            emit sBindRouterCodeResult(0);
            return;
        }
        else
        {
            NormalNotice::getInstance()->showMessage(tr("Get Router Code Successfully"), Notice_Color_Success,
                                                     tr("Get Router Code Successfully, Trying to Bind Xware now!"));
        }

        bindCodeToXware(jsonCode);

        // this can help js function pointSetDefaultDownloader()
        QString id_tmp = getLocalPeerId();
        XwarePopulateObject::getInstance()->setDefaultDownloader(id_tmp);
    }

    QTimer::singleShot(200, this, SLOT(initDefaultSetting()));

    NormalNotice::getInstance()->showMessage(tr("Xware Login Successfully"), Notice_Color_Success,
                                             tr(":D"));

    emit sBindRouterCodeResult(1);
}

void XwareController::initDefaultSetting()
{
    // max task
    XwareSetting::setMaxRunTaskNumber(-1);

    // speed limits
    XwareSetting::setUploadSpeedLimit(-1);  // tmp speed, not limit
    XwareSetting::setDownloadSpeedLimit(-1); // tmp speed, not limit
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

