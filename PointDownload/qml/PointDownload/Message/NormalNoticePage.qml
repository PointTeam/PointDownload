import QtQuick 2.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtGraphicalEffects 1.0

Window {
    id:normalNoticePage
    flags:Qt.FramelessWindowHint | Qt.ToolTip

    color: "#00000000"
    width: 280
    height: 30 + messageText.height + noticeTitleText.height
    opacity: 1

    property string messageTitle: ""
    property string titleColor: ""
    property string message: ""

    x:Screen.width - width - 10
    y:20

    Timer {
        id:delayTimer
        interval: 3500
        repeat: false
        running: true
        onTriggered: destoryNotice()
    }

    Rectangle {
        id:mainRec
        width: parent.width
        height: parent.height
        radius: 6
        color: "#1f6f8c"
        opacity: 0.8

        anchors {fill: parent; rightMargin: 10}

    }

    Text {
        id:noticeTitleText
        text:messageTitle
        color: titleColor
        font.pixelSize: 15
        width:mainRec.width - 25
        font.bold: true
        wrapMode: Text.Wrap
        anchors {top: mainRec.top; topMargin: 10; horizontalCenter: mainRec.horizontalCenter}
    }

    Text {
        id:messageText
        text: message
        color: "#c0dce6"
        font.pixelSize: 13
        width:mainRec.width - 20
        wrapMode: Text.Wrap
        anchors {top: noticeTitleText.bottom; topMargin: 10; horizontalCenter: mainRec.horizontalCenter}
    }

    MouseArea {
        anchors.fill: messageText
        hoverEnabled: true
        onEntered: delayTimer.stop()
        onExited: delayTimer.start()
    }

    Rectangle {
        id:closeRec
        width: 20
        height: 20
        radius: 20
        color: "#1f6f8c"
        opacity: 0.8

        anchors {top: parent.top; right: parent.right}

        Image {
            id: closeImg
            source: "qrc:/images/dropzone/closebutton"
            anchors {verticalCenter:  parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
            height: parent.height - 3
            width: parent.height - 3

            MouseArea {
                anchors.fill: parent
                onClicked: destoryNotice()
            }

        }

    }

    function destoryNotice()
    {
        normalNoticePage.destroy()
    }
}

