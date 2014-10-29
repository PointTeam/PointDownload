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
import Singleton.PEventFilter 1.0
import Singleton.DropzoneSettingControler 1.0

Item{
    id:innerViewItem
//    source: "qrc:/images/dropzone/tback"

    property string percentageColor: "#ffffff"    //使用率的颜色
    property real startAngle: Math.PI / 2
    property real percentage: 0
    property string downloadSpeed: "0KB/S"
    property int jobCount:0
    property real storageUsage: 0

    property string dragIng: "false"
    property int winx:0
    property int winy:height
    property int oldX: 0
    property int oldY: 0
    property int stateIndex:0
    property real animationDuration: 700

    x:winx
    y:winy

    signal sNewJobCountChange(int count)

    Connections{
        target: DropzoneSettingControler
        onSNewJobCount:{
            jobCount = newCount
            innerViewItem.sNewJobCountChange(jobCount)
        }
        onSNewStorageUsage:{
            storageUsage = newUsage
        }
    }

    Timer{
        id:updateTimer
        interval:DropzoneSettingControler.infoInterval
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: {
            if (stateIndex >= states.length)
                stateIndex = 0
            if (!DropzoneSettingControler.showStorageUsage && states[stateIndex].name === "showStorageUsage")
            {
                //如果不显示存储信息，则直接跳过
                stateIndex ++;
            }

            if (!DropzoneSettingControler.showJobCount && states[stateIndex].name === "showJobCount")
            {
                stateIndex ++;
            }
            if (stateIndex >= states.length)
                stateIndex = 0

            innerViewItem.state = states[stateIndex].name
            stateIndex ++
        }
    }

    Rectangle{
        id:innerRec
        width: parent.width
        height: parent.height
        radius: parent.width
        color:"#1b9ad6"

        anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}

        Text{
            id:speedText
            text: downloadSpeed
            font.family: "Cantarell"
            font.bold: true
            width: parent.width
            height: parent.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 11
            color: "#ffffff"
            anchors {horizontalCenter: innerRec.horizontalCenter;verticalCenter: innerRec.verticalCenter}
        }
        Text{
            id:tipsText
            text: ""
            font.family: "Cantarell"
            font.bold: true
            width: parent.width
            height: parent.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "#ffffff"
            font.pixelSize: 11
            anchors {horizontalCenter: innerRec.horizontalCenter;verticalCenter: innerRec.verticalCenter}
        }
        Text{
            id:storageUsageText
            text: qsTr("Disk: ") + storageUsage + "%"
            font.family: "Cantarell"
            font.bold: true
            width: parent.width
            height: parent.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "#ffffff"
            font.pixelSize: 11
            anchors {horizontalCenter: innerRec.horizontalCenter;verticalCenter: innerRec.verticalCenter}
        }
        Text{
            id:jobCountText
            text: qsTr("Task: ") + jobCount
            font.family: "Cantarell"
            font.bold: true
            width: parent.width
            height: parent.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "#ffffff"
            font.pixelSize: 11
            anchors {horizontalCenter: innerRec.horizontalCenter;verticalCenter: innerRec.verticalCenter}
        }

        //进度环画布
        Canvas {
            id: innerCanvas
            width: parent.width
            height: parent.height

            anchors {
                left:parent.left;/*leftMargin: 5*/
                top: parent.top;/*topMargin: 5*/}

            onPaint:{
                //percentage = percentage + 1;

                var ctx = innerCanvas.getContext('2d');
                ctx.clearRect(0,0,100,100);
                ctx.strokeStyle = percentageColor;
                ctx.lineWidth = 3;
                ctx.beginPath();
                // 根据percentage的值画出不同长度的圆弧
                //注意圆的方向是顺时针，所以90度角在下方
                ctx.arc(35,35, 32.9,  startAngle, 2 * Math.PI * percentage / 100 + startAngle, false);
                ctx.stroke();
            }
        }

    }

    states:[
        State {
            name: "showSpeed"
            PropertyChanges {target: speedText; opacity:1}
            PropertyChanges {target: storageUsageText; opacity:0}
            PropertyChanges {target: jobCountText; opacity:0}
        },
        State{
            name: "showStorageUsage"
            PropertyChanges {target: speedText; opacity:0}
            PropertyChanges {target: storageUsageText; opacity:1}
            PropertyChanges {target: jobCountText; opacity:0}
        },
        State{
            name: "showJobCount"
            PropertyChanges {target: speedText; opacity:0}
            PropertyChanges {target: storageUsageText; opacity:0}
            PropertyChanges {target: jobCountText; opacity:1}
        }
    ]

    State{
        name: "showTip"
        PropertyChanges {target: speedText; opacity:0}
        PropertyChanges {target: storageUsageText; opacity:0}
        PropertyChanges {target: jobCountText; opacity:0}
    }

    transitions: [
        Transition {
            from: ""
            to: ""
            NumberAnimation { target: speedText; property: "opacity"; duration: animationDuration;easing.type: Easing.InOutBack}
            NumberAnimation { target: storageUsageText; property: "opacity"; duration: animationDuration;easing.type: Easing.InOutBack}
            NumberAnimation { target: jobCountText; property: "opacity"; duration: animationDuration;easing.type: Easing.InOutBack}
            NumberAnimation { target: tipsText; property: "opacity"; duration: animationDuration;easing.type: Easing.InOutBack}
        }
    ]

    function showButtonTips(buttonTips)
    {
        updateTimer.stop()
        speedText.visible = false
        storageUsageText.visible = false
        jobCountText.visible = false
        tipsText.visible = true
        tipsText.text = buttonTips
    }

    function hideButtonTips()
    {
        updateTimer.start()
        speedText.visible = true
        storageUsageText.visible = true
        jobCountText.visible = true
        tipsText.visible = false
    }

    function updateSpeedValue(speedValue)
    {
        if (speedValue > 1024)
            downloadSpeed = (speedValue / 1024).toFixed(1) + "MB/S"
        else
            downloadSpeed = (speedValue).toFixed(1) + "KB/S"
    }

    function updatePercentage()
    {
        innerCanvas.requestPaint()
    }
}
