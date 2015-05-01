/*************************************************************
*File Name: TaskMainFrame.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月12日 星期四 19时51分52秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import PDataType 1.0
import Singleton.MainController 1.0

Item {
    id: taskPanel
	property var dataModel: ListModel {}
	property int buttomSpacing: 20

    Connections {
        target: MainController
        onSignalAddDownloadingItem: {
            print ("Add new task:",itemInfo.fileName, itemInfo.fileTotalSize,"Byte")
            addToModel(itemInfo)
        }
        onSignalTaskItemInfoUpdate: {
            updateDataModel(itemInfo.fileID,itemInfo.taskState,itemInfo.taskDLSpeed,itemInfo.taskProgress / 100)
        }
        onSignalTaskFinished: {
            print ("Task finishied:",fileID)
            deleteFromModel(fileID)
        }
    }

    function getItemCount(){
        return dataModel.count
    }

    function addToModel(dataObj){
        if (indexOfModel(dataObj.fileID) == -1){//not in nodel, add it
			dataModel.append({
                "fileId": dataObj.fileID,
                "fileName": dataObj.fileName,
                "fileSize": dataObj.fileTotalSize,
                "fileSavePath": dataObj.fileSavePath,
                "url": dataObj.url,
                "toolType": dataObj.toolType,
                "taskState": dataObj.taskState,
                "taskSpeed": 0, //Byte/S
                "taskProgress": dataObj.fileTotalSize != undefined ? dataObj.fileReadySize / dataObj.fileTotalSize : 0 //0~1
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
		width: parent.width - 20 * 2
		height: parent.height
		topMargin: 25
		bottomMargin: 25
		leftMargin: 20
		rightMargin: 20
		spacing: 25

		model: dataModel
		delegate: TaskFileItem {
			width: parent.width - 20 * 2
			pFileId: fileId
			pFileName: fileName
			pFileSize: fileSize
			pTaskState: taskState
			pTaskSpeed: taskSpeed
			pTaskProgress: taskProgress
		}
	}

}
