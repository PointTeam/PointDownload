/*************************************************************
*File Name: TaskMainFrame.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月12日 星期四 19时51分52秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import "../Widgets"

Item {
	id: taskPanel
	//DataType::TaskStateDownloading == 0
	//DataType::TaskStateSuspend == 1
	//DataType::TaskStateBlock == 2
	//DataType::TaskStateError == 3
	property var dataModel: ListModel {}
	property int buttomSpacing: 20

	function addToModel(fileId, fileName, fileSize){
		if (indexOfModel(fileId) == -1){//not in nodel, add it
			dataModel.append({
				"fileId": fileId,
				"fileName": fileName,
				"fileSize": fileSize,
				"taskState": 1,
				"taskSpeed": 1024, //Byte/S
				"taskProgress": 0 //100%
			})
		}
	}

	function deleteFromModel(fileId){
		var tmpIndex = indexOfModel(fileId)
		if (tmpIndex != -1){
			print ("==>[Info] Remove item from data model...",tmpIndex,fileId)
			dataModel.remove(tmpIndex)
		}
		else
			print ("==>[Warning] Delete data,id not exist in model!")
	}

	function updateDataModel(fileId, taskState, taskSpeed, taskProgress){
		var tmpIndex = indexOfModel(fileId)
		if (tmpIndex != -1){
			dataModel.set(tmpIndex,{
				"taskState": taskState,
				"taskSpeed": taskSpeed,
				"taskProgress": taskProgress
			})
		}
		else
			print ("==>[Warning] Update data,id not exist in model!")

	}

	function indexOfModel(fileId) {
		for (var i = 0; i < dataModel.count; i ++){
			if (dataModel.get(i).fileId == fileId){
				return i
			}
		}
		return -1
	}

	ListView {
		anchors.top: parent.top
		anchors.horizontalCenter: parent.horizontalCenter
		width: parent.width
		height: parent.height

		model: dataModel
		delegate: FileItem {
			pFileId: fileId
			pFileName: fileName
			pFileSize: fileSize
			pTaskState: taskState
			pTaskSpeed: taskSpeed
			pTaskProgress: taskProgress
		}
	}

	Rectangle {
		color: "#444444"
		width: parent.width
		height: parent.height / 2
		anchors.centerIn: parent
	}
}
