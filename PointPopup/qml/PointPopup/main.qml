/*************************************************************
*File Name: main.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年04月05日 星期日 15时34分31秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import QtGraphicalEffects 1.0
import QtQuick.Window 2.1
import Singleton.PEventFilter 1.0
import Singleton.DataController 1.0
import SettingXMLHandler 1.0
import "./SearchBar"

Window {
    id:mainWindow
    width: 600
    height: readyForDownload ? 500 : 75
    x: 500
    y: 200
    color: "#00000000"
    flags: Qt.FramelessWindowHint

    property int frameRadius: 3
    property int shadowRadius: 10
    property bool readyForDownload: false

    Component.onCompleted: {
        mainWindow.show()
    }

    Connections{
        target: DataController
        onSignalFileInfoListChanged: {
            readyForDownload = true
        }
    }

    SettingXMLHandler {
        id: settingXMLHandler
    }

    Rectangle {
        id: mainRec
        anchors.centerIn: parent
        color: "#3A4246"
        radius: frameRadius
        border.width: 1
        border.color: Qt.rgba(1, 1, 1, 0.15)
        width: mainWindow.width - (shadowRadius + frameRadius) * 2
        height: mainWindow.height - (shadowRadius + frameRadius) * 2

        SearchBar {
            id: searchBar
            width: parent.width
            height: 75 - (shadowRadius + frameRadius) * 2
            anchors.top: parent.top
        }

        ContentPanel {
            id: contentPanel
            width: parent.width
            height: readyForDownload ? 400 : 0
            anchors {top: searchBar.bottom; topMargin: 10; horizontalCenter: mainRec.horizontalCenter}
        }
    }

    RectangularGlow {
        id: shadow
        z: -1
        anchors.fill: mainRec
        glowRadius: shadowRadius
        spread: 0.2
        color: Qt.rgba(0, 0, 0, 0.3)
        cornerRadius: mainRec.radius + shadowRadius
        visible: true
    }

    MouseArea{
        id:mArea
        z: -6
        anchors.fill: parent

        property int oldX: 0
        property int oldY: 0
        property bool dragIng: false

        onPressed: {
            oldX = mouseX
            oldY = mouseY
            dragIng = true
            mArea.cursorShape=Qt.DragMoveCursor
        }
        onReleased: {
            dragIng = false
            mArea.cursorShape=Qt.ArrowCursor
        }

        onPositionChanged: {
            if (dragIng){
                mainWindow.x = PEventFilter.globalX- oldX
                mainWindow.y = PEventFilter.globalY - oldY;
            }
        }
    }
}

