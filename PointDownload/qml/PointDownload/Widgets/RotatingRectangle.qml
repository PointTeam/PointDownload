/*************************************************************
*File Name: RotatingRectangle.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月15日 星期日 10时26分35秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Item {

	property real fileSize: 0		//Byte
	property int fileSizeOnShow: {
		if (fileSize > 1024 * 1024 * 1024)
			return fileSize / (1024 * 1024 * 1024)
		else if (fileSize > 1024 * 1024)
			return fileSize / (1024 * 1024)
		else if (fileSize > 1024)
			return fileSize / 1024
		else
			return fileSize
	}
	property real showIntervalOfSpeed: 9000
	property real showIntervalOfSize: 3000
	property double taskProgress: 0		//0~1
	property real taskSpeed: 0	//Byte/Second
	property bool shouldShowSpeed: false

	property int rotaInterval: 700

	function getSizeUnit(){
		if (fileSize > 1024 * 1024 * 1024)
			return "GB"
		else if (fileSize > 1024 * 1024)
			return "MB"
		else if (fileSize > 1024)
			return "KB"
		else
			return "B"
	}

	function getSizeText(){
		var tmpStr = ""
		if (taskProgress != 1)
            tmpStr = (fileSizeOnShow * taskProgress).toFixed(1).toString() + "/" + fileSizeOnShow.toFixed(1).toString()
		else
            tmpStr = fileSizeOnShow.toFixed(1).toString()
		return tmpStr
	}

	function getSpeedUnit(){
		if (taskSpeed > 1024 * 1024)
			return "MB/S"
		else if (taskSpeed > 1024)
			return "KB/S"
		else
			return "B/S"
	}

	function getSpeedText(){
		if (taskSpeed > 1024 * 1024)
			return (taskSpeed/(1024 * 1024)).toFixed(2).toString()
		else if (taskSpeed > 1024)
			return (taskSpeed / 1024).toFixed(2).toString()
		else
			return taskSpeed.toFixed(2).toString()
	}

	onTaskProgressChanged: {
		sizeText.text = getSizeText()
	}

	onTaskSpeedChanged: {
		speedUnitText.text = getSpeedUnit()
		speedText.text = getSpeedText()
	}

	onShouldShowSpeedChanged: {
		if (shouldShowSpeed)
			speedTimer.start()
		else{
			sizeTimer.stop()
			speedTimer.stop()
			speedRec.visible = false
			sizeRec.visible = true
		}
	}

	Component.onCompleted: {
		sizeUnitText.text = getSizeUnit()
		sizeText.text = getSizeText()
		if (shouldShowSpeed)
			speedTimer.start()
	}

	Timer {
		id: sizeTimer
		interval: showIntervalOfSize + rotaInterval
		onTriggered: {
			sizeRec.visible = false
			sizeRota.angle = 180
			speedRota.angle = 0
			speedRec.visible = true
			speedTimer.start()
		}
	}

	Timer {
		id: speedTimer
		interval: showIntervalOfSpeed + rotaInterval
		onTriggered: {
			speedRec.visible = false
			speedRota.angle = 180
			sizeRota.angle = 0
			sizeRec.visible = true
			sizeTimer.start()
		}
	}

	Rectangle {
		id: sizeRec
		width: parent.width
		height: parent.height
		anchors.fill: parent
		color: "#70bcc4"

		Text {
			id: sizeText
			visible: sizeRota.angle < 90
			color: "#ffffff"
			font.pixelSize: 14
			anchors.verticalCenter: parent.verticalCenter
			anchors.horizontalCenter: parent.horizontalCenter
		}

		Text {
			id: sizeUnitText
			visible: sizeRota.angle < 90
			anchors.bottom: parent.bottom
			anchors.right: parent.right
			color: "#ffffff"
			font.pixelSize: 8
		}

		transform: Rotation {
			id:sizeRota
			origin.x: sizeRec.width / 2;
			origin.y: sizeRec.height / 2;
			axis { x: 1; y: 0; z: 0 }
			Behavior on angle {  // for animation
			NumberAnimation { duration: rotaInterval;easing.type : Easing.InOutBack }
			}
		}
	}

	Rectangle {
		id: speedRec
		width: parent.width
		height: parent.height
		anchors.fill: parent
		visible: false
		color: "#70bcc4"

		Text {
			id: speedText
			visible: speedRota.angle < 90
			color: "#ffffff"
			font.pixelSize: 14
			anchors.verticalCenter: parent.verticalCenter
			anchors.horizontalCenter: parent.horizontalCenter
		}

		Text {
			id: speedUnitText
			visible: speedRota.angle < 90
			anchors.bottom: parent.bottom
			anchors.right: parent.right
			color: "#ffffff"
			font.pixelSize: 8
		}

		transform: Rotation {
			id:speedRota
			origin.x: speedRec.width / 2;
			origin.y: speedRec.height / 2;
			axis { x: 1; y: 0; z: 0 }
			Behavior on angle {  // for animation
			NumberAnimation { duration: rotaInterval;easing.type : Easing.InOutBack }
			}
		}
	}
}
