/*************************************************************
*File Name: SearchBar.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年04月07日 星期二 20时15分49秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import Singleton.DataController 1.0
import PDataType 1.0

Item {
    id: searchItem
    width: parent.width
    height: parent.height

    function getSelectedToolType(){
        return toolsComboBox.getSelectedTool()
    }

    Connections{
        target: DataController
        onSignalReceiveNewURL:{
            searchInput.text = url
        }
        onSignalSupportToolsListChanged: {
            toolsComboBox.toolsList = toolsList
        }
        onSignalFileInfoListChanged: {
            analyzeButton.changeToNormalState()
        }
    }

    SearchInput {
        id: searchInput
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width - toolsComboBox.width - analyzeButton.width
        height: parent.height
        onUrlChanged: {
            DataController.getSupportToolsList(url.trim())
            readyForDownload = false
            analyzeButton.changeToNormalState()
        }
    }

    ToolsComboBox {
        id: toolsComboBox
        anchors.right: analyzeButton.left
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width / 6
        height: parent.height
    }

    AnalyzeButton {
        id: analyzeButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width / 5
        height: parent.height
        onEntered: quitImg.opacity = 1
        onExited: delayHideTimer.start()
        onDoAnalyze: {
            DataController.analyzeURL(searchInput.text.trim())
        }
    }

    Image {
        id: quitImg
        opacity: 0
        anchors.top: parent.top
        anchors.right: parent.right
        source: "qrc:///images/quit-normal.png"

        Behavior on opacity {
            NumberAnimation {duration: 200}
        }

        Timer {
            id: delayHideTimer
            interval: 200
            onTriggered: quitImg.opacity = 0
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                delayHideTimer.stop()
                opacity = 1
                quitImg.source = "qrc:///images/quit-hover.png"
            }
            onExited: {
                opacity = 0
                quitImg.source = "qrc:///images/quit-normal.png"
            }

            onClicked: {
                Qt.quit()
            }
        }
    }
}
