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

Image{
    id:innerImg

    property string percentageColor: "#ffffff"    //使用率的颜色
    property real startAngle: Math.PI / 2
    property real percentage: 0
    property string downloadSpeed: "0KB/S"

    property string dragIng: "false"
    property int winx:0
    property int winy:height
    property int oldX: 0
    property int oldY: 0


    x:winx
    y:winy
    source: "qrc:/images/dropzone/tback"

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
            enabled: false
            visible: false
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

    function showButtonTips(buttonTips)
    {
        speedText.enabled = false
        speedText.visible = false

        tipsText.enabled = true
        tipsText.visible = true
        tipsText.text = buttonTips
    }

    function hideButtonTips()
    {

        speedText.enabled = true
        speedText.visible = true

        tipsText.enabled = false
        tipsText.visible = false
        tipsText.text = ""
    }

    function updateSpeedValue(speedValue)
    {
        if (speedValue > 1024)
            downloadSpeed = speedValue / 1024 + "MB/S"
        else
            downloadSpeed = speedValue + "KB/S"
    }

    function updatePercentage()
    {
        innerCanvas.requestPaint()
    }
}
