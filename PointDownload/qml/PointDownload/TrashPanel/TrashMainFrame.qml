/*************************************************************
*File Name: TrashMainFrame.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月12日 星期四 23时04分23秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import PDataType 1.0
import Singleton.MainController 1.0

Item {
	id: trashPanel
	property var dataModel: ListModel {}
	property int buttomSpacing: 20

    Connections {
        target: MainController
        onSignalAddDownloadTrashItem: {
            addToModel(itemInfo)
        }
        onSignalAddDownloadingItem: {
            deleteFromModel(itemInfo.fileID)
        }
        onSignalControlResult: {
            if (controlResult.result && controlResult.dlType == PDataType.PDLTypeDownloadTrash){
                switch (controlResult.operaType){
                case PDataType.PCtrlTypeDelete:
                    deleteFromModel(controlResult.fileID)
                    break
                default:
                    break;
                }
            }
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
                "url": dataObj.url,
                "toolType": dataObj.toolType
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
		delegate: TrashFileItem {
			width: parent.width - 20 * 2
			pFileId: fileId
			pFileName: fileName
			pFileSize: fileSize
		}
	}

}
