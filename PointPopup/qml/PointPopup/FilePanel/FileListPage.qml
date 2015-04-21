/*************************************************************
*File Name: FileListPage.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年04月11日 星期六 11时11分38秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import Singleton.DataController 1.0

Item {
    id: fileListPage
    width: parent.width
    height: parent.height

    property var fileNameList: []

    function getSelectedFileList(){
        var infoList = new Array()

        for (var i in fileNameList){
            var tmpName = fileNameList[i]
            infoList.push({"fileName": tmpName,
                           "fileType":getValueFromModel(tmpName, "fileType"),
                           "fileSize":getValueFromModel(tmpName, "fileSize")})
        }
        return infoList
    }

    function addInfoItem(fileName, fileType, fileSize){
        fileListView.model.append({"fileName": fileName,
                                  "fileType": fileType,
                                  "fileSize": fileSize
                                  })
        fileNameList.push(fileName)
        allCheckButton.updateCheckState()
    }

    function getValueFromModel(fileName, valueType){
        for (var i = 0; i < fileListView.model.count; i ++){
            if (fileListView.model.get(i).fileName == fileName){
                if (valueType == "fileSize")
                    return fileListView.model.get(i).fileSize
                else if (valueType == "fileType")
                    return fileListView.model.get(i).fileType
            }
        }

        return ""
    }

    function cleanList(){
        fileListView.model.clear()
        fileNameList.splice(0,fileNameList.length);
        allCheckButton.updateCheckState()
    }

    function removeFromList(fileName){
        var index = fileNameList.indexOf(fileName)
        if (index > -1){
            fileNameList.splice(index,1)
        }
        allCheckButton.updateCheckState()
    }

    function addToList(fileName){
        if (fileNameList.indexOf(fileName) == -1)
            fileNameList.push(fileName)
        allCheckButton.updateCheckState()
    }

    Connections{
        target: DataController
        onSignalFileInfoListChanged: {
            cleanList()
            for (var i in infoList){
                var fileName = infoList[i][0];
                var fileType = infoList[i][1];
                var fileSize = infoList[i][2];
                addInfoItem(fileName,fileType,fileSize)
            }
        }
    }

    Item {
        id: topLine
        width: parent.width
        height: 30
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        CheckButton {
            id: allCheckButton
            anchors {left: parent.left; verticalCenter: parent.verticalCenter}

            property bool selectAll: false

            onClicked: {
                selectAll = !check//确保值一定会变化
                selectAll = check
            }

            function updateCheckState(){
                checked = fileNameList.length == fileListView.model.count && fileNameList.length != 0
            }
        }

        Text {
            id: nameText
            width: contentWidth
            height: parent.height
            anchors {left: allCheckButton.right; leftMargin: 20; verticalCenter: parent.verticalCenter}
            verticalAlignment: Text.AlignVCenter
            color: "#b4b4b4"
            text: qsTr("FileName")
        }

        Text {
            id: typeText
            width: 40
            height: parent.height
            anchors {right: sizeText.left; rightMargin: 60; verticalCenter: parent.verticalCenter}
            verticalAlignment: Text.AlignVCenter
            color: "#b4b4b4"
            text: qsTr("FileType")
        }

        Text {
            id: sizeText
            width: 50
            height: parent.height
            anchors {right: parent.right; rightMargin: 30; verticalCenter: parent.verticalCenter}
            verticalAlignment: Text.AlignVCenter
            color: "#b4b4b4"
            text: qsTr("FileSize")
        }
    }

    ListView {
        id: fileListView
        width: parent.width
        height: parent.height
        anchors {top: topLine.bottom; horizontalCenter: parent.horizontalCenter}
        model: ListModel {}
        clip: true
        delegate: FileInfoItem{
            onSelected: {
                if (select){
                    addToList(fileName)
                }
                else{
                    removeFromList(fileName)
                }
            }
        }
    }
}
