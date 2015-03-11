/*************************************************************
*File Name: MiddleMenuItem.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月11日 星期三 00时27分53秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Item {
    id: menuItem

    property string menuItemName: ""
    property string menuItemId: ""
    property int taskCount: 0
    property bool showCount: true
	property bool inActived: false

    signal clicked(string itemId)

    width: menuTitleText.width + countRec.width + 3

    Text {
        id: menuTitleText
        text: menuItemName
        color: "#ffffff"
        font.bold: true
        font.pixelSize: 12
        height: parent.height
        width: contentWidth
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
    }

    Rectangle {
        id: countRec
        height: 12
        visible: showCount
        width: taskNumberText.width + 6
        color: "#e82500"
        radius: height
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id: taskNumberText
            text: taskCount
            color: "#ffffff"
            font.bold: true
            font.pixelSize: 9
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            width: contentWidth
            height: parent.height
            anchors.centerIn: parent
        }
    }

	Rectangle {
		id: activeRec
		opacity: inActived ? 1 : 0
		width: 5
		height: 5
		radius: 5
		color: "#ffffff"
		anchors.horizontalCenter: menuTitleText.horizontalCenter
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 3
		Behavior on opacity {
			NumberAnimation { duration: 300 }
		}
	}

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            menuTitleText.color = "#e77c0a"
        }
        onExited: {
            menuTitleText.color = "#ffffff"
        }
        onPressed: {
            menuTitleText.color = "#ffffff"
        }
        onReleased: {
            menuTitleText.color = "#e77c0a"
        }
        onClicked: {
            menuItem.clicked(menuItemId)
        }
    }
}
