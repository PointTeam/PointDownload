/*************************************************************
*File Name: ../DonePanel/DoneFileItem.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月21日 星期六 14时14分51秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import PDataType 1.0
import Singleton.MainController 1.0
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
                "buttonId": PDataType.PCtrlTypeReDownload,
                "buttonIconNormalPath": "qrc:/FileItem/images/button-download-normal.png",
                "buttonIconHoverPath": "qrc:/FileItem/images/button-download-normal.png",
                "buttonIconPressPath": "qrc:/FileItem/images/button-download-normal.png",
                "buttonIconDisablePath": "qrc:/FileItem/images/button-download-disable.png",
				"buttonDisable": false
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

	RotatingRectangle {
		id: headRec
        width: 80
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
                warningButton.x = 20 + (20 + 24) * buttonIndex - (warningButton.width - 24) / 2

                if (buttonId == PDataType.PCtrlTypeDelete){
                    warningButton.buttonId = buttonId
                    warningButton.buttonTitle = qsTr("Delete")
                    warningButton.visible = !warningButton.visible
                }
                else if (buttonId == PDataType.PCtrlTypeTrash){
                    warningButton.buttonId = buttonId
                    warningButton.buttonTitle = qsTr("Trash")
                    warningButton.visible = !warningButton.visible
                }
                else{
                    MainController.pControlFileItem(pFileId,PDataType.PDLTypeDownloaded, buttonId)
                    controlButtonLine.hide()
                    controlMouseArea.buttonShowed = false
                    warningButton.visible = false
                }
			}
		}

        ArrowTipButton {
            id: warningButton
            visible: false
            z: 5
            width: 60
            height: 30
            anchors.top: parent.top
            anchors.topMargin: parent.height - arrowHeight
            property int buttonId: -1
            onClicked: {
                MainController.pControlFileItem(pFileId,PDataType.PDLTypeDownloaded, buttonId)
            }
        }

        MouseArea {
            id: controlMouseArea
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

                warningButton.visible = false
            }
        }
	}
}

