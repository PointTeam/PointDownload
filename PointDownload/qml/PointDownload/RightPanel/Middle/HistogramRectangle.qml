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
/*******************************************************************
Date:   2014.3.20~
Description:
    单个直方图组件，被HistogramPanel使用，使用率使用usageHeight计算得出
Others:
Function list:

History:
**********************************************************************/

import QtQuick 2.0

Rectangle {

    id: histogramRectangle

    property string recBottomTitle: ""
    property real usageHeight: 0

    width: 15
    height: 120
    color: "#ecf2f6"

    Rectangle {
        id: baseHisRec
        width: parent.width
        height: parent.height - recBottomText.height
        color: "#d9e4eb"
        radius: 3
        anchors {top: parent.top; bottom: recBottomText.top;bottomMargin: 5; horizontalCenter: parent.horizontalCenter}
    }

    Rectangle {
        id: percentageRec
        width: baseHisRec.width
        height: usageHeight < baseHisRec.height ? usageHeight: baseHisRec.height
        radius: 3
        color: "#37a8af"
        anchors {bottom: baseHisRec.bottom; horizontalCenter: baseHisRec.horizontalCenter}
    }

    Text {
        id: recBottomText
        text:recBottomTitle
        height: 4
        color: "#596679"
        font.bold: true
        font.family: "URW Bookman L"
        font.pixelSize: 10
        anchors {bottom: parent.bottom; horizontalCenter: parent.horizontalCenter}
    }
}
