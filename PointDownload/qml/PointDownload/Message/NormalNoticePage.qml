import QtQuick 2.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtGraphicalEffects 1.0

Window {
    id:normalNoticePage
    flags:Qt.FramelessWindowHint | Qt.ToolTip

    color: "#00000000"
    width: 280
    height: 80
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
        font.bold: true
        anchors {top: mainRec.top; topMargin: 10; horizontalCenter: mainRec.horizontalCenter}
    }

    Text {
        id:messageText
        text: message
        color: "#c0dce6"
        font.pixelSize: 13
        width:mainRec.width - 20
        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignHCenter
    }

    ScrollView {
        id:csView
        contentItem: messageText
        width: mainRec.width - 20
        height: mainRec.height - 50
        style: ScrollViewStyle {
            transientScrollBars: true
            handle: Item {
                implicitWidth: 14
                implicitHeight: 18
                Rectangle {
                    color: "#114f64"
                    radius: 3
                    anchors.fill: parent
                    anchors.topMargin: 6
                    anchors.leftMargin: 4
                    anchors.rightMargin: 4
                    anchors.bottomMargin: 6
                }
            }
            scrollBarBackground: Item {
                implicitWidth: 14
                implicitHeight: 26
            }
        }
        anchors {top: noticeTitleText.bottom; topMargin: 5;bottomMargin: 10;right: mainRec.right; rightMargin: 8}
    }
    MouseArea {
        anchors.fill: csView
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

