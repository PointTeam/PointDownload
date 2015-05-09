/*************************************************************
*File Name: DoneMainFrame.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月12日 星期四 23时03分41秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import PDataType 1.0
import Singleton.MainController 1.0

Item {
	id: donePanel
	property var dataModel: ListModel {}
	property int buttomSpacing: 20

    Connections {
        target: MainController
        onSignalAddDownloadedItem: {
            addToModel(itemInfo)
        }
        onSignalAddDownloadingItem: {
            deleteFromModel(itemInfo.fileID)
        }
        onSignalControlResult: {
            if (controlResult.result && controlResult.dlType == PDataType.PDLTypeDownloaded){
                switch (controlResult.operaType){
                case PDataType.PCtrlTypeDelete:
                case PDataType.PCtrlTypeTrash:
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
                "fileSavePath": dataObj.fileSavePath,
                "fileExist": dataObj.fileExist,
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
        width: parent.width
		height: parent.height
		topMargin: 25
		bottomMargin: 25
        leftMargin: 40
		rightMargin: 20
		spacing: 25

		model: dataModel
		delegate: DoneFileItem {
            id: doneFileItem
            width: parent.width
			pFileId: fileId
			pFileName: fileName
			pFileSize: fileSize

            ListView.onAdd: SequentialAnimation {
                PropertyAction { target: doneFileItem; property: "opacity"; value: 0 }
                NumberAnimation { target: doneFileItem; property: "opacity"; to: 1 ; duration: 260; easing.type: Easing.InOutQuad }
            }

            ListView.onRemove: SequentialAnimation {
                PropertyAction { target: doneFileItem; property: "ListView.delayRemove"; value: true }
                NumberAnimation { target: doneFileItem; property: "opacity"; to: 0; duration: 260; easing.type: Easing.InOutQuad }
                // Make sure delayRemove is set back to false so that the item can be destroyed
                PropertyAction { target: doneFileItem; property: "ListView.delayRemove"; value: false }
            }
		}
	}
}
