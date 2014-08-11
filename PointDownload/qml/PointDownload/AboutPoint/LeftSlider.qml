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
    id:leftSlider
    width: 80
    height: parent.height
    color:"#323355"

    property int imageSmallSize: 30
    property int imgBigSize: 60
    property int fontSmallSize: 5
    property int fontBigSize: 10

    state: "softwareGetMouse"

    Image{
        id:aboutSoftware
        source:"qrc:/images/aboutpoint/button"
        width: imageSmallSize
        height: imageSmallSize
        anchors {top: parent.top;topMargin: 20;horizontalCenter: parent.horizontalCenter}

        Text{
            id:softwareTitle
            text:qsTr("SoftWare")
            visible: false
            font.bold: true
            font.pixelSize: fontSmallSize
            color: "#ffffff"
            anchors {horizontalCenter: parent.horizontalCenter;verticalCenter: parent.verticalCenter}
        }
        MouseArea{
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                leftSlider.state = "softwareGetMouse"
                rightView.setCurrentPage(0)
            }
        }
    }
    Image{
        id:aboutUs
        source:"qrc:/images/aboutpoint/button"
        width: imageSmallSize
        height: imageSmallSize
        anchors {top: aboutSoftware.top;topMargin: parent.height / 3;horizontalCenter: parent.horizontalCenter}
        Text{
            id:aboutTitle
            text:qsTr("About Us")
            visible: false
            font.bold: true
            font.pixelSize: fontSmallSize
            color: "#ffffff"
            anchors {horizontalCenter: parent.horizontalCenter;verticalCenter: parent.verticalCenter}
        }
        MouseArea{
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                leftSlider.state = "aboutGetMouse"
                rightView.setCurrentPage(1)
            }
        }
    }
    Image{
        id:helpUs
        source:"qrc:/images/aboutpoint/button"
        width: imageSmallSize
        height: imageSmallSize
        anchors {top: aboutUs.top;topMargin: parent.height / 3;horizontalCenter: parent.horizontalCenter}
        Text{
            id:helpUsTitle
            text:qsTr("Help Us")
            visible: false
            font.bold: true
            font.pixelSize: fontSmallSize
            color: "#ffffff"
            anchors {horizontalCenter: parent.horizontalCenter;verticalCenter: parent.verticalCenter}
        }
        MouseArea{
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                leftSlider.state = "helpUsGetMouse"
                rightView.setCurrentPage(2)
            }
        }
    }

    states:[
        State{
            name:"softwareGetMouse"
            PropertyChanges {target: aboutSoftware;width:60;height:60}
            PropertyChanges{target:softwareTitle;visible:true;font.pixelSize: 10}
        },
        State{
            name:"aboutGetMouse"
            PropertyChanges {target: aboutUs;width:60;height:60}
            PropertyChanges{target:aboutTitle;visible:true;font.pixelSize: 10}
        },
        State{
            name:"helpUsGetMouse"
            PropertyChanges {target: helpUs;width:60;height:60}
            PropertyChanges{target:helpUsTitle;visible:true;font.pixelSize: 10}
        }
    ]

    transitions:[
        Transition {
            from: "*";to: "*"
            PropertyAnimation {properties: "width"; duration: 200;easing.type: Easing.OutBack}
            PropertyAnimation {properties: "height"; duration: 200;easing.type: Easing.OutBack}
//            PropertyAnimation {properties: "font.pixelSize"; duration: 200}
        }
    ]
}
