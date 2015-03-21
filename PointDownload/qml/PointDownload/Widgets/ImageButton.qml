/*************************************************************
*File Name: ImageButton.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月15日 星期日 18时13分19秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Item {

	property string pButtonId: ""
	property bool pButtonDisable: false
	property string pButtonIconNormalPath: ""
	property string pButtonIconHoverPath: ""
	property string pButtonIconPressPath: ""
	property string pButtonIconDisablePath: ""

	signal buttonClicked(string buttonId)

	onPButtonDisableChanged: {
		buttonImg.source = pButtonIconDisablePath
	}

	Image {
		id: buttonImg
		width: parent.width
		height: parent.height
		source: pButtonIconNormalPath
		anchors.fill: parent
	}

	MouseArea {
		anchors.fill: parent
		enabled: !pButtonDisable
		hoverEnabled: true
		onEntered: buttonImg.source = pButtonIconHoverPath
		onExited: buttonImg.source = pButtonIconNormalPath
		onPressed: buttonImg.source = pButtonIconPressPath
		onClicked: {
			parent.buttonClicked(pButtonId)
		}
	}
}
