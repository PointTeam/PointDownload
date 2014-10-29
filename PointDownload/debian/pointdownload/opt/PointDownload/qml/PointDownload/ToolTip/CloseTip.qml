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
    id: closeTip
    width: 200
    height: 165

    property int fadeInDelay
    property int fadeOutDelay

    color: "#292c31"
    radius: 15
    opacity: 0
    anchors {top: parent.top; right: parent.right}
    state: ""

    Text {
        id: sureText
        text: "要直接退出？"
        color: "#ffffff"
        font.bold:true
        font.pixelSize: 14
        anchors {top: parent.top; topMargin: 10; horizontalCenter: parent.horizontalCenter}
    }

    Rectangle {
        id: yesRec
        width: parent.width
        height: 20
        color: "#292c31"
        anchors {top: sureText.bottom; topMargin: 10; left: parent.left;leftMargin: 35}
        Image{
            id: yesCheckImg
            source: "qrc:/images/tooltip/radio-uncheck"
            width: parent.height
            height: parent.height
            anchors.left: parent.left
        }
        Text {
            text: "是，直接退出!"
            font.bold: true
            color: "#999a9c"
            font.pixelSize: 12
            width: parent.width - yesCheckImg.width
            height: parent.height
            anchors.left: yesCheckImg.right
            anchors.leftMargin: 10
        }
    }

    Rectangle {
        id: noRec
        width: parent.width
        height: 20
        color: "#292c31"
        anchors {top: yesRec.bottom; topMargin: 10; left: parent.left;leftMargin: 35}
        Image {
            id: noChecImg
            source: "qrc:/images/tooltip/radio-check"
            width: parent.height
            height: parent.height
            anchors.left: parent.left
        }
        Text {
            text: "不，最小化到托盘!"
            font.bold: true
            color: "#999a9c"
            font.pixelSize: 12
            width:parent.width - noChecImg.width
            height: parent.height
            anchors.left: noChecImg.right
            anchors.leftMargin: 10
        }
    }

    Rectangle {
        id: remeberCheckRec
        width: parent.width
        height: 20
        color: "#292c31"
        anchors {top: noRec.bottom; topMargin: 10; left: parent.left;leftMargin: 35}
        Image {
            id: rememberImg
            source: "qrc:/images/tooltip/checkbox-uncheck"
            width: parent.height - 3
            height: parent.height - 3
            anchors.left: parent.left
        }
        Text {
            text: "下次不再提醒"
            font.bold: true
            color: "#999a9c"
            font.pixelSize: 12
            width:parent.width - rememberImg.width
            height: parent.height
            anchors.left: rememberImg.right
            anchors.leftMargin: 10
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (rememberImg.source == "qrc:/images/tooltip/checkbox-uncheck")
                {
                    rememberImg.source = "qrc:/images/tooltip/checkbox-check"
                    //update config file
                }
                else
                {
                    rememberImg.source = "qrc:/images/tooltip/checkbox-uncheck"
                    //update config file
                }
            }
        }
    }

    Rectangle {
        id: okButtonRec
        color: "#ff4589"
        width: 70
        height: 30
        radius: 10

        anchors {bottom: parent.bottom; bottomMargin: 10; horizontalCenter: closeTip.horizontalCenter}

        Text {
            text: "确定"
            color: "#ffffff"
            font.bold: true
            anchors {horizontalCenter: parent.horizontalCenter;verticalCenter: parent.verticalCenter}
        }
        MouseArea{
            anchors.fill: parent
            onClicked: Qt.quit()
        }
    }

    // The object travels from an empty state(on creation) to 'poppedUp' state and then to 'poppedDown' state
    states: [
        State {
            name: "poppedUp"
            PropertyChanges { target: closeTip; opacity: 1 }
            PropertyChanges { target: closeTip; scale: 1 }
        },
        State {
            name: "poppedDown"
            PropertyChanges { target: closeTip; opacity: 0 }
            PropertyChanges { target: closeTip; scale: 0.5 }
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "poppedUp"
            PropertyAnimation { target: closeTip; property: "opacity"; duration: closeTip.fadeInDelay}
            PropertyAnimation { target: closeTip; property: "scale"; duration: closeTip.fadeInDelay}
        },

        Transition {
            from: "poppedUp"
            to: "poppedDown"
            PropertyAnimation { target: closeTip; property: "opacity"; duration: closeTip.fadeOutDelay; }
            PropertyAnimation { target: closeTip; property: "scale"; duration: closeTip.fadeOutDelay; }
        }
    ]


    onStateChanged: {
        if (closeTip.state === "poppedDown") {
            closeTip.destroy(closeTip.fadeOutDelay);
            // If you think that the above line is ugly then,
            //you can destroy the element in onOpacityChanged: if (opacity == 0)
        }
    }
}
