/*************************************************************
*File Name: ValueInput.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年04月13日 星期一 23时44分05秒
*Description:
*
*************************************************************/
import QtQuick 2.1

FocusScope {
    id: mainScope
    width: parent.width
    height: parent.height
    clip: true

    property int maxValue: 10
    property int minValue: 0
    property int step: 1
    property alias textInput: input
    property alias title: titleText.text
    property alias imageButton: imgButton
    property bool showImageButton: false
    property string iconPath: ""


    Rectangle {
        width: parent.width
        height: parent.height
        anchors.fill: parent
        border.width: 2
        border.color: "#79CB8C"
        radius: 0
        clip: true

        Text {
            id: titleText
            width: contentWidth
            height: parent.height
            anchors {left: parent.left;leftMargin: 5; verticalCenter: parent.verticalCenter}
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            color: "#b4b4b4"
        }

        TextInput {
            id: input
            clip: true
            width: parent.width - titleText.width - imgButton.width - 25
            height: parent.height
            anchors {left: titleText.right;leftMargin: 5; verticalCenter: parent.verticalCenter}
            selectByMouse: true
            color: "#6d6b6b"
            selectionColor: "#66afd6"
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
            font.pixelSize: 15
            validator: IntValidator{bottom: minValue; top: maxValue;}

        }

        Rectangle {
            id: imgButton
            visible: showImageButton
            height: parent.height / 2
            width: showImageButton ? parent.height : 0
            color: "#79CB8C"
            anchors {right: parent.right; rightMargin: parent.height / 4; verticalCenter: parent.verticalCenter}

            Image {
                id: iconImg
                anchors.centerIn: parent
                width: 16
                height: 16
                source: iconPath
            }
        }

        MouseArea {
            anchors.fill: parent
            z: -5
            onWheel: {
                if (wheel.angleDelta.y > 0 && parseInt(input.text) + step <= maxValue){
                    input.text = (parseInt(input.text) + step).toString()
                }
                else if(wheel.angleDelta.y < 0 &&parseInt(input.text) - step >= minValue){
                    input.text = (parseInt(input.text) - step).toString()
                }
            }
        }
    }
}
