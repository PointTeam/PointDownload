#ifndef XWARECONSTANTS_H
#define XWARECONSTANTS_H

#include <QString>
#include <QStandardPaths>

static struct XwareConstants
{
    // is output the debug info
    const bool DEBUG = false;

    int  ETM_PORT;  // default port

    // cfg
    QString HOME_PATH ;
    QString POINT_CFG_DIR ;
    QString XWARE_CFG_DIR ;
    QString XWARE_ETM_CFG;

    // work dir
    QString XWARE_HOME;
    QString XWARE_WORK_DIR;
    QString XWARE_ETM_PATH;

    // xware firmware location
    QString XWARE_FIRMWARE_LOCATION;

    // url
    QString URLSTR;

    // msg spliter
    const QString spliterBtwData = "#..#";
    const QString spliterEnd = "#.^_^.#";
    const QString defaultPara = "--";

    XwareConstants()
    {
         ETM_PORT = 9000;  // default port

        // cfg
        HOME_PATH = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0) + "/";
        POINT_CFG_DIR = HOME_PATH + ".PointConfig/";
        XWARE_CFG_DIR = POINT_CFG_DIR + "XwarePlugin/cfg/";
        XWARE_ETM_CFG = XWARE_CFG_DIR + "etm.cfg";

        // work dir
        XWARE_HOME = POINT_CFG_DIR + "XwarePlugin/";
        XWARE_WORK_DIR = XWARE_HOME + "Xware/";
        XWARE_ETM_PATH = XWARE_WORK_DIR + "EmbedThunderManager";

        // xware firmware location
        XWARE_FIRMWARE_LOCATION = "https://gitcafe.com/choldrim/PointXwareTest/raw/master/XwareFirmxware.zip";

        // url
        URLSTR = "http://127.0.0.1:" + QString::number(ETM_PORT) + "/";
    }

}XWARE_CONSTANTS_STRUCT;



#endif // XWARECONSTANTS_H
