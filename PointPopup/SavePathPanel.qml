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

import QtQuick 2.0
import Singleton.DataControler 1.0

Rectangle {

    id:savePanel
    radius: 25
    color:"#ffffff"

    property string freeSpaceSize: DataControler.freeSpace

    // 存储路径设置
    Text{
        text:qsTr("Save As:")
        font.pixelSize: 12
        color: "#008dac"
        anchors {left: savePathPanel.left; leftMargin: 20; bottom: savePathPanel.top}
    }

    Rectangle{
        id: savePathPanel
        width: parent.width
        height: parent.height
        radius: 25
        color:"#ffffff"
        border.width: 1.5
        border.color: "#b2b2b2"

        state: "pointGetMouse"

        Rectangle{
            id: backRec
            color: "#69b4ad"
            width: pointText.width + 30
            height: pointText.height + 10
            radius: 20
            anchors {verticalCenter: pointText.verticalCenter}
            x:pointText.x -15
        }

        Text{
            id:pointText
            text:qsTr("Default")
            color: "#6d6f6e"
            font.bold: true
            anchors {left: parent.left; leftMargin: 40; top:parent.top; topMargin: 12}

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: pathPanel.state = "showDetails"
                onClicked: {
                    savePathPanel.state = "pointGetMouse"
                    DataControler.selectSavePath("Default")
                }
            }
        }
        Text{
            id:deskTopText
            text:qsTr("Desktop")
            color: "#6d6f6e"
            font.bold: true
            anchors {horizontalCenter: parent.horizontalCenter; top:parent.top; topMargin: 12}
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: pathPanel.state = "showDetails"
                onClicked: {
                    savePathPanel.state = "desktopGetMouse"
                    DataControler.selectSavePath("Desktop")
                }
            }
        }
        Text{
            id:selectText
            text:qsTr("Other")
            color: "#6d6f6e"
            font.bold: true
            anchors {right:parent.right;rightMargin: 40; top:parent.top; topMargin: 12}
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: pathPanel.state = "showDetails"
                onClicked: {
                    savePathPanel.state = "selectGetMouse"
                    DataControler.selectSavePath("Other")
                }
            }
        }


        Rectangle{
            id:pathPanel
            width: parent.width - 20
            height: 20
            radius: 5
            clip: true
            visible: false
            state: ""
            anchors {horizontalCenter: parent.horizontalCenter; bottom: parent.bottom; bottomMargin: 5}
            //路径
            TextInput{
                id:pathText
                clip: true
                text:DataControler.fileSavePath
                color: "#6d6f6e"
                selectByMouse: true
                selectionColor: "#59add4"
                enabled: true
                width: parent.width - 70
                anchors {left: parent.left; verticalCenter: parent.verticalCenter}
            }


            //间隔
            Rectangle{
                id: splitRec
                width:2
                height: freeSpaceRec.height - 6
                radius: 2
                color: "#6bb8ae"
                anchors {left: pathText.right; leftMargin: 3;verticalCenter: freeSpaceRec.verticalCenter}
            }

            //剩余空间大小
            Rectangle {
                id: freeSpaceRec
                width: 40
                radius: 5
                height: pathPanel.height
                anchors {left:splitRec.left;leftMargin: 6; verticalCenter: pathText.verticalCenter}
                Text{
                    id:freeSpaceText
                    color: "#6d6f6e"
                    text:freeSpaceSize
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            MouseArea{
                anchors {fill: parent; topMargin: 15}
                hoverEnabled: true
                onEntered: pathPanel.state = "showDetails"
                onExited: pathPanel.state = "hideDetails"
            }


            states:[
                State {
                    name: "showDetails"
                    PropertyChanges {target: savePanel; height: 60}
                    PropertyChanges {target: pathPanel; visible: true}
                    PropertyChanges {target: pathPanel; opacity: 1}
                },
                State {
                    name: "hideDetails"
                    PropertyChanges {target: savePanel; height: 40}
                    PropertyChanges {target: pathPanel; visible: false}
                    PropertyChanges {target: pathPanel; opacity: 0}
                }

            ]
            transitions: [
                Transition {
                    from: "*";to: "*"
                    PropertyAnimation {
                        properties: "height"; duration: 300
                    }
                    PropertyAnimation {
                        properties: "opacity"; duration: 300
                    }
                }
            ]

        }


        states:[
            State {
                name: "pointGetMouse"
                PropertyChanges {target: pointText; color: "#ffffff"}
                PropertyChanges {target: backRec;x:pointText.x - 15; width: pointText.width + 30}
            },
            State {
                name: "desktopGetMouse"
                PropertyChanges {target: deskTopText; color: "#ffffff"}
                PropertyChanges {target: backRec;x:deskTopText.x - 15; width: deskTopText.width + 30}
            },
            State {
                name: "selectGetMouse"
                PropertyChanges {target: selectText; color: "#ffffff"}
                PropertyChanges {target: backRec;x:selectText.x - 15; width: selectText.width + 30}
            }

        ]

        transitions: [
            Transition {
                from: "*";to: "*"
                PropertyAnimation {
                    properties: "x"; duration: 300
                }
                PropertyAnimation {
                    properties: "color"; duration: 300
                }
            }
        ]
    }

    function getSavePath()
    {
        return pathText.text
    }

}
