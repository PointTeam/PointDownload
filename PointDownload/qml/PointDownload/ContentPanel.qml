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

Item {
	id: contentItem

	property var stackViewPages: {
		"taskPage": Qt.resolvedUrl("TaskPanel/TaskMainFrame.qml"),
		"donePage": Qt.resolvedUrl("DonePanel/DoneMainFrame.qml"),
		"trashPage": Qt.resolvedUrl("TrashPanel/TrashMainFrame.qml"),
		"settingPage": Qt.resolvedUrl("SettingPanel/SettingFrame.qml")
	}

	function gotoTaskPage(){
		stackView.push({
			"item": stackViewPages["taskPage"],
			"properties": {"width": contentItem.width}
		})
	}

	function gotoDonePage(){
		stackView.push({
			"item": stackViewPages["donePage"],
			"properties": {"width": contentItem.width}
		})
	}

	function gotoTrashPage(){
		stackView.push({
			"item": stackViewPages["trashPage"],
			"properties": {"width": contentItem.width}
		})
	}

	function gotoSettingPage(){
		stackView.push({
			"item": stackViewPages["settingPage"],
			"properties": {"width": contentItem.width}
		})
	}

	StackView {
		id: stackView
		width: parent.width
		height: parent.height

		function reset(){
			stackView.pop(null)
		}

		Component.onCompleted: gotoTaskPage()
	}
}
