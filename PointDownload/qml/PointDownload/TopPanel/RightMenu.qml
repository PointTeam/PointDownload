/*************************************************************
*File Name: RightMenuItem.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月10日 星期二 22时40分50秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Item {
    id: rightMenu

	signal menuClicked(string menuItemId)

    Row {
        id: middleMenuRow
        spacing: 10
        anchors.fill: parent
        width: parent.width
        height: parent.height

        RightMenuItem {
            id: settingMenuItem
            height: middleMenu.height
            menuItemId: "Setting"
            menuItemName: qsTr("Setting")
            onClicked: {
                print ("==>[Info] Menu clicked:",menuItemId)
				rightMenu.menuClicked(menuItemId)
            }
        }

        RightMenuItem {
            id: storageMenuItem
            height: middleMenu.height
            menuItemId: "Storage"
            menuItemName: qsTr("Storage")
            onClicked: {
                print ("==>[Info] Menu clicked:",menuItemId)
				rightMenu.menuClicked(menuItemId)
            }
        }

        RightMenuItem {
            id: newTaskMenuItem
            height: middleMenu.height
            menuItemId: "New"
            menuItemName: qsTr("New")
            onClicked: {
                print ("==>[Info] Menu clicked:",menuItemId)
				rightMenu.menuClicked(menuItemId)
            }
        }

        RightMenuItem {
            id: quickMenuItem
            height: middleMenu.height
            menuItemId: "Quick"
            menuItemName: qsTr("Quick")
            onClicked: {
                print ("==>[Info] Menu clicked:",menuItemId)
				rightMenu.menuClicked(menuItemId)
				Qt.quit()
            }
        }

    }
}
