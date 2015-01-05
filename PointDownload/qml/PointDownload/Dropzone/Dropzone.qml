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

import QtQuick 2.1
import QtQuick.Window 2.1
import QtGraphicalEffects 1.0
import Singleton.PEventFilter 1.0
import Singleton.TopContrl 1.0
import Singleton.MiddleSender 1.0
import Singleton.DropzoneSettingControler 1.0

import "InnerCircle"
import "OuterCircle"

Window {
    id:dropzonePage
    flags: Qt.WindowStaysOnTopHint |Qt.FramelessWindowHint | Qt.ToolTip

    color: "#00000000"
    width: 135
    height: 135
    opacity: DropzoneSettingControler.opacity/10

    property bool dragIng: false
    property int winx:DropzoneSettingControler.winX
    property int winy:DropzoneSettingControler.winY
    property int oldWinx: 0
    property int oldWiny:0
    property int oldX: 0
    property int oldY: 0

    x:winx
    y:winy

    Timer{
        id:updateTimer
        interval: (MiddleSender.totalProgress>0 && MiddleSender.totalProgress < 1)?20 / MiddleSender.totalProgress : 1000
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: {
            if (interval < 30)
                innerMainCircle.startAngle += 0.05
            else if(interval < 60)
                innerMainCircle.startAngle += 0.03
            else
                innerMainCircle.startAngle += 0.01

            innerMainCircle.updatePercentage()
        }
    }

    Connections {
        target: MiddleSender
        onSendTotalProgressChange: {
            if (MiddleSender.totalProgress === 1)
            {
                innerMainCircle.percentageColor = "#1b9ad6"
                innerMainCircle.updatePercentage()
            }
            else
                innerMainCircle.percentageColor = "#ffffff"

            innerMainCircle.percentage = MiddleSender.totalProgress * 100
        }

        onSendDownSpeedChange: {
            innerMainCircle.updateSpeedValue(MiddleSender.downSpeed)
        }
    }


    Item{
        id:mainViewItem
        width: parent.width
        height: parent.height


        OuterMainCircle{
            id:outerCircle
            width: 142
            height: 142
            anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
            onMenuButtonHover: {
                if (buttonTips == "")
                    innerMainCircle.hideButtonTips()
                else
                    innerMainCircle.showButtonTips(buttonTips)
            }
        }

        InnerMainCircle{
            id:innerMainCircle
            width: 70
            height: 70
            anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
            onSNewJobCountChange:{
                if (count > 0)
                {
                    normalInfo.angle = 0;
                    innerMainCircle.visible = true
                    iconRota.angle = 180;
                    iconShadowItem.visible = false
                }
                else
                {
                    normalInfo.angle = 180
                    innerMainCircle.visible = false
                    iconRota.angle = 0;
                    iconShadowItem.visible = true
                }
            }

            transform: Rotation {
                id:normalInfo
                origin.x: innerMainCircle.width / 2;
                origin.y: innerMainCircle.width / 2;
                axis { x: 0; y: 1; z: 0 }
                Behavior on angle {  // for animation
                    NumberAnimation { duration: 700;easing.type : Easing.InOutBack }
                }
            }
        }

        Rectangle{
            id:iconShadowItem
            width: 70
            height: 70
            radius: 70
            color:"#1b9ad6"
            anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}

            Text{
                text: qsTr("Point")
                width: parent.width
                height: parent.height
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "#ffffff"
                font.pixelSize: 15
                font.bold: true
                anchors.centerIn: parent
            }

            transform: Rotation {
                id:iconRota
                origin.x: innerMainCircle.width / 2;
                origin.y: innerMainCircle.width / 2;
                axis { x: 0; y: 1; z: 0 }
                Behavior on angle {  // for animation
                    NumberAnimation { duration: 700;easing.type : Easing.InOutBack }
                }
            }
        }

        MouseArea{
            id:mArea
            anchors {verticalCenter: mainViewItem.verticalCenter; horizontalCenter: mainViewItem.horizontalCenter}
            width: parent.width / 3
            height: parent.height / 3
            hoverEnabled: true

            onPressed:  {
                oldX = mouseX + parent.width / 3;
                oldY = mouseY + parent.width / 3;
                oldWinx = winx; oldWiny = winy
                dragIng = true

            }
            onReleased: {
                dragIng = false
                mArea.cursorShape=Qt.ArrowCursor
            }

            onPositionChanged: {
                if (dragIng)
                {
                    mArea.cursorShape=Qt.DragMoveCursor
                    winx = PEventFilter.globalX- oldX
                    winy = PEventFilter.globalY - oldY;

                    DropzoneSettingControler.winX = winx
                    DropzoneSettingControler.winY = winy
                }
            }

            onClicked: {
                if (oldWinx == winx && oldWiny == winy)
                    outerCircle.updateMenuState()
            }

            onDoubleClicked: {
                TopContrl.showMainWindow()
                TopContrl.updateShowState(true)
                outerCircle.updateMenuState()
                dropzonePage.close()
            }
        }
    }

    //阴影必须在所有组件之后才会在最底层
    DropShadow {
        anchors.fill: mainViewItem
        horizontalOffset: 1
        verticalOffset: 2
        radius: 2.0
        samples: 16
        fast: true
        color: "#1d2833"
        source: mainViewItem
    }
}
