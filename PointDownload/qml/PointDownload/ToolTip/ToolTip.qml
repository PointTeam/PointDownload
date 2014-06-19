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

Rectangle {
    id: tooltip
    width: tooltipText.width + 10
    height: tipRec.height + triangleImg.height

    property int fadeInDelay
    property int fadeOutDelay
    property alias text: tooltipText.text

    color: "#00ffffff"
    radius: 6
    anchors {bottom: parent.top;bottomMargin: 0; horizontalCenter: parent.horizontalCenter}
    state: ""

    Timer {
        id: outDelayTimer
        interval: 3500;
        running: false;
        onTriggered: {
            tooltip.state = "poppedDown"
        }
    }
    Timer {
        id: inDelayTimer
        interval: 1500;
        running: false;
        onTriggered: {
            tooltip.state = "poppedUp"
        }
    }

    Rectangle {
        id: tipRec
        width: parent.width
        height: tooltipText.height + 10
        color: "black"
        opacity: 0
        radius: 8
        anchors{top: parent.top; horizontalCenter: parent.horizontalCenter}
        Text {
            id: tooltipText
            font.bold: true
            font.pixelSize: 12
            color: "white"
            anchors.centerIn: parent
        }
        Image {
            id: triangleImg
            width: 15
            height: 15
            source: "qrc:/images/main/triangle"
            anchors {top: tooltipText.bottom; horizontalCenter: parent.horizontalCenter}
        }
    }

    // The object travels from an empty state(on creation) to 'poppedUp' state and then to 'poppedDown' state
    states: [
        State {
            name: "poppedUp"
            PropertyChanges { target: tipRec; opacity: 1 }
            PropertyChanges { target: tipRec; scale: 1 }
        },
        State {
            name: "poppedDown"
            PropertyChanges { target: tipRec; opacity: 0 }
            PropertyChanges { target: tipRec; scale: 0.5 }
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "poppedUp"
            PropertyAnimation { target: tipRec; property: "opacity"; duration: tooltip.fadeInDelay}
            PropertyAnimation { target: tipRec; property: "scale"; duration: tooltip.fadeInDelay}
        },

        Transition {
            from: "poppedUp"
            to: "poppedDown"
            PropertyAnimation { target: tipRec; property: "opacity"; duration: tooltip.fadeOutDelay; }
            PropertyAnimation { target: tipRec; property: "scale"; duration: tooltip.fadeOutDelay; }
        }
    ]


    onStateChanged: {
        if (tooltip.state == "poppedDown") {
            tooltip.destroy(tooltip.fadeOutDelay);
            // If you think that the above line is ugly then,
            //you can destroy the element in onOpacityChanged: if (opacity == 0)
        }
    }

    function startTimer()
    {
        inDelayTimer.restart()
        outDelayTimer.restart()
    }
}
