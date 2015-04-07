/***********************************************************************
*PointDownload
*Copyright (C) 2014~2015  PointTeam
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
import Singleton.DLDataConverter 1.0
import "../../../ToolTip/MenuTooltipCreator.js" as MenuToolTip

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
        iconSource: "qrc:/images/right/resume"
        anchors {left: parent.left; leftMargin: menuLeftMargin; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                MenuToolTip.showMenuToolTip(menuReDownload,qsTr("Redownload"))
                parent.opacity = 0.8;
            }
            onExited: {
               MenuToolTip.close();
                parent.opacity = 1;
            }
            onClicked:
            {
                var task = trashModel.get(index);
                DLDataConverter.restartTask(downloadURL);
                trashModel.remove(index);
                //在新增下载项时再做处理qml显示界面
                //调用C++类做文件处理
//                DLDataConverter.controlItem("dl_trash","download_redownload",downloadURL);
            }
        }
    }
    MenuButton {
        id: menuDelete
        height: parent.height - 10
        iconSource: "qrc:/images/right/delete"
        anchors {left: menuReDownload.right; leftMargin: menuLeftMargin; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                MenuToolTip.showMenuToolTip(menuDelete,qsTr("Double Click Will Delete"))
                parent.opacity = 0.8;
            }
            onExited: {
               MenuToolTip.close();
                parent.opacity = 1;
            }
            onDoubleClicked:
            {
                DLDataConverter.removeTask(rawUrl);
                trashModel.remove(index);
            }
        }
    }
}
