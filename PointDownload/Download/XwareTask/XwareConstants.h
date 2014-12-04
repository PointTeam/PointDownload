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


#ifndef XWARECONSTANTS_H
#define XWARECONSTANTS_H

#include <QString>
#include <QStandardPaths>


static struct XwareConstants
{
    // is output the debug info
    static const bool DEBUG = false;

      // show the test webview
    static const bool DEBUG_2 = false;

    int  ETM_PORT;

    // cfg
    QString HOME_PATH;
    QString POINT_CFG_DIR ;
    QString XWARE_CFG_DIR ;
    QString XWARE_ETM_CFG;

    // files
    QString XWARE_MOUNTS_FILE;
    QString XWARE_SO_FILE;

    // work dir
    QString XWARE_HOME;
    QString XWARE_WORK_DIR;
    QString XWARE_MOUNTS_DIR;
    QString XWARE_TMP_DIR;
    QString XWARE_START_UP_PATH;
    QString XWARE_ETM_PATH;

    // xware firmware location
    QString XWARE_FIRMWARE_LOCATION;
    QString XWARE_FIRMWARE_NAME;

    // url
    QString URLSTR;

    // msg spliter
    QString SPLITER_BTWN_DATA;
    QString SPLITER_END;
    QString SPLITER_DEFAULT_PARAM;

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
        XWARE_MOUNTS_DIR = XWARE_HOME + "mounts/";
        XWARE_TMP_DIR = XWARE_HOME + "tmp/";
        XWARE_WORK_DIR = XWARE_HOME + "Xware/";
        XWARE_ETM_PATH = XWARE_WORK_DIR + "EmbedThunderManager";
        XWARE_START_UP_PATH = "/opt/Point/PointDownload/XwareStartUp";

        // file
        XWARE_MOUNTS_FILE = XWARE_MOUNTS_DIR + "mounts";
        XWARE_SO_FILE = XWARE_WORK_DIR + "mask.so";

        // xware firmware location
        XWARE_FIRMWARE_LOCATION = "https://gitcafe.com/choldrim/PointXwareFirmware/raw/master/XwareFirmxware.zip";
//        XWARE_FIRMWARE_LOCATION = "http://www.linuxdeepin.com/forum/download?id=9303";
        XWARE_FIRMWARE_NAME = "XwareFirmxware.zip";

        // url
        URLSTR = "http://127.0.0.1:" + QString::number(ETM_PORT) + "/";

        SPLITER_BTWN_DATA = "#..#";
        SPLITER_END = "#.^_^.#";
        SPLITER_DEFAULT_PARAM = "--";
    }

}XWARE_CONSTANTS_STRUCT;



#endif // XWARECONSTANTS_H
