/*************************************************************
*File Name: FileInfoItem.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年04月11日 星期六 11时10分52秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Item {
    id: fileInfoItem
    width: parent.width
    height: 30
    clip: true

    property bool all_checked: allCheckButton.selectAll
    property string file_name: fileName
    property string file_type: fileType
    property real file_size: fileSize//byte

    onAll_checkedChanged: {
        if (all_checked){
            checkButton.checked = true
        }
        else{
            checkButton.checked = false
        }
    }

    function getSizeWithUnit(){
        if (file_size > 1024 * 1024 * 1024){
            return (file_size / (1024 * 1024 * 1024)).toFixed(2) + " GB"
        }
        else if (file_size > 1024 * 1024){
            return (file_size / (1024 * 1024)).toFixed(2) + " MB"
        }
        else if (file_size > 1024){
            return (file_size / 1024).toFixed(2) + " KB"
        }
        else
            return file_size + " B"
    }

    signal selected(bool select, string fileName)

    CheckButton {
        id: checkButton
        checked: true
        anchors {left: parent.left; verticalCenter: parent.verticalCenter}
        onClicked: {
            fileInfoItem.selected(check, file_name)
        }
        onCheckedChanged: fileInfoItem.selected(checked, file_name)
    }


    TextInput {
        id: nameText
        clip: true
        selectByMouse: true
        selectionColor: "#66afd6"
        width: parent.width - 260
        height: parent.height
        anchors {left: checkButton.right; leftMargin: 20; verticalCenter: parent.verticalCenter}
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        color: "#b4b4b4"
        text: file_name
    }

    Text {
        id: typeText
        width: 40
        height: parent.height
        anchors {right: sizeText.left; rightMargin: 60; verticalCenter: parent.verticalCenter}
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        color: "#b4b4b4"
        text: file_type
    }

    Text {
        id: sizeText
        width: 50
        height: parent.height
        anchors {right: parent.right; rightMargin: 30; verticalCenter: parent.verticalCenter}
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        color: "#b4b4b4"
        text: getSizeWithUnit()
    }
}
