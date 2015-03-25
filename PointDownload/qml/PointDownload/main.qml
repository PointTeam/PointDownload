/*************************************************************
*File Name: main.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月10日 星期二 21时19分35秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import QtQuick.Window 2.1
import Singleton.MainController 1.0
//import TaskInfo 1.0
import "./TopPanel"

Window {
    id:mainWindow
    width: 800
    height: 500
    x: 300
    y: 100
    color: "#00000000"
    flags: Qt.FramelessWindowHint

    property var backbroundImagePath: "qrc:/FileItem/images/backimg.jpg"
    property alias backgroundImageOpacity: backgroundImage.opacity
    property var backbroundRecColor: "#116666"
    property alias backbroundRecOpacity: backgroundRec.opacity

    Component.onCompleted: {
        mainWindow.show()
        MainController.pSuspendAllTask()
    }

    Connections {
        target: MainController
        onSignalAddDownloadingItem: {
            print ("====================------------------",taskInfo.maxThreads,taskInfo.fileID,taskInfo.rawUrl)
        }
    }

    MouseArea {
        anchors.fill: parent
        property int startX
        property int startY
        property bool holdFlag
        onPressed: {
            startX = mouse.x;
            startY = mouse.y;
            holdFlag = true;
        }
        onReleased: holdFlag = false;
        onPositionChanged: {
            if (holdFlag) {
                mainWindow.setX(mainWindow.x + mouse.x - startX)
                mainWindow.setY(mainWindow.y + mouse.y - startY)
            }
        }
    }

    TopBar {
        id: topBar
        width: parent.width
        height: 40
        z: 1
        onMenuClicked: {
            if (menuItemId == "Task")
                contentPanel.gotoTaskPage()
            else if (menuItemId == "Done")
                contentPanel.gotoDonePage()
            else if (menuItemId == "Trash")
                contentPanel.gotoTrashPage()
            else if (menuItemId == "Setting")
                contentPanel.gotoSettingPage()
        }
    }

    ContentPanel {
        id: contentPanel
        width: parent.width
        height: parent.height - topBar.height
        z: 1
        anchors.top: topBar.bottom
    }

    Item {
        anchors.fill: parent
        width: parent.width
        height: parent.height

        Image {
            id: backgroundImage
            anchors.fill: parent
            opacity: 1
            source: backbroundImagePath
        }
    }

    Rectangle {
        id: backgroundRec
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        color: backbroundRecColor
        opacity: 0
        radius: 6
    }
}
