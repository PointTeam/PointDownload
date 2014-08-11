import QtQuick 2.0

Rectangle {

    property string iconImg:""
    property string title:""

    height: 60
    width: 60
    radius: height
    color: "#464852"

    Image{
        id:itemImg
        source: iconImg
        width: parent.width * 3 / 7
        height: parent.height * 3 / 7
        anchors {top: parent.top;topMargin:parent.height / 7;  horizontalCenter: parent.horizontalCenter}
    }

    Text{
        width: itemImg.width
        height: parent.height / 3
        text: title
        color: "#ffffff"
        font.pixelSize: 11
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors {top: parent.top;topMargin: parent.height * 1 / 2; horizontalCenter: parent.horizontalCenter}
    }
}
