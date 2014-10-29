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
Date:   2014.3.20~
Description:
    这是一个蓝色背景的按钮，当鼠标经过的时候背景会变成蓝色，被TopPanel使用
Others:
Function list:

History:
**********************************************************************/

import QtQuick 2.0

Rectangle {

    id:blueButton
    property string imagePath: ""
    property int imageWidth: 20
    property int imageHeigth: 20

    color: "#ffffff"
    width: 40
    height: 40

    signal sBlueButtonClick();

    Image {
        id: iconImg
        source: imagePath
        width: imageWidth
        height: imageHeigth
        fillMode: Image.PreserveAspectFit
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

    }


    MouseArea{
        id: topMenuButtonHover
        hoverEnabled: true;
        anchors.fill:parent
        onEntered: color = "#15a4fa"
        onExited: color = "#ffffff"
        onClicked: blueButton.sBlueButtonClick()
    }
}
