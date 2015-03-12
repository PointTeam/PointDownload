/*************************************************************
*File Name: FileItem.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月12日 星期四 20时17分22秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Item {
	id: fileItem

	property string pFileId: ""
	property string pFileName: ""
	property double pFileSize: 0
	property var pTaskState
	property var pTaskSpeed
	property var pTaskProgress
}

