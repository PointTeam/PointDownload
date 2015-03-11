/*************************************************************
*File Name: RightMenuItem.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月11日 星期三 21时08分57秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Item {
    id: menuItem

    property string menuItemName: ""
    property string menuItemId: ""

    width: menuTitleText.width

    signal clicked(string itemId)

    Text {
        id: menuTitleText
        text: menuItemName
        color: "#ffffff"
        font.bold: true
        font.pixelSize: 10
        height: parent.height
        width: contentWidth
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        Behavior on color {
            PropertyAnimation { duration: 200; easing.type: Easing.OutQuad }
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

