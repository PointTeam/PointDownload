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

import QtQuick 2.1
import QtQuick.Window 2.1

Window {
    id:aboutMainPage
    flags: Qt.FramelessWindowHint
    visible: true
    width: 500
    height: 350
    x:(Screen.width - width) / 2
    y:(Screen.height - height) / 2

    Rectangle{
        id:mainWin
        color: "#323355"
        width: parent.width
        height: parent.height

        LeftSlider{
            id:leftSlider
            anchors {left:parent.left;top:parent.top}
        }

        RightView{
            id:rightView
            anchors {left: leftSlider.right}
            width: 400
            height: 350
        }

        Image{
            id:closeImg
            visible: false
            source:"qrc:/images/aboutpoint/quit"
            anchors { top: parent.top; right:parent.right}

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: parent.visible = true
                onExited: parent.visible = false
                onClicked: aboutMainPage.destroy()
            }
        }

        MouseArea{
            anchors {top: parent.top;right:parent.right;rightMargin: closeImg.width}
             height: 20
             width: 500
            hoverEnabled: true
            onEntered: closeImg.visible = true
            onExited: closeImg.visible = false
        }
    }

}
