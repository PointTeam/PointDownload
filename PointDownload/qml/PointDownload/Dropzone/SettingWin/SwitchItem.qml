import QtQuick 2.0

Rectangle {
    id:switchItem

    property string title:""
    property bool itemState:false
    color: "#3b5a6f"

    signal switchValueChanged(int switchState)

    Rectangle{
        width: parent.width - 16
        height: parent.height
        color: "#233a4a"
        radius: 3
        clip: true
        anchors {fill: parent; leftMargin: 8; rightMargin: 8}

        Text {
            id: titleText
            text: title
            color: "#cdd7d9"
            font.pixelSize: 13
            height: 30
            width: 130
            anchors {left:parent.left; leftMargin: 10}
            verticalAlignment: Text.AlignVCenter
        }

        Image{
            id:buttonImg
            source: itemState?"qrc:/images/dropzone/on":"qrc:/images/dropzone/off"
            width: 40
            height: 40
            anchors {right: parent.right;rightMargin: 5; verticalCenter: parent.verticalCenter}

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if (itemState)
                    {
                        buttonImg.source = "qrc:/images/dropzone/off"
                        switchItem.switchValueChanged(false)
                        itemState = false
                    }
                    else
                    {
                        buttonImg.source = "qrc:/images/dropzone/on"
                        switchItem.switchValueChanged(true)
                        itemState = true
                    }
                }
            }
        }
    }
}
