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
Date:   2014.3.20~
Description:
    左侧主面板，包括按钮导航条跟快捷设置按钮
Others:

History:
**********************************************************************/

import QtQuick 2.0

Rectangle {
    width: 110
    height: 62

    id: leftMainPanel
    color: "#08334b"

    Image {
        id: iconImg
        source: "qrc:/images/main/point-32-b"
        width: parent.width * 1 / 6
        height: parent.width * 1 / 6
        anchors {left:parent.left; leftMargin: 20; top: parent.top; topMargin: 15}
    }

    Text {
        id: iconText
        text: qsTr("POINT")
        font.family: "URW Bookman L"
        anchors {left:iconImg.right; leftMargin: 10; verticalCenter: iconImg.verticalCenter}
        font.bold: true
        font.pixelSize: 12
        color: "#e2d9d9"
    }

    Image {
        id: splitLine1
        width: parent.width
        height: 2
        source: "qrc:/images/navigation/left-split"
        anchors {top: iconText.bottom; topMargin: 10}
    }

    Text {
        id: navigationBarText
        text: qsTr("Download")//下载
        anchors {top: splitLine1.top; topMargin: 12; left: parent.left; leftMargin: 12}
        font.bold: true
        font.pixelSize: 13
        color: "#a0acbf"
    }

    NavigationBar {
        id: mainMenu
        width: parent.width
        height: 120
        anchors {top: navigationBarText.bottom; left: parent.left}
    }

    Image {
        id: splitLine2
        width: parent.width
        height: 2
        source: "qrc:/images/navigation/left-split"
        anchors {top: mainMenu.bottom;}
    }

    Text {
        id: shortcutText
        text: qsTr("Quick")//快捷
        anchors {top: splitLine2.top; topMargin: 14; left: parent.left; leftMargin: 12}
        font.bold: true
        font.pixelSize: 13
        color: "#a0acbf"
    }

    ShortcutBar {
        id: shortcutMenu
        width: parent.width
        height: 100
        color: "#08334b"
        anchors {top: shortcutText.bottom; left: parent.left}
    }
}
