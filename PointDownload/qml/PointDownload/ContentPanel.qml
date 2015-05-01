/*************************************************************
*File Name: ContentPanel.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月12日 星期四 22时28分28秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import QtQuick.Controls 1.2
import "./TaskPanel"
import "./DonePanel"
import "./TrashPanel"
import "./SettingPanel"

Item {
	id: contentItem

    property int taskCount: taskMainFrame.getItemCount()
    property int doneCount: doneMainFrame.getItemCount()
    property int trashCount: trashMainFrame.getItemCount()
    property int currentIndex: contentListView.currentIndex

    function gotoTaskPage(){
        contentListView.currentIndex = 0
	}

	function gotoDonePage(){
        contentListView.currentIndex = 1
	}

	function gotoTrashPage(){
        contentListView.currentIndex = 2
	}

	function gotoSettingPage(){
        contentListView.currentIndex = 3
	}

    ListView {
        id:contentListView

        width: parent.width
        height: parent.height

        model: itemModel
        snapMode: ListView.SnapToItem
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        flickDeceleration: 5000
        highlightFollowsCurrentItem: true
        highlightMoveDuration:500
        highlightRangeMode: ListView.StrictlyEnforceRange
        currentIndex: 0

        clip: true

        VisualItemModel
        {
            id: itemModel
            TaskMainFrame {id:taskMainFrame; width: contentItem.width; height: contentItem.height}
            DoneMainFrame {id:doneMainFrame; width: contentItem.width; height: contentItem.height}
            TrashMainFrame {id:trashMainFrame; width: contentItem.width; height: contentItem.height}
            SettingFrame {id:settingFrame; width: contentItem.width; height: contentItem.height}
        }

        function refresh()
        {
            currentItem.refresh();
        }
    }
}
