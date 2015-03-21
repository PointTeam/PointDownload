/*************************************************************
*File Name: ../DonePanel/DoneFileItem.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月21日 星期六 14时14分51秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import "../Widgets"

Item {
	id: doneItem

	width: parent.width
	height: 40

	property string pFileId: ""
	property string pFileName: ""
	property double pFileSize: 0
	property var controlButtonModel: ListModel{

	Component.onCompleted: {
		append({
				"buttonId": "redownload",
				"buttonIconNormalPath": "../images/button-download-normal.png",
				"buttonIconHoverPath": "../images/button-download-hover.png",
				"buttonIconPressPath": "../images/button-download-press.png",
				"buttonIconDisablePath": "../images/button-download-disable.png",
				"buttonDisable": false
				})
		append({
				"buttonId": "folder",
				"buttonIconNormalPath": "../images/button-suspend-normal.png",
				"buttonIconHoverPath": "../images/button-suspend-hover.png",
				"buttonIconPressPath": "../images/button-suspend-press.png",
				"buttonIconDisablePath": "../images/button-suspend-disable.png",
				"buttonDisable": true
				})
		append({
				"buttonId": "trash",
				"buttonIconNormalPath": "../images/button-trash-normal.png",
				"buttonIconHoverPath": "../images/button-trash-hover.png",
				"buttonIconPressPath": "../images/button-trash-press.png"
				})
		append({
				"buttonId": "delete",
				"buttonIconNormalPath": "../images/button-delete-normal.png",
				"buttonIconHoverPath": "../images/button-delete-normal.png",
				"buttonIconPressPath": "../images/button-delete-normal.png"
				})
		}
	}

	RotatingRectangle {
		id: headRec
		width: 70
		height: parent.height
		fileSize: pFileSize
		taskProgress: 1
		shouldShowSpeed: false
	}

	Rectangle {
		id: nameBackRec
		width: parent.width - headRec.width
		height: parent.height
		color: "#3b4f67"
		opacity: 0.3
		anchors.verticalCenter: parent.verticalCenter
		anchors.left: headRec.left
	}

	Item {
		anchors.left: headRec.right
		anchors.verticalCenter: parent.verticalCenter
		width: parent.width - headRec.width
		height: parent.height

		Text {
			id: fileText
			width: parent.width
			text: pFileName
			color: "#ffffff"
			font.pixelSize: 20
			anchors.left: parent.left
			anchors.leftMargin: 15
			anchors.verticalCenter : parent.verticalCenter
			verticalAlignment: Text.AlignVCenter
		}

		ControlButtonLine {
			id: controlButtonLine
			color: "#4497dd"
			width: parent.width
			height: parent.height
			anchors.left: parent.left
			anchors.leftMargin: 0
			anchors.verticalCenter: parent.verticalCenter
			buttonModel: controlButtonModel
			onButtonClicked: {
				//TODO
			}
		}


		Timer {
			id: delayShowTimer
			interval: 300
			onTriggered: {
				fileText.visible = false
				controlButtonLine.show()
			}
		}

		MouseArea {
			anchors.fill: parent
			hoverEnabled: true
			propagateComposedEvents: true
			onEntered: {
				delayShowTimer.start()
			}
			onExited: {
				delayShowTimer.stop()
				controlButtonLine.hide()
				fileText.visible = true
			}
		}
	}
}

