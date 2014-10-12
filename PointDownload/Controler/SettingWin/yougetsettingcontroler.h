#ifndef YOUGETSETTING_H
#define YOUGETSETTING_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include "settingxmlhandler.h"

class YouGetSettingControler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isYouGetEnable READ getIsYouGetEnable WRITE setIsYouGetEnable NOTIFY sIsYouGetEnableChange)
public:
    explicit YouGetSettingControler(QObject *parent = 0);
    ~YouGetSettingControler();

    Q_INVOKABLE void enableYouGet();
    Q_INVOKABLE void disableYouGet();

    bool getIsYouGetEnable();
    void setIsYouGetEnable(bool flag);
signals:
    void gotError(QString errString);
    void installingStep(int step, QString descririytion);

    void sIsYouGetEnableChange();

private slots:
    void downloadError();
    void installFeedback(int exitCode);
    void installError();

private:
    void downloadYouGet();
    void installYouGet();

    void initDownloadProcess();
    void initInstallProcess();
    void initStateFlag();

private:
    const QString YOUGET_MASTER_URL = "https://github.com/soimort/you-get/zipball/master";
    const QString YOUGET_DEVELOP_URL = "https://github.com/soimort/you-get/zipball/develop";
    const QString CONFIG_DIR_PATH =
            QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/.PointConfig";

    QProcess * dlProcess;
    QProcess * inProcess;
    QStringList dlArguments;
    QStringList inArguments;

    bool isYouGetEnable;
};

#endif // YOUGETSETTING_H
