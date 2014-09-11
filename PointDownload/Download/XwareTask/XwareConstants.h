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
    static const bool DEBUG = true;
    static const bool DEBUG_2 = false;

    int  ETM_PORT;  // default port

    // cfg
    QString HOME_PATH;
    QString POINT_CFG_DIR ;
    QString XWARE_CFG_DIR ;
    QString XWARE_ETM_CFG;

    // work dir
    QString XWARE_HOME;
    QString XWARE_WORK_DIR;
    QString XWARE_MOUNTS_DIR;
    QString XWARE_TMP_DIR;
    QString XWARE_START_UP_PATH;
    QString XWARE_ETM_PATH;

    // xware firmware location
    QString XWARE_FIRMWARE_LOCATION;

    // url
    QString URLSTR;

    // msg spliter
    const QString SPLITER_BTWN_DATA = "#..#";
    const QString SPLITER_END = "#.^_^.#";
    const QString SPLITER_DEFAULT_PARAM = "--";

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

        // xware firmware location
        XWARE_FIRMWARE_LOCATION = "https://gitcafe.com/choldrim/PointXwareTest/raw/master/XwareFirmxware.zip";

        // url
        URLSTR = "http://127.0.0.1:" + QString::number(ETM_PORT) + "/";
    }

}XWARE_CONSTANTS_STRUCT;



#endif // XWARECONSTANTS_H
