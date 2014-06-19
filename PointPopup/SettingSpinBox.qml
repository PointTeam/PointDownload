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
import QtQuick.Controls.Styles 1.1
import QtQuick.Controls 1.0
import Singleton.DataControler 1.0

Rectangle {
    width: 100
    height: 62

    color: "#f1f1f1"

    //
    Text{
        text:qsTr("Threads:")
        color: "#6d6f6e"
        font.pixelSize: 10
        anchors {left: boxThread.left; bottom: boxThread.top; bottomMargin: 3}
    }
    SpinBox{
        id:boxThread
        decimals: 0
        value: DataControler.maxThread
        maximumValue: 10
        minimumValue: 1
        stepSize: 1
        width: 60
        height: 27
        anchors {top:parent.top; topMargin: 30; right:parent.horizontalCenter;rightMargin: 25}
        style: SpinBoxStyle{
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 20
                border.color: "gray"
                radius: 3
            }
            textColor: "#6d6f6e"
            selectedTextColor: "#ffffff"
            selectionColor: "#59add4"
        }
        font.pixelSize: 13
    }

    //
    Text{
        text:qsTr("Speed:")
        color: "#6d6f6e"
        font.pixelSize: 10
        anchors {left: boxSpeed.left; bottom: boxSpeed.top; bottomMargin: 3}
    }
    SpinBox{
        id:boxSpeed
        decimals: 0
        value: DataControler.maxSpeed
        maximumValue: 10000
        minimumValue: 0
        stepSize: 10
        width: 60
        height: 27
        anchors {top:parent.top; topMargin: 30; left:parent.horizontalCenter;leftMargin: 25}
        style: SpinBoxStyle{
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 20
                border.color: "gray"
                radius: 3
            }
            textColor: "#6d6f6e"
            selectedTextColor: "#ffffff"
            selectionColor: "#59add4"
        }
        font.pixelSize: 13

    }

    function getThreadCount()
    {
        return boxThread.value
    }

    function getSpeed()
    {
        return boxSpeed.value
    }
}
