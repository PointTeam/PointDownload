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

class XwareController : public QObject
{
    Q_OBJECT
public:
    ~XwareController();
    static XwareController *getInstance();
    void startFeedbackDloadList();

    // called by setting dialog
    void login(QString userName, QString pwd);
    void logout();
    void addXwareFirmware();   // add the xware firmware
    void removeXwareFirmware();
    void tryAutomaticLogin(QString userName, QString pwd);

signals:
    void sLoginResult(XwareLoginResultType);
    void sRealTimeDataChanged(DownloadingItemInfo);
    void sAddXwareSupportResult(int);     // add xware support result (to the setting dialog)
    void sFinishDownload(QString);

private slots:
    void loginResult(XwareLoginResultType rs);
    void tryToStartAndBindXware(QStringList allPeerList);
    void getXwareFirmwareFinishHandle(int exitCode, QProcess::ExitStatus exitStatus);   // finish downloading xware firmware
    void finishDownloadHandle(QString URL);

private:
    explicit XwareController(QObject *parent = 0);
    QString getValueFromEtmcfg(QString key);         // get etm.cfg value by key, ( it's a tool method )
    QString getLocalPeerId();               // get local peer id(machine code) from etm.cfg
    bool startETM();
    bool tryToClearXwareCfg(QString cfgPath);
    QString getCodeFromJson();          // get local peer id(machine code) from json , from "http://127.0.0.1:9000/getsysinfo"
    void bindCodeToXware(QString code);
//    void parseTask(QString taskInfo);   //

private:
    static XwareController * xwareController;
    QStringList allPeerIds;
    QProcess *ETMProcess;
};

#endif // XWARECONTROLLER_H
