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
    中间面板，包括三个表示使用率的圆圈，一个流量统计直方图，被RightListView
    使用
Others:

History:
**********************************************************************/

import QtQuick 2.0
import middleSender 1.0

Rectangle {
    id: middlePanel
    width: parent.width
    height: 190
    color: "#ecf2f6"
    state: "middleShow"

    property real testHeight: 0

    MiddleSender {
        id: middleSend
        onSendCpuUsageChange: {
            cpuCircle.percentage = middleSend.cpuUsage;
            cpuCircle.updatePercentage();
        }
        onSendDiskUsageChange: {
            diskCircle.percentage = middleSend.diskUsage;
            diskCircle.updatePercentage();
        }
        onSendDownSpeedChange: {
            netCircle.percentage = 100 * middleSend.downSpeed / (middleSend.downSpeed + middleSend.upSpeed);
            netCircle.updatePercentage();
        }
    }

    //cpu使用率圈
    InfoCircle {
        id: cpuCircle
        ///theRadius: 80
        mainTitle: middleSend.cpuUsage + "%"
        subTitle: "CPU USAGE"
        anchors {top:parent.top; topMargin: 20; left: parent.left; leftMargin: 18}
    }

    //网速圈
    InfoCircle {
        id: netCircle
        ///theRadius: 80
        percentageColor: "#15a4fa"
        mainTitle: middleSend.downSpeed
        subTitle: "NET SPEED"
        anchors {top:parent.top; topMargin: 20;left: cpuCircle.right; leftMargin: 18}
    }

    //磁盘使用率圈
    InfoCircle {
        id: diskCircle
        ///theRadius: 80
        percentageColor: "#ae69af"
        mainTitle: middleSend.diskUsage + "%"
        subTitle: "DISK USAGE"
        anchors {top:parent.top; topMargin: 20;left: netCircle.right; leftMargin: 18}
    }

    //在三个圆圈下的标题
    Rectangle {
        id: circleTitleRec
        width: 120
        height: 28
        radius: 15
        color: "#d1d8e2"
        anchors {horizontalCenter: netCircle.horizontalCenter; top: netCircle.bottom; topMargin: 25}

        Rectangle {
            id: insideWriteRec
            width: parent.width - 4
            height: parent.height - 4
            radius: 15
            color: "#ffffff"
            anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
        }

        Text {
            id: circleTitleText
            text: "SYSTEM . USAGE"
            font.family: "URW Bookman L"
            font.pixelSize: 11
            color: "#596379"
            font.bold: true
            anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
        }
    }

    //直方图
    HistogramPanel {
        id: rightHistogramPanel
        height: 80
        anchors {right: parent.right;rightMargin: 30; top:parent.top; topMargin: 35}
//        MouseArea {
//            anchors.fill: parent
//            onClicked: {
//                testHeight += 5;
//                rightHistogramPanel.usageHeight1 = testHeight;
//            }
//        }
    }
    //直方图标题
    Rectangle {
        id: hisTitleRec
        width: 120
        height: 28
        radius: 15
        color: "#d1d8e2"
        anchors {horizontalCenter: rightHistogramPanel.horizontalCenter; top: rightHistogramPanel.bottom; topMargin: 30}

        Rectangle {
            id: insideWriteRec2
            width: parent.width - 4
            height: parent.height - 4
            radius: 15
            color: "#ffffff"
            anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
        }

        Text {
            id: circleTitleText2
            text: "DATA{GB} / DATE"
            font.family: "URW Bookman L"
            font.pixelSize: 11
            color: "#596379"
            font.bold: true
            anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
        }
    }

    //中部部件与下部部件之间的分割线
    Rectangle {
        id: middleSplitLine
        width: parent.width
        height: 2
        anchors {bottom: parent.bottom; horizontalCenter: parent.horizontalCenter}
        color: "#ecf2f6"

        Rectangle {
            id: leftSplitRec
            width: (parent.width - 100) / 2
            height: 2
            anchors {verticalCenter: parent.verticalCenter; right: arrowImg.left; rightMargin: 10}
            color: "#d2dae2"
        }

        Image {
            id: arrowImg
            source: "qrc:/images/navigation/downarrow"
            anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}

            MouseArea {
                id: arrowMouse
                anchors.fill: parent
                onClicked: {
                    if (middlePanel.state == "middleHide")
                        middlePanel.state = "middleShow";
                    else
                        middlePanel.state = "middleHide"
                }
            }
        }
        Rectangle {
            id: rightSplitRec
            width: (parent.width - 100) / 2
            height: 2
            anchors {verticalCenter: parent.verticalCenter; left: arrowImg.right; leftMargin: 10}
            color: "#d2dae2"
        }
    }

    states:[
        State{
            name: "middleHide"
            PropertyChanges {target: arrowImg; rotation: 180}
            PropertyChanges {target: middlePanel; y: topMenu.height - middlePanel.height}
            PropertyChanges {target: cpuCircle; visible:false}
            PropertyChanges {target: netCircle; visible:false}
            PropertyChanges {target: diskCircle; visible:false}
            PropertyChanges {target: circleTitleRec; visible:false}
            PropertyChanges {target: rightHistogramPanel;visible: false}
            PropertyChanges {target: hisTitleRec;visible: false}
            PropertyChanges {target: middlePanel; height: middleSplitLine.height}
        },
        State{
            name: "middleShow"
            PropertyChanges {target: arrowImg; rotation: 0}
            PropertyChanges {target: middlePanel; y: topMenu.height}
        }

    ]

    transitions: [
        Transition {
            from: "*";to: "*"
            PropertyAnimation {
                properties: "y"; duration: 700
                easing.type: "OutBounce"
            }
            PropertyAnimation {
                properties: "height";duration: 200
                //easing.type: "OutBounce"
            }
            PropertyAnimation {
                properties: "visible";duration: 100
            }
        }
    ]
}
