import QtQuick 2.0

Image {
    id:logoutPage

    Image{
        id:thunderIcon
        width: 70
        height: 70

        anchors {top: parent.top;topMargin: 5; horizontalCenter: parent.horizontalCenter}

        source: "qrc:/images/dropzone/thunder64"
    }

    Text{
        id:nameText
        text:xwareSettingPage.getDefaultUserName()
        font.pixelSize: 11
        font.bold: true
        color: "gray"
        visible: parent.visible
        horizontalAlignment: Text.AlignHCenter
        anchors {top: thunderIcon.bottom;topMargin: 5; horizontalCenter: parent.horizontalCenter}
    }
}
