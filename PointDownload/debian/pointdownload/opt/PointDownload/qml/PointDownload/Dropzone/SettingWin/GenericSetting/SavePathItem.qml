import QtQuick 2.0
import settingControler 1.0

Rectangle {
    id:savePathItem

    property string newSavePath:settingCtrl.savePath
    property int iconSize: 20
    color: "#3b5a6f"
    state:settingCtrl.savePathState == "Default"?"useDefault":settingCtrl.savePathState == "Desktop"?"useDesktop":"useOther"

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
            text: qsTr("SavePath:")
            color: "#cdd7d9"
            font.pixelSize: 13
            height: 30
            width: 60
            anchors {left:parent.left; leftMargin: 10;top:parent.top; topMargin: 7}
        }

        Text{
            id:pathText
            text:newSavePath
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
            id:defaultItem
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
                        savePathItem.state = "useDefault"
                        settingCtrl.selectSavePath("Default")
                    }
                }
            }

            Text{
                text: qsTr("Default")
                color: "#ffffff"
                font.pixelSize: 13
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors { left: checkImg.right; leftMargin: 2; verticalCenter: parent.verticalCenter}
            }
        }
        Rectangle{
            id:desktopItem
            width: parent.width / 4
            height: parent.height
            color: "#d74e68"
            anchors {left: defaultItem.right; leftMargin: 14; top: parent.top}
            Image{
                id:checkImg2
                source: "qrc:/images/dropzone/uncheck"
                width: iconSize
                height: iconSize
                anchors {left: parent.left; verticalCenter: parent.verticalCenter}

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        savePathItem.state = "useDesktop"
                        settingCtrl.selectSavePath("Desktop")
                    }
                }
            }

            Text{
                text: qsTr("Desktop")
                color: "#ffffff"
                font.pixelSize: 13
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors { left: checkImg2.right; leftMargin: 2; verticalCenter: parent.verticalCenter}
            }
        }
        Rectangle{
            id:otherItem
            width: parent.width / 4
            height: parent.height
            color: "#d74e68"
            anchors {left: desktopItem.right; leftMargin: 14; top: parent.top}
            Image{
                id:checkImg3
                source: "qrc:/images/dropzone/uncheck"
                width: iconSize
                height: iconSize
                anchors {left: parent.left;verticalCenter: parent.verticalCenter}


                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        savePathItem.state = "useOther"
                        settingCtrl.selectSavePath("Other")
                    }
                }
            }

            Text{
                text: qsTr("Other")
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
            name: "useDefault"
            PropertyChanges {target: checkImg;source:"qrc:/images/dropzone/checked"}
            PropertyChanges {target: checkImg2;source:"qrc:/images/dropzone/uncheck"}
            PropertyChanges {target: checkImg3;source:"qrc:/images/dropzone/uncheck"}
        },
        State {
            name:"useDesktop"
            PropertyChanges {target: checkImg;source:"qrc:/images/dropzone/uncheck"}
            PropertyChanges {target: checkImg2;source:"qrc:/images/dropzone/checked"}
            PropertyChanges {target: checkImg3;source:"qrc:/images/dropzone/uncheck"}
        },
        State {
            name:"useOther"
            PropertyChanges {target: checkImg;source:"qrc:/images/dropzone/uncheck"}
            PropertyChanges {target: checkImg2;source:"qrc:/images/dropzone/uncheck"}
            PropertyChanges {target: checkImg3;source:"qrc:/images/dropzone/checked"}
        }
    ]
}
