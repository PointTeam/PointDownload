/*************************************************************
*File Name: MiddleMenu.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月10日 星期二 22时40分25秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Item {
    id:middleMenu

    property int dingTaskCount: 9
    property int ddoneTaskCount: 20
    property int dtrashTaskCount: 5
	property int activeIndex: 0

	signal menuClicked(string menuItemId)

	Row {
        id: middleMenuRow
        spacing: 30
        anchors.fill: parent
        width: parent.width
        height: parent.height

        MiddleMenuItem {
            id: dingMenuItem
            height: middleMenu.height
            menuItemId: "Task"
            menuItemName: qsTr("Task")
            taskCount: dingTaskCount
			inActived: activeIndex == 0
            onClicked: {
                print ("==>[Info] Menu clicked:",menuItemId)
				activeIndex = 0
				middleMenu.menuClicked(menuItemId)
            }
        }

        MiddleMenuItem {
            id: ddoneMenuItem
            height: middleMenu.height
            menuItemId: "Done"
            menuItemName: qsTr("Done")
            taskCount: ddoneTaskCount
			inActived: activeIndex == 1
            onClicked: {
                print ("==>[Info] Menu clicked:",menuItemId)
				activeIndex = 1
				middleMenu.menuClicked(menuItemId)
            }
        }

        MiddleMenuItem {
            id: dtrashMenuItem
            height: middleMenu.height
            menuItemId: "Trash"
            menuItemName: qsTr("Trash")
            taskCount: dtrashTaskCount
			inActived: activeIndex == 2
            onClicked: {
                print ("==>[Info] Menu clicked:",menuItemId)
				activeIndex = 2
				middleMenu.menuClicked(menuItemId)
            }
        }

    }

}
