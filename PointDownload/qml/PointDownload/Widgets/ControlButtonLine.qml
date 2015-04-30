/*************************************************************
*File Name: ControlButtonLine.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月15日 星期日 18时12分52秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Item {
	id: buttonLine
	width: parent.width
	height: parent.height

    property int buttonShowedIndex: -1
    property bool showing: false
    property var buttonModel

	signal buttonClicked(string buttonId)
    signal buttonAllHided

    function show(){
        showing = true
        buttonShowedIndex = 0
	}

    function hide(){
        showing = false
        buttonShowedIndex = contrlRepeater.count - 1
	}

	Row {
		id: buttonRow
		width: parent.width
		height: parent.height
		anchors.left: parent.left
		anchors.leftMargin: 20
		anchors.verticalCenter: parent.verticalCenter
        spacing: 20
        clip: true

		Repeater {
            id: contrlRepeater
			model: buttonModel
            delegate: ImageButton {
                width: 24
                height: 24
				pButtonId: buttonId
				pButtonIconNormalPath: buttonIconNormalPath
				pButtonIconHoverPath: buttonIconHoverPath
				pButtonIconPressPath: buttonIconPressPath
				pButtonIconDisablePath: typeof(buttonIconDisablePat) == "undefined" ? "" : buttonIconDisablePath
				pButtonDisable: typeof(buttonDisable) == "undefined" ? false : buttonDisable

                Connections {
                    target: buttonLine
                    onButtonShowedIndexChanged: {
                        if(showing && buttonShowedIndex == index){
                            showInCenter()
                        }
                        else if (!showing && buttonShowedIndex == index){
                            hideInBottom()
                        }
                    }
                }

				onButtonClicked: {
					print ("==>[Info] %1 button has been clicked!".arg(buttonId))
					buttonLine.buttonClicked(buttonId)
				}
                onShowed: buttonShowedIndex = index + 1
                onHided: {
                    buttonShowedIndex = index - 1
                    if (buttonShowedIndex < 0)
                        buttonLine.buttonAllHided()
                }
			}
		}
	}
}
