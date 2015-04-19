/*************************************************************
*File Name: SearchInput.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年04月07日 星期二 20时24分42秒
*Description:
*
*************************************************************/
import QtQuick 2.1

FocusScope {
    id: mainScope
    width: parent.width
    height: parent.height
    clip: true
    state: "normal"

    property alias textInput: input
    property alias text: input.text

    signal urlChanged(string url);
//    onFocusChanged: {
//        if (focus){
//            mainScope.state = "focus"
//        }
//        else{
//            mainScope.state = "normal"
//        }
//    }

    Rectangle {
        id: backgroundRec
        width: parent.width
        height: parent.height
        color: "#ffffff"
        border.width: 1
        anchors.fill: parent
    }

    TextInput {
        id: input
        clip: true
        width: parent.width
        height: parent.height
        anchors.fill: parent
        anchors.leftMargin: 8
        anchors.rightMargin: 5
        selectByMouse: true
        color: "#6d6b6b"
        selectionColor: "#66afd6"
        verticalAlignment: TextInput.AlignVCenter
        font.pixelSize: 18
        onTextChanged: mainScope.urlChanged(text)
    }

    Text {
        id: tipText
        clip: true
        width: parent.width
        height: parent.height
        anchors.fill: parent
        anchors.leftMargin: 8
        anchors.rightMargin: 5
        color: "#b4b4b4"
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 18
        text: qsTr("Please fill URL here.")

        opacity: input.text == "" ? 1 : 0

        Behavior on opacity {
            NumberAnimation {duration: 300}
        }
    }

    states:[
        State {
            name: "focus"
            PropertyChanges {target: backgroundRec; border.color: "#6d6b6b";}
        },
        State {
            name: "normal"
            PropertyChanges {target: backgroundRec; border.color: "#ffffff";}
        }
    ]
}
