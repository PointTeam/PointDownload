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
    直方图面板，这其中包含一个星期的流量使用情况直方图
Others:
Function list:

History:
**********************************************************************/

import QtQuick 2.0
import Singleton.MiddleSender 1.0

Rectangle {
    id: histogramPanel

    property real usageHeight1: 0
    property real usageHeight2: 0
    property real usageHeight3: 0
    property real usageHeight4: 0
    property real usageHeight5: 0
    property real usageHeight6: 0
    property real usageHeight7: 0

    property int   textSpace: 2
    property int fontSize: 12
    property string fontFamily: "URW Bookman L"


    width: 230
    height: 100
    color: "#ecf2f6"

    Connections{
        target:MiddleSender
        onSendDataListChange: {
            usageHeight1 = getValueFromDataList(0);
            usageHeight2 = getValueFromDataList(1);
            usageHeight3 = getValueFromDataList(2);
            usageHeight4 = getValueFromDataList(3);
            usageHeight5 = getValueFromDataList(4);
            usageHeight6 = getValueFromDataList(5);
            usageHeight7 = getValueFromDataList(6);
        }
    }

    Rectangle {
        id: textRec

        height: parent.height
        width: 20
        color: "#ecf2f6"
        anchors {left: parent.left; bottom: parent.bottom;bottomMargin: 10}

        Text {
            id: usageText10
            text: "10"
            font.family: fontFamily
            font.pixelSize: fontSize
            color: "#8a95a5"
            anchors {top: parent.top; horizontalCenter: parent.horizontalCenter}
        }

        Text {
            id: usageText8
            text: "8"
            font.family: fontFamily
            font.pixelSize: fontSize
            color: "#8a95a5"
            anchors {top: usageText10.bottom;topMargin: textSpace; horizontalCenter: parent.horizontalCenter}
        }

        Text {
            id: usageText6
            text: "6"
            font.family: fontFamily
            font.pixelSize: fontSize
            color: "#8a95a5"
            anchors {top: usageText8.bottom;topMargin: textSpace; horizontalCenter: parent.horizontalCenter}
        }

        Text {
            id: usageText4
            text: "4"
            font.family: fontFamily
            font.pixelSize: fontSize
            color: "#8a95a5"
            anchors {top: usageText6.bottom;topMargin: textSpace; horizontalCenter: parent.horizontalCenter}
        }

        Text {
            id: usageText2
            text: "2"
            font.family: fontFamily
            font.pixelSize: fontSize
            color: "#8a95a5"
            anchors {top: usageText4.bottom;topMargin: textSpace; horizontalCenter: parent.horizontalCenter}
        }

        Text {
            id: usageText0
            text: "0"
            font.family: fontFamily
            font.pixelSize: fontSize
            color: "#8a95a5"
            anchors {top: usageText2.bottom;topMargin: textSpace; horizontalCenter: parent.horizontalCenter}
        }
    }

    HistogramRectangle {
        id: hisRec1
        height: textRec.height + 25
        usageHeight: usageHeight1
        recBottomTitle: qsTr("Mon")//"一"//
        anchors {left: textRec.right; leftMargin: 5; top: textRec.top}
    }

    HistogramRectangle {
        id: hisRec2
        height: textRec.height + 25
        usageHeight: usageHeight2
        recBottomTitle: qsTr("Tue")//"二"//
        anchors {left: hisRec1.right; leftMargin: 11; top: textRec.top}
    }
    HistogramRectangle {
        id: hisRec3
        height: textRec.height + 25
        usageHeight: usageHeight3
        recBottomTitle: qsTr("Wed")//"三"//
        anchors {left: hisRec2.right; leftMargin: 11; top: textRec.top}
    }
    HistogramRectangle {
        id: hisRec4
        height: textRec.height + 25
        usageHeight: usageHeight4
        recBottomTitle: qsTr("Thu")//"四"//
        anchors {left: hisRec3.right; leftMargin: 11; top: textRec.top}
    }
    HistogramRectangle {
        id: hisRec5
        height: textRec.height + 25
        usageHeight: usageHeight5
        recBottomTitle: qsTr("Fri")//"五"//
        anchors {left: hisRec4.right; leftMargin: 11; top: textRec.top}
    }
    HistogramRectangle {
        id: hisRec6
        height: textRec.height + 25
        usageHeight: usageHeight6
        recBottomTitle: qsTr("Sat")//"六"//
        anchors {left: hisRec5.right; leftMargin: 11; top: textRec.top}
    }
    HistogramRectangle {
        id: hisRec7
        height: textRec.height + 25
        usageHeight: usageHeight7
        recBottomTitle: qsTr("Sun")//"日"//
        anchors {left: hisRec6.right; leftMargin: 11; top: textRec.top}
    }

    function getValueFromDataList(index)
    {
        var infoArry = MiddleSender.dataList.split("#");
        if (index >= 0 && index <= 6)
        {
            return (infoArry[index] / (1024 * 1024 * 1024)) * (textRec.height + 25) / 10
        }
    }
}
