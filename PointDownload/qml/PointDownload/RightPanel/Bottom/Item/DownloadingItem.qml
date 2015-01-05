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
Date:   2014.3.20~
Description:
    正在下载的项组件，每个正在下载的项都会使用这个组件新建一个表示
    正在下载的下载项
Others:

History:
**********************************************************************/

import QtQuick 2.0

Rectangle {
    id: downloadingItem

    property string iconPath: "qrc:/images/right/unknow-file"
    property string checkIconPath: "qrc:/images/right/uncheck"
    property real ingPercentage:0
    property string fileName: ""
    property string fileURL: ""
    property string fileState: "dlstate_suspend"  // "Downloading" or "Ready"
    property string thunderOfflineSpeed:""
    property string thunderHightSpeed:""
    property string netSpeed: ""
    property string fileSize: ""
    property string dlToolsType: ""
    property real percentageOldWidth:0

    width: parent.width
    height: 60 + ingMenu.height

    color: "#32738e"
    opacity: 0.7
    radius: 4

    anchors.horizontalCenter: parent.horizontalCenter

    Rectangle {
        id: infoRec
        width: parent.width
        height: 60
        color: "#32738e"
        opacity: 0.7
        radius: 4
        clip: true

        anchors.top: parent.top

        // 文件图标
        Image {
            id: ingIcon
            source: iconPath
            anchors {left: parent.left; leftMargin: 15; verticalCenter: parent.verticalCenter}
        }

        Text {
            text: fileName
            color: "#ffffff"
            font.bold: true
            font.pixelSize: 12
            clip: true
            elide: Text.ElideRight
            width: parent.width < 200 ? 100 : parent.width - 200
            anchors {left: ingIcon.right; leftMargin: 13; top: parent.top; topMargin: 17}
        }

        Text {
            text: fileSize
            color: "#ffffff"
            font.bold: true
            font.pixelSize: 12
            anchors {left: ingIcon.right; leftMargin: 13; bottom: parent.bottom; bottomMargin: 13}
        }

        Text {
            text: netSpeed
            color: "#ffffff"
            font.bold: true
            font.pixelSize: 12
            anchors {right: parent.right;rightMargin: 15; verticalCenter: parent.verticalCenter}
        }

        Text {
            text: ingPercentage + " %"
            color: "#ffffff"
            font.bold: true
            font.pixelSize: 9
            anchors {right: parent.right;rightMargin: 15; bottom:parent.bottom;bottomMargin: 5}
        }

        Rectangle{
            id: percentageRec
            color: "#e03d48"
            height: 4
            width: parent.width * ingPercentage / 100
            anchors {bottom: parent.bottom; left:parent.left}
            onWidthChanged: {
                percentageChangeAnima.start()
                percentageOldWidth = width;
            }
        }

        MouseArea {
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                //ingMenu.height = ingMenu.height == 0 ? 40:0
                if (ingMenu.height == 0)
                    showMenuAnima.start()
                else
                    hideMenuAnima.start()
            }
        }

    }

    // 正在下载的项的菜单
    DownloadingMenu {
        id: ingMenu
        height: 0
        downloadURL: fileURL//for control button
        downloadState: fileState
        offlineSpeed: thunderOfflineSpeed
        hightSpeed: thunderHightSpeed

        anchors {bottom: parent.bottom; left: parent.left}

        SequentialAnimation {
            id: showMenuAnima
            NumberAnimation { target: ingMenu; property: "height"; to: 40; duration: 250; easing.type: Easing.InOutQuad }
        }
        SequentialAnimation {
            id: hideMenuAnima
            NumberAnimation { target: ingMenu; property: "height"; to: 0; duration: 250; easing.type: Easing.InOutQuad }
        }
    }
    SequentialAnimation {
        id: percentageChangeAnima
        NumberAnimation { target: percentageRec; property: "width";
            from:percentageOldWidth; to: parent.width * ingPercentage / 100; duration: 600; easing.type: Easing.InOutQuad }
    }

}
