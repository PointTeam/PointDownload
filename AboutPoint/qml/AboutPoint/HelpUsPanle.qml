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
        id: helpUsArrow
        source: "qrc:/images/arrow-red"
        width: 40
        height: 40
        anchors {left:parent.left; verticalCenter: titleRec.verticalCenter}
    }

    Rectangle{
        id:titleRec
        width: parent.width - helpUsArrow.width * 3 / 2
        height: 80
        color: "#ae3531"
        anchors {left: parent.left;leftMargin: 25; bottom:parent.bottom}

        Text{
            text: qsTr("We need your help")
            font.pixelSize: 17
            font.bold: true
            color: "#ffffff"
            anchors {horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
        }
    }
    Rectangle{
        id:textRec
        width: titleRec.width
        height: 210
        color: "#ffffff"
        anchors {left: titleRec.left;bottom:titleRec.top}
    }

    TextEdit{
        enabled: false
        font.pixelSize: 13
        color:"#9b9fb1"
        font.bold: true
        text: qsTr("We hope that you can contact us when you find BUG
in the process of using,which will be of great help to us.
We still hope that those who take an interest in
this software can install it in Linux with
various Linux Distributions and test it.
Also, if you can provide more help, please contact us. ")
        anchors {horizontalCenter: parent.horizontalCenter;top:parent.top; topMargin: 80}
    }
}
