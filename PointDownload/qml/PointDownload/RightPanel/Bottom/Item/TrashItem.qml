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

Rectangle {
    id: trashItem

    property string iconPath: "qrc:/images/right/filetype/unknow-file"
    property string checkIconPath: "qrc:/images/right/uncheck"
    property string fileName: ""
    property string fileURL: ""
    property string fileSize: ""
    property string dlToolsType: ""


    width: parent.width
    height: 60 + trMenu.height

    color: "#3468af"//"#11a8ab"
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
            id: trIcon
            source: iconPath
            anchors {left: parent.left; leftMargin: 15; verticalCenter: parent.verticalCenter}
        }

        Text {
            text: fileName
            color: "#ffffff"
            font.bold: true
            font.pixelSize: 13
            anchors {left: trIcon.right; leftMargin: 13; top: parent.top; topMargin: 17}
        }

        Rectangle {
            width: 300
            height: 20
            clip: true
            color: "#00ffffff"
            anchors {left: trIcon.right; leftMargin: 13; bottom: parent.bottom; bottomMargin: 5}
            Text {
                text: fileURL
                color: "#ffffff"
                font.bold: true
                font.pixelSize: 12
                width: 50
                anchors.fill: parent/* {left: trIcon.right; leftMargin: 13; bottom: parent.bottom; bottomMargin: 13}*/
            }
        }

        Text {
            text: fileSize
            color: "#ffffff"
            font.bold: true
            font.pixelSize: 15
            anchors {right: parent.right; rightMargin: 10; verticalCenter: parent.verticalCenter}
        }

        MouseArea {
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                //console.log(parent.height)
//                trMenu.height = trMenu.height === 0 ? 40:0

                if (trMenu.height == 0)
                    showMenuAnima.start()
                else
                    hideMenuAnima.start()
            }
        }

    }

    // 正在下载的项的菜单
    TrashMenu {
        id: trMenu
        height: 0
        downloadURL: fileURL//for control button
        anchors {bottom: parent.bottom; left: parent.left}

        SequentialAnimation {
            id: showMenuAnima
            NumberAnimation { target: trMenu; property: "height"; to: 40; duration: 250; easing.type: Easing.InOutQuad }
        }
        SequentialAnimation {
            id: hideMenuAnima
            NumberAnimation { target: trMenu; property: "height"; to: 0; duration: 250; easing.type: Easing.InOutQuad }
        }
    }

}
