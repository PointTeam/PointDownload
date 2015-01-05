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

import QtQuick 2.0
import QtQuick.Controls.Styles 1.1
import QtQuick.Controls 1.1
import settingControler 1.0

Rectangle {
    id: sliderWin
    width: 185
    height: 30

    property string winType//ThreadCount,MaxJobCount,MaxDSpeed,DSPath
    property int fadeInDelay
    property int fadeOutDelay
    property real maxCount
    property real miniCount
    property real sliderStep
    property real currentVlaue
    property string grooveColor
    property string showed: "true"


    color: "#4a565f"
    radius: 8
    opacity: 0
    anchors {left:parent.right; leftMargin: 180;verticalCenter: parent.verticalCenter}
    state: ""

    SettingControler{
        id:settingCtrl;
    }

    Slider {
        id:valueSlide
        maximumValue: maxCount
        minimumValue: minimumValue
        stepSize: sliderStep
        value: currentVlaue

        anchors {left: parent.left; leftMargin: 8;verticalCenter: parent.verticalCenter}
        style: SliderStyle {
            groove: Rectangle {
                implicitWidth: 100
                implicitHeight: 6
                color: sliderWin.grooveColor
                radius: 5
            }
            handle: Rectangle {
                anchors.centerIn: parent
                color: control.pressed ? "white" : "lightgray"
                width: 15
                height: 13
                radius: 5
            }
        }
        onValueChanged: {
            valueText.text = value.toString()
        }
    }

    Rectangle{
        id:valueRec
        width: 40
        height: 20
        color: "#3b424a"
        radius: 8
        anchors {left:valueSlide.right; leftMargin: 6;verticalCenter: parent.verticalCenter}
        TextInput{
            id: valueText
            validator: IntValidator { bottom:miniCount; top: maxCount}

            text:currentVlaue
            selectByMouse: true
            selectionColor: "#545454"
            font.pixelSize: 10
            color: "#ffffff"
            anchors.centerIn: parent
            onTextChanged: {
                valueSlide.value = valueText.text == "0" ? "0":valueText.text
            }
        }
    }

    Rectangle {
        id: splitLine
        width: 2
        height: parent.height
        color: "#333333"
        anchors {left: valueRec.right; leftMargin: 3; verticalCenter: parent.verticalCenter}
    }

    Image {
        source: "qrc:/images/setting/Close"
        anchors {right: parent.right; rightMargin: 5; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            onClicked: {
                updateValue();
                sliderWin.showed = "false"
                sliderWin.state = "poppedDown"
            }
        }
    }

    // The object travels from an empty state(on creation) to 'poppedUp' state and then to 'poppedDown' state
    states: [
        State {
            name: "poppedUp"
            PropertyChanges { target: sliderWin; opacity: 1 }
            PropertyChanges { target: sliderWin; scale: 1 }
        },
        State {
            name: "poppedDown"
            PropertyChanges { target: sliderWin; opacity: 0 }
            PropertyChanges { target: sliderWin; scale: 0.5 }
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "poppedUp"
            PropertyAnimation { target: sliderWin; property: "opacity"; duration: sliderWin.fadeInDelay}
            PropertyAnimation { target: sliderWin; property: "scale"; duration: sliderWin.fadeInDelay}
        },

        Transition {
            from: "poppedUp"
            to: "poppedDown"
            PropertyAnimation { target: sliderWin; property: "opacity"; duration: sliderWin.fadeOutDelay; }
            PropertyAnimation { target: sliderWin; property: "scale"; duration: sliderWin.fadeOutDelay; }
        }
    ]


    onStateChanged: {
        if (sliderWin.state === "poppedDown") {
            sliderWin.destroy(sliderWin.fadeOutDelay);
            // If you think that the above line is ugly then,
            //you can destroy the element in onOpacityChanged: if (opacity == 0)
        }
    }

    function updateValue()
    {

        if (winType == "ThreadCount")
            settingCtrl.defaultThreadCount = valueSlide.value.toString()
        else if (winType == "MaxJobCount")
            settingCtrl.maxJobCount = valueSlide.value.toString()
        else if (winType == "MaxDSpeed")
            settingCtrl.maxDownloadSpeed = valueSlide.value.toString()
    }

}
