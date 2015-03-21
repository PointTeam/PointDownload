/*************************************************************
*File Name: TopBar.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月10日 星期二 22时02分38秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Rectangle {
    id:topBar
    width: parent.width

    color: "#0d0e0f"
    opacity: 0.8

	signal menuClicked(string menuItemId)

    Rectangle {
        id: iconTitleRec
        width: 120
        height: parent.height
        color: "#e22500"

        Text {
            id: titleText
            width: parent.width
            height: parent.height
            text: "PointDownload"
            font.bold: true
            font.pixelSize: 12
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.centerIn: parent
        }
    }

    MiddleMenu {
        id: middleMenu
        width: 210
        height: parent.height
        anchors.centerIn: parent
		onMenuClicked: {
			topBar.menuClicked(menuItemId)
		}
    }

    Rectangle {
        id: splitLineRec
        height: 14
        width: 1
        anchors.right: rightMenu.left
        anchors.rightMargin: 15
        anchors.verticalCenter: parent.verticalCenter
        color: "#ffffff"
    }

    RightMenu {
        id: rightMenu
        height: parent.height
        width: 180
        anchors.right: parent.right
		onMenuClicked: {
			topBar.menuClicked(menuItemId)
		}
    }
}
