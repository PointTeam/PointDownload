#include "yougetsettingcontroler.h"

YouGetSettingControler::YouGetSettingControler(QObject *parent) :
    QObject(parent)
{
    initDownloadProcess();
    initInstallProcess();
    initStateFlag();
}

void YouGetSettingControler::enableYouGet()
{
    downloadYouGet();
}

void YouGetSettingControler::disableYouGet()
{
    QString comm = "rm -r " + CONFIG_DIR_PATH + "/YouGetPlugin";
    system(comm.toLatin1());

    SettingXMLHandler tmpHandler;
    tmpHandler.setChildElement(YouGetSetting,"State","Disable");
    tmpHandler.setChildElement(YouGetSetting,"ExecutePath","you-get");
}

bool YouGetSettingControler::getIsYouGetEnable()
{
    return isYouGetEnable;
}

void YouGetSettingControler::setIsYouGetEnable(bool flag)
{
    isYouGetEnable = flag;
    emit sIsYouGetEnableChange();
}

void YouGetSettingControler::downloadYouGet()
{
    emit installingStep(1,"Downloading You-Get...");

    SettingXMLHandler tmpHandler;
    dlProcess->setWorkingDirectory(tmpHandler.getChildElement(GeneralSettings,"SavePath"));
    dlProcess->start("wget",dlArguments);
}

void YouGetSettingControler::installYouGet()
{
    emit installingStep(2,"Installing you-get...");

    SettingXMLHandler tmpHandler;
    inProcess->setWorkingDirectory(tmpHandler.getChildElement(GeneralSettings,"SavePath"));
    inProcess->start("unzip",inArguments);
}

void YouGetSettingControler::initDownloadProcess()
{
    dlProcess = new QProcess(0);
    connect(dlProcess, SIGNAL(readyReadStandardError()), this, SLOT(downloadError()));

    dlArguments << "-nv";
    dlArguments << "-O";
    dlArguments << "YouGetPlugin.zip";
    dlArguments << YOUGET_DEVELOP_URL;
}

void YouGetSettingControler::initInstallProcess()
{

    inProcess = new QProcess(0);
    connect(inProcess, SIGNAL(readyReadStandardError()), this, SLOT(installError()));
    connect(inProcess,SIGNAL(finished(int)), this, SLOT(installFeedback(int)));

    inArguments << "-x";
    inArguments << "-o";
    inArguments << "YouGetPlugin.zip";
    inArguments << "-d";
    inArguments << CONFIG_DIR_PATH;
}

void YouGetSettingControler::initStateFlag()
{
    SettingXMLHandler tmpHandler;
    if (tmpHandler.getChildElement(YouGetSetting,"State") == "Enable")
        isYouGetEnable = true;
    else
        isYouGetEnable = false;
}

void YouGetSettingControler::downloadError()
{
    QString feedbackData(dlProcess->readAllStandardError());
    if (feedbackData.contains("YouGetPlugin.zip"))
    {
        qDebug() << "Download YouGetPlugin Finish!";
        installYouGet();
    }
    else
    {
        qDebug() << "Download YouGetPlugin Error:"<<feedbackData;
        emit gotError(feedbackData);
    }
}

void YouGetSettingControler::installFeedback(int exitCode)
{
    if (exitCode != 0)
    {
        emit gotError("Install Error!Please Retry!");
    }
    else
    {
        emit installingStep(3,"Installation is completed!");
        QString comm = "mv " + CONFIG_DIR_PATH + "/soimort-you-get* " + CONFIG_DIR_PATH + "/YouGetPlugin";
        system(comm.toLatin1());

        SettingXMLHandler tmpHandler;
        tmpHandler.setChildElement(YouGetSetting,"State","Enable");
        tmpHandler.setChildElement(YouGetSetting,"ExecutePath",CONFIG_DIR_PATH + "/YouGetPlugin/you-get");
    }

}

void YouGetSettingControler::installError()
{
    emit gotError(inProcess->readAllStandardError());
}

YouGetSettingControler::~YouGetSettingControler()
{
    delete dlProcess;
    delete inProcess;
}
