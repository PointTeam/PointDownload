import QtQuick 2.1
import QtQuick.Window 2.1
import Singleton.PEventFilter 1.0

Window {
    id:dropzonePage
    flags: Qt.WindowStaysOnTopHint |Qt.FramelessWindowHint | Qt.ToolTip

    color: "#00000000"

    width: tipText.width + 30
    height: tipText.height + 10

    property alias toolTips: tipText.text
    property int showInterval: 1500
    property int destroyInterval: 2000

    Timer {
        id: outDelayTimer
        interval: showInterval;
        running: false;
        onTriggered: {
            x = PEventFilter.globalX  + 10
            y = PEventFilter.globalY - 10
            dropzonePage.show()
            destroyTimer.start()
        }
    }
    Timer{
        id:destroyTimer
        interval: destroyInterval
        running: false
        onTriggered: dropzonePage.opacity = 0
    }

    Image{
        id:leftArrow
        width: 10
        height: parent.height  / 2
        source: "qrc:/images/setting/LeftArrow"
        anchors {left:parent.left; verticalCenter: parent.verticalCenter}
    }
    Rectangle{
        id:bodyRec
        color: "#4c637b"
        width: parent.width - 20
        height: parent.height
        anchors {left:parent.left;leftMargin: 8; right: parent.right;rightMargin: 10;  verticalCenter: parent.verticalCenter }

        Text{
            id:tipText
            text:""
            color: "#ffffff"
            font.pixelSize: 13
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
        }
    }
    Rectangle{
        id:radiusRec
        radius: 3
        width: 10
        height: bodyRec.height
        color: bodyRec.color
        anchors {right: parent.right; rightMargin: 3}
    }

    function startTimer()
    {
        outDelayTimer.start()
    }
}
