import QtQuick 2.0
import settingControler 1.0

Rectangle {
    id:priorityToolItem

    property string priorityTool:settingCtrl.priorityTool
    property int iconSize: 20
    color: "#3b5a6f"
    state:settingCtrl.priorityTool == "Point"?"activePoint":settingCtrl.priorityTool == "Aria2"?"activeAria2":"activeXware"

    SettingControler{
        id:settingCtrl
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            subItem1.opacity = 0
            subItem2.opacity = 1
        }
        onExited: {
            subItem1.opacity = 1
            subItem2.opacity = 0
        }
    }

    Rectangle{
        id:subItem1
        width: parent.width - 16
        height: parent.height
        color: "#233a4a"
        radius: 3
        clip: true
        anchors {top: parent.top; left: parent.left; leftMargin: 8}

        Text{
            id:titleText
            text: qsTr("Priority Components :")
            color: "#cdd7d9"
            font.pixelSize: 13
            height: 30
            width: 130
            anchors {left:parent.left; leftMargin: 10;top:parent.top; topMargin: 7}
        }

        Text{
            text:priorityTool
            color: "#cdd7d9"
            font.pixelSize: 10
            height: 30
            width: parent.width - titleText.width
            anchors {left:titleText.right; leftMargin: 2;top:parent.top; topMargin: 9}
        }
    }

    Rectangle{
        id:subItem2
        opacity: 0
        width: parent.width - 16
        height: parent.height
        color: "#d74e68"
        radius: 2
        anchors {top: parent.top; left: parent.left; leftMargin: 8}

        Rectangle{
            id:pointItem
            width: parent.width / 4
            height: parent.height
            color: "#d74e68"
            anchors {left: parent.left; leftMargin: 12; top: parent.top}
            Image{
                id:checkImg
                source: "qrc:/images/dropzone/checked"
                width: iconSize
                height: iconSize
                anchors {left: parent.left; verticalCenter: parent.verticalCenter}

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        priorityToolItem.state = "activePoint"
                        settingCtrl.selectPriorityTool("Point")
                    }
                }
            }

            Text{
                text: qsTr("Point")
                color: "#ffffff"
                font.pixelSize: 13
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors { left: checkImg.right; leftMargin: 2; verticalCenter: parent.verticalCenter}
            }
        }
        Rectangle{
            id:aria2Item
            width: parent.width / 4
            height: parent.height
            color: "#d74e68"
            anchors {left: pointItem.right; leftMargin: 14; top: parent.top}
            Image{
                id:checkImg2
                source: "qrc:/images/dropzone/uncheck"
                width: iconSize
                height: iconSize
                anchors {left: parent.left; verticalCenter: parent.verticalCenter}

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        priorityToolItem.state = "activeAria2"
                        settingCtrl.selectPriorityTool("Aria2")
                    }
                }
            }

            Text{
                text: qsTr("Aria2")
                color: "#ffffff"
                font.pixelSize: 13
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors { left: checkImg2.right; leftMargin: 2; verticalCenter: parent.verticalCenter}
            }
        }
        Rectangle{
            id:xwareItem
            width: parent.width / 4
            height: parent.height
            color: "#d74e68"
            anchors {left: aria2Item.right; leftMargin: 14; top: parent.top}

            Image{
                id:checkImg3
                source: "qrc:/images/dropzone/uncheck"
                width: iconSize
                height: iconSize
                anchors {left: parent.left; verticalCenter: parent.verticalCenter}

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        priorityToolItem.state = "activeXware"
                        settingCtrl.selectPriorityTool("Xware")
                    }
                }
            }

            Text{
                text: qsTr("Xware")
                color: "#ffffff"
                font.pixelSize: 13
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors { left: checkImg3.right; leftMargin: 2; verticalCenter: parent.verticalCenter}
            }
        }
    }

    states:[
        State {
            name: "activePoint"
            PropertyChanges {target: checkImg;source:"qrc:/images/dropzone/checked"}
            PropertyChanges {target: checkImg2;source:"qrc:/images/dropzone/uncheck"}
            PropertyChanges {target: checkImg3;source:"qrc:/images/dropzone/uncheck"}
        },
        State {
            name:"activeAria2"
            PropertyChanges {target: checkImg;source:"qrc:/images/dropzone/uncheck"}
            PropertyChanges {target: checkImg2;source:"qrc:/images/dropzone/checked"}
            PropertyChanges {target: checkImg3;source:"qrc:/images/dropzone/uncheck"}
        },
        State {
            name:"activeXware"
            PropertyChanges {target: checkImg;source:"qrc:/images/dropzone/uncheck"}
            PropertyChanges {target: checkImg2;source:"qrc:/images/dropzone/uncheck"}
            PropertyChanges {target: checkImg3;source:"qrc:/images/dropzone/checked"}
        }
    ]
}
