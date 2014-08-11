import QtQuick 2.0
import Singleton.TopContrl 1.0

Rectangle {
    width: 100
    height: 62
    color: "#3b5a6f"

    HelpItem{
        id:aboutItem
        iconImg: "qrc:/images/dropzone/about"
        title: qsTr("About")
        width: 60
        height: 60
        anchors {left: parent.left; leftMargin: 10; top:parent.top;topMargin: 10}
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: aboutItem.color = "#dd5c07"
            onExited: aboutItem.color = "#464852"
            onClicked: {
                TopContrl.showAboutWindow()
            }
        }
    }
    HelpItem{
        id:checkUpdateItem
        iconImg: "qrc:/images/dropzone/checkupdate"
        title: qsTr("Update")
        width: 60
        height: 60
        anchors {left: aboutItem.right; leftMargin: 20; top:parent.top;topMargin: 10}
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: checkUpdateItem.color = "#dd5c07"
            onExited: checkUpdateItem.color = "#464852"
            onClicked: {
                TopContrl.checkUpdate()
            }
        }
    }
    HelpItem{
        id:skillsItem
        iconImg: "qrc:/images/dropzone/skills"
        title: qsTr("Skills")
        width: 60
        height: 60
        anchors {right: parent.right; rightMargin: 10; top:parent.top;topMargin: 10}
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: skillsItem.color = "#dd5c07"
            onExited: skillsItem.color = "#464852"
            onClicked: {

            }
        }
    }
}
