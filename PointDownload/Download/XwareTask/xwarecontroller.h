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

#ifndef XWARECONTROLLER_H
#define XWARECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QEventLoop>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonArray>
#include <QEventLoop>

#include "xwarewebcontroller.h"
#include "XwareDataType.h"
#include "XwareConstants.h"
#include "Controler/SettingWin/xwaresettingcontroler.h"
#include "Controler/topcontrl.h"
#include "downloadxmlhandler.h"


#define GET_R_CODE_MAX_TRY 5  // 5t => 45s
#define GET_R_DEFAULT_INTERVAL 3000  // second

class XwareController : public QObject
{
    Q_OBJECT
public:
    ~XwareController();
    static XwareController *getInstance();
    void startFeedbackDloadList();

    // ===================== called by setting dialog =============================== //
    void login(QString userName, QString pwd, QString vertifyCode = QString(""));
    void logout();
    void addXwareFirmware();                  // add the xware firmware
    void removeXwareFirmware();
    void tryAutomaticLogin(QString userName, QString pwd);
    // =============================================================================== //

signals:
    void sAddXwareSupportResult(bool);     // the result of downloading xware firmware and unziping it (to the setting dialog)
    void sFinishDownload(QString);
    void sBindRouterCodeResult(int);    // the result of bind router code , 1: success, 0: timeout

public slots:
    void stopETM();

private slots:
    void allDestroyHandle();
    void tryToStartAndBindXware(QStringList allPeerList);
    void getXwareFirmwareFinishHandle(int exitCode, QProcess::ExitStatus exitStatus);   // finish downloading xware firmware
    void finishDownloadHandle(QString URL);
    void initDefaultSetting();                         // init default setting, like max running job and download & upload speed limit
    void ETMProcessFinishedHandl(int exitCode, QProcess::ExitStatus exitStatus);

private:
    explicit XwareController(QObject *parent = 0);
    QString getValueFromEtmcfg(QString key);         // get etm.cfg value by key, ( it's a tool method )
    QString getLocalPeerId();                      // get local peer id(machine code) from etm.cfg
    bool startETM();
    bool tryToClearXwareCfg(QString cfgPath);
    QString getCodeFromJson();                // get local peer id(machine code) from json , from "http://127.0.0.1:9000/getsysinfo"
    void bindCodeToXware(QString code);
    bool tryToMakeDir(QString dirPath);
    bool tryToMakeFile(QString filePath);
    bool checkConfigFiles();

private:
    static XwareController * xwareController;
    QStringList allPeerIds;
    QProcess *ETMProcess;
    short getRouterCodeCounter;
};

#endif // XWARECONTROLLER_H
