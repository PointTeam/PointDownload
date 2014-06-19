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
/**********************************************************************************
Date:   2014.3.5~
Description:
    主界面中的中间菜单导航按钮（文件信息，下载设置，帮助）
Others:
Function list:

History:
***********************************************************************************/
import QtQuick 2.0

Rectangle {

    id: nvigationButton

    property string buttonText: ""
    property string jobCount: "0"
    property string buttonColor: "#08334b"
    property string fontColor: "#a0acbf"
    property string iconSource: ""
    property int buttonHeigth: parent.height

    height: parent.height
    width: parent.width
    color: buttonColor

    Image {
        id: buttonIcon
        source: iconSource
        width: 16
        height: 16
        anchors {verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 8}
    }

    Text {
        id: bText
        text: buttonText
        font.bold: true
        font.pixelSize: 12
        font.family: "ProFont"
        color: fontColor
        anchors {verticalCenter: parent.verticalCenter; left:buttonIcon.right; leftMargin: 4}
    }
    Rectangle {
        anchors {right: parent.right;rightMargin: 15; verticalCenter: parent.verticalCenter}
        height: 15
        width: 15
        radius: 5
        color: "#011825"
        opacity: 0.7
        Text{
            id: countText
            anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
            text: jobCount
            font.bold: true
            font.pixelSize: 8
            color: "#ffffff"
        }
    }

}
