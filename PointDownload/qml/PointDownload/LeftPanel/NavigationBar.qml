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
/****************************************************************************************
Date:   2014.3.5~
Description:
    包含NavigationButton的整个导航条
Others:
Function list:

History:
*****************************************************************************************/
import QtQuick 2.0

import "../RightPanel"

Rectangle {

    id: navigationBar

    property int buttonSpacing: 5

    color: "#08334b"
    state: "downloadingGetMouse"   //default state

//    NavigationButton {
//        id: searchButton
//        buttonText: "资源搜索"
//        height: 30
//        iconSource: "qrc:/images/navigation/home-g"
//        anchors {left:parent.left;top:parent.top; topMargin: buttonSpacing}

//        MouseArea {
//            id: searchMouse
//            anchors.fill: parent
//            onClicked: {
//                rightPanel.setDownloadListPage(0)
//                navigationBar.state = "searchGetMouse"

//            }
//        }
//    }
    Timer {
        interval: 1000;
        running: true;
        repeat: true
        onTriggered:{
            downloadingButton.jobCount = rightPanel.getDownloadListCount("Downloading")
            downloadedButton.jobCount = rightPanel.getDownloadListCount("Downloaded")
            downloadTrashButton.jobCount = rightPanel.getDownloadListCount("DownloadTrash")
        }
    }

    NavigationButton {
        id: downloadingButton
        buttonText: qsTr("Task")//"正在下载"//
        height: 30
        iconSource: "qrc:/images/navigation/downloading-g"
        anchors {left:parent.left; top: parent.top; topMargin: buttonSpacing}

        MouseArea {
            id: downloadingMouse
            anchors.fill: parent
            onClicked: {
                rightPanel.setCurrentPage(0);
                navigationBar.state = "downloadingGetMouse"
            }
        }
    }

    NavigationButton {
        id: downloadedButton
        buttonText: qsTr("Complete")//"下载完成"//
        height: 30
        iconSource: "qrc:/images/navigation/downloaded-g"
        anchors {left:parent.left; top: downloadingButton.bottom; topMargin: buttonSpacing}

        MouseArea {
            id: downloadedMouse
            anchors.fill: parent
            onClicked: {
                rightPanel.setCurrentPage(1);
                navigationBar.state = "downloadedGetMouse"
            }
        }
    }

    NavigationButton {
        id: downloadTrashButton
        buttonText: qsTr("Trash")//"垃圾箱"//
        height: 30
        iconSource: "qrc:/images/navigation/trash-g"
        anchors {left:parent.left; top: downloadedButton.bottom; topMargin: buttonSpacing}

        MouseArea {
            id: downloadTrashMouse
            anchors.fill: parent
            onClicked: {
                rightPanel.setCurrentPage(2);
                navigationBar.state = "downloadTrashGetMouse"
            }
        }
    }

    Rectangle {
        id: bottomRec
        color: "#15a4fa"
        width: 3
        height: downloadingButton.height
        anchors.left: parent.left
        y:downloadingButton.y
    }

    states:[
//        State {
//            name: "searchGetMouse"
//            PropertyChanges {target: searchButton; fontColor: "#ffffff"}
//            PropertyChanges {target: searchButton; iconSource:"qrc:/images/navigation/home-w"}
//            PropertyChanges {target: searchButton; buttonColor: "#2f3949"}
//            PropertyChanges {target: bottomRec;y:searchButton.y}
//        },
        State {
            name: "downloadingGetMouse"
            PropertyChanges {target: downloadingButton;fontColor: "#ffffff"}
            PropertyChanges {target: downloadingButton;iconSource: "qrc:/images/navigation/downloading-w"}
            PropertyChanges {target: downloadingButton; buttonColor: "#00588a"}
            PropertyChanges {target: bottomRec;y:downloadingButton.y}
        },
        State {
            name: "downloadedGetMouse"
            PropertyChanges {target: downloadedButton;fontColor: "#ffffff"}
            PropertyChanges {target: downloadedButton;iconSource: "qrc:/images/navigation/downloaded-w"}
            PropertyChanges {target: downloadedButton; buttonColor: "#00588a"}
            PropertyChanges {target: bottomRec;y:downloadedButton.y}
        },
        State {
            name: "downloadTrashGetMouse"
            PropertyChanges {target: downloadTrashButton; fontColor: "#ffffff"}
            PropertyChanges {target: downloadTrashButton; iconSource: "qrc:/images/navigation/trash-w"}
            PropertyChanges {target: downloadTrashButton; buttonColor: "#00588a"}
            PropertyChanges {target: bottomRec;y:downloadTrashButton.y}
        }

    ]

    transitions: [
        Transition {
            from: "*";to: "*"
            PropertyAnimation {
                properties: "y"; duration: 300
            }
        }
    ]

}
