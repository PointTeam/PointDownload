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
    id: imageButton

    state: "hideInBottom"

    property int pButtonId: 0
	property bool pButtonDisable: false
	property string pButtonIconNormalPath: ""
	property string pButtonIconHoverPath: ""
	property string pButtonIconPressPath: ""
	property string pButtonIconDisablePath: ""

    signal buttonClicked(int buttonId)
    signal showed
    signal hided

    function showInCenter(){
        delaySenderTimer.restart()
        imageButton.state = "showInCenter"
    }

    function hideInBottom(){
        delaySenderTimer.restart()
        imageButton.state = "hideInBottom"
    }

	onPButtonDisableChanged: {
		buttonImg.source = pButtonIconDisablePath
	}

    Timer {
        id: delaySenderTimer
        interval: 70
        onTriggered: {
            if (imageButton.state == "showInCenter")
                imageButton.showed()
            else
                imageButton.hided()
        }
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

    states: [
        State {
            name: "showInCenter"
            AnchorChanges { target: imageButton; anchors.verticalCenter: parent.verticalCenter; anchors.top: undefined}
        },
        State {
            name: "hideInBottom"
            AnchorChanges { target: imageButton; anchors.verticalCenter: undefined; anchors.top: parent.bottom}
        }
    ]

    transitions: Transition {
        AnchorAnimation { duration: 200; easing.type: Easing.OutCirc }
    }
}
