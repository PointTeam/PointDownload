import QtQuick 2.0

Rectangle{
    id:settingMainItem

    property string itemTitle:""
    property string enableButtonIcon:""

    Image{
        id:settingItemBackImg
        width: parent.width
        height: parent.height
        source: "qrc:/images/dropzone/itemback"
        anchors {top: parent.top}

        Text{
            id:itemTitleText
            text:itemTitle
            width: 50
            height: 40
            color: "#535456"
            anchors {left: parent.left;leftMargin: 15; top: parent.top; topMargin: 13}
        }

        Image{
            id:buttonImg
            width: 40
            height: 40
            source: enableButtonIcon
            anchors {right: parent.right; rightMargin: 5; top:parent.top}
        }

        MouseArea{
            id:itemMouse
            anchors.fill: parent
            anchors.rightMargin: 40
            hoverEnabled: true
            onEntered: itemTitleText.color = "#26282c"
            onExited: itemTitleText.color = "#535456"
        }
    }
}
