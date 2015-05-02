/*************************************************************
*File Name: TaskFileItem.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月15日 星期日 20时17分54秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import PDataType 1.0
import "../Widgets"

Item {
	id: taskItem

	width: parent.width
	height: 40

	property string pFileId: ""
	property string pFileName: ""
	property double pFileSize: 0
	property var pTaskState
	property var pTaskSpeed
	property var pTaskProgress
	property var controlButtonModel: ListModel{

	function changeDownloadButtonState(state){
		if (controlButtonModel.count > 0)
			setProperty(0,"buttonDisable",!state)
	}

	function changeSuspendButtonState(state){
		if (controlButtonModel.count > 1)
			setProperty(1,"buttonDisable",!state)
	}

	Component.onCompleted: {
		append({
                "buttonId": PDataType.PCtrlTypeResume,
                "buttonIconNormalPath": "qrc:/FileItem/images/button-download-normal.png",
                "buttonIconHoverPath": "qrc:/FileItem/images/button-download-hover.png",
                "buttonIconPressPath": "qrc:/FileItem/images/button-download-press.png",
                "buttonIconDisablePath": "qrc:/FileItem/images/button-download-disable.png",
				"buttonDisable": false
				})
		append({
                "buttonId": PDataType.PCtrlTypeSuspend,
                "buttonIconNormalPath": "qrc:/FileItem/images/button-suspend-normal.png",
                "buttonIconHoverPath": "qrc:/FileItem/images/button-suspend-normal.png",
                "buttonIconPressPath": "qrc:/FileItem/images/button-suspend-normal.png",
                "buttonIconDisablePath": "qrc:/FileItem/images/button-suspend-normal.png",
                "buttonDisable": false
                })
        append({
                "buttonId": PDataType.PCtrlTypeRaise,
                "buttonIconNormalPath": "qrc:/FileItem/images/button-raise-normal.png",
                "buttonIconHoverPath": "qrc:/FileItem/images/button-raise-normal.png",
                "buttonIconPressPath": "qrc:/FileItem/images/button-raise-normal.png"
                })
        append({
                "buttonId": PDataType.PCtrlTypeOpenFolder,
                "buttonIconNormalPath": "qrc:/FileItem/images/button-folder-normal.png",
                "buttonIconHoverPath": "qrc:/FileItem/images/button-folder-normal.png",
                "buttonIconPressPath": "qrc:/FileItem/images/button-folder-normal.png"
                })
		append({
                "buttonId": PDataType.PCtrlTypeTrash,
                "buttonIconNormalPath": "qrc:/FileItem/images/button-trash-normal.png",
                "buttonIconHoverPath": "qrc:/FileItem/images/button-trash-normal.png",
                "buttonIconPressPath": "qrc:/FileItem/images/button-trash-normal.png"
				})
		append({
                "buttonId": PDataType.PCtrlTypeDelete,
                "buttonIconNormalPath": "qrc:/FileItem/images/button-delete-normal.png",
                "buttonIconHoverPath": "qrc:/FileItem/images/button-delete-normal.png",
                "buttonIconPressPath": "qrc:/FileItem/images/button-delete-normal.png"
				})
		}
	}

    onPTaskStateChanged: {
        if (pTaskState == PDataType.PTaskStateDownloading){
			controlButtonModel.changeDownloadButtonState(false)
			controlButtonModel.changeSuspendButtonState(true)
		}
		else{
			controlButtonModel.changeDownloadButtonState(true)
			controlButtonModel.changeSuspendButtonState(false)
		}
	}

	RotatingRectangle {
		id: headRec
        width: 80
		height: parent.height
		fileSize: pFileSize
        taskSpeed: pTaskSpeed
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
            Behavior on opacity {
                NumberAnimation {duration: 200}
            }
		}

		ControlButtonLine {
            id: controlButtonLine
			width: parent.width
			height: parent.height
			anchors.left: parent.left
			anchors.leftMargin: 0
			anchors.verticalCenter: parent.verticalCenter
			buttonModel: controlButtonModel
            onButtonAllHided: fileText.opacity = 1
			onButtonClicked: {
				//TODO
			}
		}

		MouseArea {
            z: -1
			anchors.fill: parent
			hoverEnabled: true
			propagateComposedEvents: true

            property bool buttonShowed: false
            onClicked: {
                if (!buttonShowed){
                    fileText.opacity = 0
                    controlButtonLine.show()
                    buttonShowed = true
                }
                else{
                    controlButtonLine.hide()
                    buttonShowed = false
                }
            }
		}
	}
}

