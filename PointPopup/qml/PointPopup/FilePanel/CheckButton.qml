/*************************************************************
*File Name: CheckButton.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年04月11日 星期六 11时10分29秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Item {
    id: checkButton
    width: checkImg.width
    height: checkImg.height

    property bool checked: false
    property bool hovered: false

    signal clicked(bool check)

    Image {
        id: checkImg
        anchors.centerIn: parent
        source: {
            checked ? (hovered ? "qrc:///images/checkbox-check-hover.png" : "qrc:///images/checkbox-check-normal.png")
                    : (hovered ? "qrc:///images/checkbox-uncheck-hover.png" : "qrc:///images/checkbox-uncheck-normal.png")
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: hovered = true
        onExited: hovered = false
        onClicked: {
            checked = !checked
            checkButton.clicked(checked)
        }
    }
}
