/*************************************************************
*File Name: ControlPage.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年04月11日 星期六 23时25分03秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Rectangle{
    width: parent.width

    ValueInput {
        id: storageInput
        width: 230 * 2 + 70
        height: 40
        anchors {left:parent.left; leftMargin: 10; top: parent.top; topMargin: 20}
        title: "Storage:"
        maxValue: 10
        minValue: 1
        step: 1
        showImageButton: true
        iconPath: "qrc:///images/button-folder-normal.png"
        textInput.horizontalAlignment: TextInput.AlignLeft
        textInput.validator: null
        textInput.color: "#b4b4b4"
        textInput.text: "/home/wanqing/Downloads/PointDownload"
    }

    ValueInput {
        id: dlThreadInput
        width: 240
        height: 40
        anchors {left:parent.left; leftMargin: 10; top: storageInput.bottom; topMargin: 20}
        title: "Max Thread:"
        maxValue: 10
        minValue: 1
        step: 1
        textInput.text: "5"
    }

    ValueInput {
        id: dlSpeadInput
        width: 240
        height: 40
        anchors {right: parent.right; rightMargin: 10; top: storageInput.bottom; topMargin: 20}
        title: "Max Speed(KBps):"
        maxValue: 100 * 1024
        minValue: 1
        step: 100
        textInput.text: "500"
    }

    Rectangle {
        id: downloadButton
        width: dlSpeadInput.width / 2
        height: 40
        radius: 0
        color: "#d94255"
        anchors {bottom: parent.bottom; bottomMargin: 10; right: dlSpeadInput.right}

        Text {
            id: titleText
            width: contentWidth
            height: parent.height
            anchors {horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "#d0c5c7"
            font.pixelSize: 17
            text: qsTr("Download")
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                titleText.color = "#ffffff"
            }
            onExited: {
                titleText.color = "#d0c5c7"
            }
            onClicked: {
                //Sent info to server
            }
        }
    }

}
