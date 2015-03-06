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
import "Item"
import "DataFormatHelper.js" as DataFormat

import taskInfo 1.0

Rectangle {
    id: downloadingPanel
    color: "#3da5ca"

    Component {
        id: listDelegate

        DownloadingItem {
            id:delegateItem
            width: ingItemView.width - 30
            //height: 60

            fileName: name
            ingPercentage: percentage.toFixed(2);
            iconPath: iconPath
            fileState: state
            fileURL: rawUrl
            netSpeed: "0"
            thunderOfflineSpeed: ""
            thunderHightSpeed: ""
            fileSize: DataFormat.formatFileSize(size);
            dlToolsType: toolType
            // Animate adding and removing of items:

            ListView.onAdd: SequentialAnimation {
                PropertyAction { target: delegateItem; property: "width"; value: 0 }
                NumberAnimation { target: delegateItem; property: "width"; to: ingItemView.width - 30; duration: 250; easing.type: Easing.InOutQuad }
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
        id: ingItemView
        anchors.fill: parent
        model: downloadingModel
        spacing: 4
        delegate: listDelegate
        clip: true
    }

    //启动排序的计时器
    Timer {
        id:sortTimer
        interval: 1500;
        running: false;
        repeat: false
        onTriggered:{
            moveItemToTop()
        }
    }
    function moveItem(url)
    {
        DownloadingScript.removeItem(url)
    }

    function moveItemToTop() //在优先下载时，应该把优先项移动到最前面
    {
        DownloadingScript.moveItemToTop()
    }

    function addItem(infoList)
    {
        DownloadingScript.addNewItem(infoList)
    }

    function getFileInfo(url)
    {
        return DownloadingScript.getFileInfo(url)
    }

    function getListCount()
    {
        return ingItemModel.count
    }
}
