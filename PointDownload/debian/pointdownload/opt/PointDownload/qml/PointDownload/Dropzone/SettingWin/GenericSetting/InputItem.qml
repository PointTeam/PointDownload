import QtQuick 2.0

Rectangle {
    id:inputItem

    property string title:""
    property int buttonValue: 1
    property int maxValue: 1
    property int minValue: 0

    color: "#3b5a6f"

    signal valueChanged(int value)

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

        Rectangle{
            id:valueButton
            color: "#44a1f8"
            width: 45
            height: 20
            radius: 2
            anchors {right: parent.right;rightMargin: 5;top: parent.top; topMargin: 5}

            Text{
                id:valueText
                width: parent.width
                height: parent.height
                text: buttonValue
                color: "#ffffff"
                font.pixelSize: 12
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        if (valueRec.width == 0)
                            valueText.text = qsTr("Change")
                    }
                    onExited: {
                        if (valueRec.width == 0)
                            valueText.text = buttonValue
                    }

                    onClicked: {
                        if (valueRec.width != 0)
                        {
                            if (valueInput.text == "")
                                return
                            valueText.text = valueInput.text
                            inputItem.valueChanged(valueInput.text)
                            valueRec.width = 0
                        }
                        else
                        {
                            valueText.text = qsTr("Apply")
                            valueRec.width = 70
                        }
                    }
                }
            }

        }

        Rectangle{
            id:valueRec
            anchors {right: valueButton.left; top: valueButton.top}
            color: "#ffffff"
            width: 0
            clip: true
            height: valueButton.height

            TextInput{
                id:valueInput
                width: parent.width
                height: parent.height

                text:buttonValue
                font.pixelSize: 14
                selectByMouse: true
                color: "#596679"
                selectionColor: "#488bc5"
                validator: IntValidator{bottom: minValue; top: maxValue;}

                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                anchors.fill: parent
            }

            Behavior on width {
                NumberAnimation{properties: "width"; duration: 200;easing.type: Easing.InOutBack }
            }
        }
    }
}
