import QtQuick 2.0



Rectangle{
    color: "#3b5a6f"

    property int stepNum: 0
    property string stepInfo: ""
    property string middleInfo: "You-Get is a video downloader
runs on Python 3.
Project:https://github.com/soimort/you-get"

    TextEdit{
        anchors {top: parent.top;topMargin: 15; left:parent.left; leftMargin: 15;right: parent.right; rightMargin: 15}
        width: parent.width - 30
        height: parent.height - bottomRec.height
        enabled: false
        font.pixelSize: 10
        color: "#cdd7d9"
        text: middleInfo
    }

    Rectangle{
        id:bottomRec

        color: "#373942"
        width: parent.width
        height: 30
        anchors.bottom: parent.bottom

        Rectangle{
            id:stepRec

            color: "#06abc9"
            width: 50
            height: parent.height
            anchors.left: parent.left

            Text{
                id:stepText
                text:"(" + stepNum + "/3)"
                width: 20
                color: "#ffffff"
                font.pixelSize: 11
                height: parent.height
                anchors {left:parent.left; leftMargin: 10; top: parent.top; topMargin: 8}
            }
        }

        Text{
            id:stepInfoText
            text:stepInfo
            width: parent.width - 80
            height: parent.height
            color: "#aaacb7"
            font.pixelSize: 9
            anchors {left: stepRec.right; leftMargin: 15; top:parent.top; topMargin: 10}
        }

        Rectangle{
            id:licenseButton

            color: "#06abc9"
            width: 50
            height: parent.height
            anchors {right: parent.right}

            Text{
                text: qsTr("LICENSE")
                color: "#ffffff"
                font.pixelSize: 10
                anchors {horizontalCenter: parent.horizontalCenter;verticalCenter: parent.verticalCenter}
            }
        }
    }
}
