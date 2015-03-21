/*************************************************************
*File Name: TrashMainFrame.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月12日 星期四 23时04分23秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Item {
	id: trashPanel
	property var dataModel: ListModel {}
	property int buttomSpacing: 20


	Component.onCompleted: {
		addToModel("1","TrashFile1",510924000)
		addToModel("2","TrashFIle2",9050906432)
		addToModel("3","TrashFIle3",7050906432)
		addToModel("4","TrashFIle4",950906432)
	}

	function addToModel(fileId, fileName, fileSize){
		if (indexOfModel(fileId) == -1){//not in nodel, add it
			dataModel.append({
				"fileId": fileId,
				"fileName": fileName,
				"fileSize": fileSize,
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
