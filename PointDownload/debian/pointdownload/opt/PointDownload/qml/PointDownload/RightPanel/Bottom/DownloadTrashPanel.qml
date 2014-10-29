/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Match <2696627729@qq.com>
* Maintainer: Match <2696627729@qq.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

import QtQuick 2.0
import "TrashHandler.js" as TrashScript
import "Item"
import Singleton.DLDataConverter 1.0

Rectangle {
    id: trashPanel
    color: "#3da5ca"

    //连接单例的信号
    Connections {
        target: DLDataConverter
        //当c++中的DownloadingDataSender类触发以下信号时，更改相应属性
        onSFileInfoChange: {
            if (dlType === "dl_trash")
                TrashScript.addNewItem(fileInfo)
        }
    }

    ListModel {
        id: trashItemModel
    }
    Component {
        id: listDelegate

        TrashItem {
            id:delegateItem
            width: trashView.width - 30
            //height: 60

            fileName: tmpName
            iconPath: tmpPath
            fileURL: tmpURL
            fileSize: tmpSize
            dlToolsType:tmpDLToolsType
            // Animate adding and removing of items:

            ListView.onAdd: SequentialAnimation {
                PropertyAction { target: delegateItem; property: "width"; value: 0 }
                NumberAnimation { target: delegateItem; property: "width"; to: trashView.width - 30; duration: 250; easing.type: Easing.InOutQuad }
            }

            ListView.onRemove: SequentialAnimation {
                PropertyAction { target: delegateItem; property: "ListView.delayRemove"; value: true }
                NumberAnimation { target: delegateItem; property: "width"; to: 0; duration: 250; easing.type: Easing.InOutQuad }

                // Make sure delayRemove is set back to false so that the item can be destroyed
                PropertyAction { target: delegateItem; property: "ListView.delayRemove"; value: false }
            }
        }
    }

    ListView {
        id: trashView
        anchors.fill: parent
        model: trashItemModel
        spacing: 4
        delegate: listDelegate
        clip: true
    }

    function moveItem(url)
    {
        TrashScript.removeItem(url)
        //调用C++类做文件处理
//        dCtrl.controlItem("Delete",url,"Trash")
    }

    function addItem(infoList)
    {
        TrashScript.addNewItem(infoList)
    }


    function getFileInfo(url)
    {
        return TrashScript.getFileInfo(url)
    }
    function getListCount()
    {
        return trashItemModel.count
    }
}
