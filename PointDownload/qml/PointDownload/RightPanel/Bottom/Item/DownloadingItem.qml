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
import "../DataFormatHelper.js" as DataFormat
import taskInfo 1.0

Rectangle {
    id: downloadingItem

    width: parent.width
    height: 60 + downloadingMenu.height

    color: "#32738e"
    opacity: 0.7
    radius: 4

    anchors.horizontalCenter: parent.horizontalCenter

    TaskInfo {
        id: task
    }

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
            text: name
            color: "#ffffff"
            font.bold: true
            font.pixelSize: 12
            clip: true
            elide: Text.ElideRight
            width: parent.width < 200 ? 100 : parent.width - 200
            anchors {left: ingIcon.right; leftMargin: 13; top: parent.top; topMargin: 17}
        }

        Text {
            text: DataFormat.formatFileSize(size);
            color: "#ffffff"
            font.bold: true
            font.pixelSize: 12
            anchors {left: ingIcon.right; leftMargin: 13; bottom: parent.bottom; bottomMargin: 13}
        }

        Text {
            text: DataFormat.formatDownloadSpeed(speed);
            color: "#ffffff"
            font.bold: true
            font.pixelSize: 12
            anchors {right: parent.right;rightMargin: 15; verticalCenter: parent.verticalCenter}
        }

        Text {
            text: percentage.toFixed(2) + " %";
            color: "#ffffff"
            font.bold: true
            font.pixelSize: 9
            anchors {right: parent.right;rightMargin: 15; bottom:parent.bottom;bottomMargin: 5}
        }

        Rectangle{
            id: percentageRec
            color: "#e03d48"
            height: 4
            width: parent.width * percentage / 100
            anchors {bottom: parent.bottom; left:parent.left}

            property int percentageOld: 0;

            onWidthChanged: {
                percentageChangeAnima.start()
                percentageOld = width;
            }
        }

        MouseArea {
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                //ingMenu.height = ingMenu.height == 0 ? 40:0
                if (downloadingMenu.height == 0)
                    showMenuAnima.start()
                else
                    hideMenuAnima.start()
            }
        }

    }

    // 正在下载的项的菜单
    DownloadingMenu {
        id: downloadingMenu
        height: 0

        offlineSpeed: ""
        hightSpeed: ""

        anchors {bottom: parent.bottom; left: parent.left}

        SequentialAnimation {
            id: showMenuAnima
            NumberAnimation { target: downloadingMenu; property: "height"; to: 40; duration: 250; easing.type: Easing.InOutQuad }
        }
        SequentialAnimation {
            id: hideMenuAnima
            NumberAnimation { target: downloadingMenu; property: "height"; to: 0; duration: 250; easing.type: Easing.InOutQuad }
        }
    }
    SequentialAnimation {
        id: percentageChangeAnima
        NumberAnimation { target: percentageRec; property: "width";
            from:percentageRec.percentageOld; to: parent.width * percentage / 100; duration: 600; easing.type: Easing.InOutQuad }
    }

}
