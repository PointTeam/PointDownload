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

Rectangle {
    color: "#ffffff"
    width: parent.width
    height: parent.height

    FileListPage {
        id: fileListPage
        width: parent.width - 20 * 2
        height: 200
        anchors {top: parent.top; horizontalCenter: parent.horizontalCenter}
        Component.onCompleted: {
            addInfoItem("第七子：降魔之战","Media",123321)
            addInfoItem("TestName2","Media",12332199876)
            addInfoItem("TestName3cccccccccccccccccccccccccccccccccccccccccccccc","Media",833219987)
        }
    }
}
