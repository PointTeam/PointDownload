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

import QtQuick 2.0

Rectangle {
    width: 420
    height: 320
    color: "#323355"

    Image{
        id: softwareArrow
        source: "qrc:/images/aboutpoint/arrow-lightpurple"
        width: 40
        height: 40
        anchors {left:parent.left; verticalCenter: titleRec.verticalCenter}
    }

    Rectangle{
        id:titleRec
        width: parent.width - softwareArrow.width * 3 / 2
        height: 80
        color: "#a583d5"
        anchors {left: parent.left;leftMargin: 25; top:parent.top; topMargin: 15}

        Text{
            text: qsTr("Convenient . Easy to use . Efficient")
            font.pixelSize: 17
            font.bold: true
            color: "#ffffff"
            anchors {horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
        }
    }
    Rectangle{
        id:textRec
        width: titleRec.width
        height: 230
        color: "#ffffff"
        anchors {left: titleRec.left; top: titleRec.bottom}
        TextEdit{
            id:edit1
            enabled: false
            font.pixelSize: 12
            color:"#9b9fb1"
            font.bold: true
            text: qsTr("PointDownload

PointDownload is a software that can help you download
various kinds of documents efficiently.
The current version supports HTTP, besides,
the future one will support ED2K, BT and FTP,etc.
The operating systems,LinuxDeepin2014, Ubuntu14.04,
UbuntuKy14.04,are supported by the current version.")
            anchors {horizontalCenter: parent.horizontalCenter;top: parent.top; topMargin: 20}
        }
        TextEdit{
            enabled: false
            font.pixelSize: 11
            color: "#9b9fb1"
            font.bold: true
            text:qsTr("<PointDownload>
Copyright © <2014> <PointTeam>
This program comes with ABSOLUTELY NO WARRANTY
For more details:<http://www.gnu.org/licenses/gpl-3.0.html>")
            anchors {bottom: parent.bottom; bottomMargin: 20; left: edit1.left}
        }
    }
}
