/*************************************************************
*File Name: ControlButtonLine.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月15日 星期日 18时12分52秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Rectangle {
	id: buttonLine
	width: parent.width
	height: parent.height

	property var buttonModel
	property int rotaInterval: 600

	signal buttonClicked(string buttonId)

	function show(){
		buttonLine.visible = true
		controlRota.angle = 0
	}

	function hide(){
		controlRota.angle = 180
	}

	Component.onCompleted: {
		buttonLine.visible = false
		controlRota.angle = 180
	}

	Row {
		id: buttonRow
		width: parent.width
		height: parent.height
		anchors.left: parent.left
		anchors.leftMargin: 20
		anchors.verticalCenter: parent.verticalCenter
        spacing: 20

		Repeater {
			model: buttonModel
			delegate: ImageButton {
				visible: controlRota.angle < 90
                width: 24
                height: 24
				anchors.verticalCenter: parent.verticalCenter
				pButtonId: buttonId
				pButtonIconNormalPath: buttonIconNormalPath
				pButtonIconHoverPath: buttonIconHoverPath
				pButtonIconPressPath: buttonIconPressPath
				pButtonIconDisablePath: typeof(buttonIconDisablePat) == "undefined" ? "" : buttonIconDisablePath
				pButtonDisable: typeof(buttonDisable) == "undefined" ? false : buttonDisable

				onButtonClicked: {
					print ("==>[Info] %1 button has been clicked!".arg(buttonId))
					buttonLine.buttonClicked(buttonId)
				}
			}
		}
	}

	transform: Rotation {
		id:controlRota
		origin.x: buttonLine.width / 2;
		origin.y: buttonLine.height / 2;
		axis { x: 1; y: 0; z: 0 }
		Behavior on angle {  // for animation
			NumberAnimation { duration: rotaInterval;easing.type : Easing.InOutBack }
		}
		onAngleChanged: {
			if (angle == 180)
				buttonLine.visible = false
		}
	}
}
