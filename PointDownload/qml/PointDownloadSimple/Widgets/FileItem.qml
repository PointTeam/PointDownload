/*************************************************************
*File Name: FileItem.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月12日 星期四 20时17分22秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Item {
	id: fileItem

	property string pFileId: ""
	property string pFileName: ""
	property double pFileSize: 0
	property var pTaskState
	property var pTaskSpeed
	property var pTaskProgress

	width: parent.width
	height: 40

	RotatingRectangle {
		id: headRec
		width: 70
		height: parent.height
		fileSize: pFileSize
		taskSpeed: 34543//pTaskSpeed
		taskProgress: pTaskProgress
		shouldShowSpeed: true
	}

	Rectangle {
		id: nameBackRec
		width: parent.width - headRec.width
		height: parent.height
		color: "#3b4f67"
		opacity: 0.3
		anchors.verticalCenter: parent.verticalCenter
		anchors.left: headRec.right
	}

	Text {
		id: fileText
		width: parent.width - headRec.width
		text: pFileName
		color: "#ffffff"
		font.pixelSize: 20
		anchors.left: headRec.right
		anchors.leftMargin: 15
		anchors.verticalCenter : parent.verticalCenter
		verticalAlignment: Text.AlignVCenter
	}
}

