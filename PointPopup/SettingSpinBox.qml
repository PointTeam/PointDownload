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
import Singleton.DataControler 1.0

Rectangle {
    width: 150
    height: 62
    clip: true

    color: "#f1f1f1"

    //
    Text{
        text:qsTr("Threads:")
        color: "#6d6f6e"
        font.pixelSize: 10
        anchors {left: threadRec.left; bottom: threadRec.top; bottomMargin: 5}
    }
    Rectangle{
        id:threadRec
        width: 40
        height: 25
        border.color: "#c6c4c4"
        border.width: 2
        radius: 3
        anchors {top:parent.top; topMargin: 30; right:parent.horizontalCenter;rightMargin: 20}
        TextInput{
            id:threadInput
            focus: true
            font.pixelSize: 14
            selectByMouse: true
            color: "#6d6f6e"
            selectionColor: "#488bc5"
            text:DataControler.maxThread
            validator: IntValidator { bottom:1; top: 10}
            anchors {horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
            MouseArea{
                anchors {bottom: parent.bottom; horizontalCenter: parent.horizontalCenter}
                height: parent.height / 3
                width: parent.width
                onWheel: {
                    if (wheel.angleDelta.y > 0)
                    {
                        if (threadInput.text*1 < 10)
                            threadInput.text = threadInput.text*1 + 1
                    }
                    else
                    {
                        if (threadInput.text*1 > 1)
                            threadInput.text = threadInput.text*1 - 1
                    }
                }
            }
        }
    }

    //
    Text{
        text:qsTr("Speed:")
        color: "#6d6f6e"
        font.pixelSize: 10
        anchors {left: speedRec.left; bottom: speedRec.top; bottomMargin: 5}
    }
    Rectangle{
        id:speedRec
        width: 40
        height: 25
        border.color: "#c6c4c4"
        border.width: 2
        radius: 3
        anchors {top:parent.top; topMargin: 30; left:parent.horizontalCenter;leftMargin: 20}
        TextInput{
            id:speedInput
            focus: true
            font.pixelSize: 14
            selectByMouse: true
            color: "#6d6f6e"
            selectionColor: "#488bc5"
            text:DataControler.maxSpeed
            validator: IntValidator { bottom:1; top: 10000}
            anchors {horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
            MouseArea{
                anchors {bottom: parent.bottom; horizontalCenter: parent.horizontalCenter}
                height: parent.height / 3
                width: parent.width
                onWheel: {
                    if (wheel.angleDelta.y > 0)
                    {
                        if (speedInput.text*1 < 10000)
                            speedInput.text = speedInput.text*1 + 100
                    }
                    else
                    {
                        if (speedInput.text*1 > 100)
                            speedInput.text = speedInput.text*1 - 100
                        else if (speedInput.text*1 <= 100 && speedInput.text*1 > 1)
                            speedInput.text = speedInput.text*1 - 1
                    }
                }
            }
        }
    }

//    }

    function getThreadCount()
    {
        return threadInput.text
    }

    function getSpeed()
    {
        return speedInput.text
    }
}
