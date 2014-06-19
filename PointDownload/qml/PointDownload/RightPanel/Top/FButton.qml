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
Date:   2014.3.5~
Description:
    这是一个按钮qml文件，在主界面中是用作取消与下载按钮
Others:
Function list:

History:
**********************************************************************/
import QtQuick 2.0

Rectangle {

    id:fButton
    property string imagePath: ""
    property int imageWidth: 28
    property int imageHeigth: 28
    property int recWidth: imageWidth + 5
    property int recHeigth: imageHeigth + 5

    color: "#ffffff"
    width: recWidth
    height: recHeigth

    anchors.verticalCenter: parent.verticalCenter


    Rectangle{
        id:back
        anchors.fill:parent
        anchors {leftMargin: 2;rightMargin: 2;topMargin: 2;bottomMargin: 2}
        radius: 3
        opacity: 0.0;
        border.width: 1
        border.color: "#151d20"

        states: [
        State {
            name: "hover"
            when:topMenuButtonHover.containsMouse
            PropertyChanges {
                target: back
                opacity:0.3
            }
        }
    ]
        transitions : Transition {
            NumberAnimation{
                properties: "opacity"
                duration: 200

            }
        }

    }

    Image {
        id: iconImg
        source: imagePath
        width: imageWidth
        height: imageHeigth
        fillMode: Image.PreserveAspectFit
        //anchors.left: parent.left
        //anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

    }


    MouseArea{
        id: topMenuButtonHover
        hoverEnabled: true;
        anchors.fill:parent
        onClicked: {
            //console.log(iconImg.sourceSize)
        }
    }
}
