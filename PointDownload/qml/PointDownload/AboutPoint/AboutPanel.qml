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
        id: aboutArrow
        source: "qrc:/images/aboutpoint/arrow-white"
        width: 40
        height: 40
        anchors {left:parent.left; verticalCenter: parent.verticalCenter}
    }

    Rectangle{
        id:titleRec
        width: parent.width - aboutArrow.width * 3 / 2
        height: 80
        color: "#44b1b4"
        anchors {left: parent.left;leftMargin: 25; top:parent.top; topMargin: 30}

        Text{
            text: qsTr("Point Team")
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
    }

    TextEdit{
        enabled: false
        font.pixelSize: 13
        color:"#9b9fb1"
        font.bold: true
        text: qsTr("Team members：

Bonse   Kumahime   Match   起点  神奇大叔

Contact:

PointTeam@qq.com")
        anchors {horizontalCenter: parent.horizontalCenter;top:parent.top; topMargin: 130}
    }
}
