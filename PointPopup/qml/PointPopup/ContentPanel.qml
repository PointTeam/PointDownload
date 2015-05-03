/*************************************************************
*File Name: ContentPanel.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年04月11日 星期六 11时34分32秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import "./FilePanel"
import "./ControlPanel"

Item {
    width: parent.width
    height: parent.height
    clip: true

    function getFileList(){
        return fileListPage.getSelectedFileList()
    }

    Rectangle {
        id: fileNameListRec
        color: "#ffffff"
        width: parent.width - 24
        height: 200
        anchors {top: parent.top; horizontalCenter: parent.horizontalCenter}
        clip: true

        FileListPage {
            id: fileListPage
            width: parent.width - 20 * 2
            height: parent.height
            anchors.centerIn: parent
        }
    }

    ControlPage {
        color: "#ffffff"
        width: fileNameListRec.width
        height: 190
        anchors {top: fileNameListRec.bottom; topMargin: 12; horizontalCenter: parent.horizontalCenter}
    }

}
