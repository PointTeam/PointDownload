/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Match <2696627729@qq.com>
* Maintainer: Match <2696627729@qq.com>
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
/*******************************************************************
Date:   2014.4.5~
Description:
Others:

History:
**********************************************************************/

import QtQuick 2.0
import Singleton.DownloadDataSender 1.0
import "../../../ToolTip/ToolTipCreator.js" as Tooltip

Rectangle {
    id: trashMenu

    property int menuLeftMargin: 25
    property string downloadURL: ""

    width: parent.width
    height: 40
    radius: 4
    opacity: 0.8
    color: "#ffffff"

    MenuButton {
        id: menuReDownload
        height: parent.height - 10
        iconPath: "qrc:/images/right/resume"
        anchors {left: parent.left; leftMargin: menuLeftMargin; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                Tooltip.fadeInDelay = 200;
                Tooltip.fadeOutDelay = 200;
                Tooltip.tip = qsTr("Redownload")//"重新下载";
                Tooltip.showTipe(menuReDownload);
                parent.opacity = 0.8;
            }
            onExited: {
               Tooltip.close();
                parent.opacity = 1;
            }
            onClicked:
            {
                //在新增下载项时再做处理qml显示界面
                //调用C++类做文件处理
                DownloadDataSender.controlItem("dl_trash","download_redownload",downloadURL)
            }
        }
    }
    MenuButton {
        id: menuDelete
        height: parent.height - 10
        iconPath: "qrc:/images/right/delete"
        anchors {left: menuReDownload.right; leftMargin: menuLeftMargin; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                Tooltip.fadeInDelay = 200;
                Tooltip.fadeOutDelay = 200;
                Tooltip.tip = qsTr("Double Click Will Delete")//" 双击彻底删除";
                Tooltip.showTipe(menuDelete);
                parent.opacity = 0.8;
            }
            onExited: {
               Tooltip.close();
                parent.opacity = 1;
            }
            onDoubleClicked:
            {
                //处理qml显示界面
                downloadTrashPage.moveItem(downloadURL)
                DownloadDataSender.controlItem("dl_trash","download_delete",downloadURL)
            }
        }
    }
}
