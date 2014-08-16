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
import "DownloadingHandler.js" as DownloadingScript
import "Item"
//import QtQuick.Controls 1.0
import Singleton.DownloadDataSender 1.0

Rectangle {
    id: downloadingPanel
    color: "#3da5ca"

    //连接单例的信号
    Connections {
        target: DownloadDataSender
        //当c++中的DownloadDataSender类触发以下信号时，更改相应属性

        onFileInfoChange: {
            if (DownloadDataSender.downloadType === "dl_downloading")
                DownloadingScript.addNewItem(DownloadDataSender.fileInfo)
        }
        onContrlResultTypeChange: {
            if (DownloadDataSender.downloadType === "dl_downloading")
            {
                if (DownloadDataSender.contrlResultType === "download_priority")
                    sortTimer.start();
            }
        }
        onDownloadSpeedChange: {
            DownloadingScript.updateNetSpeed(DownloadDataSender.downloadURL, DownloadDataSender.downloadSpeed)
        }
        onThunderOfflineSpeedChange:{
            DownloadingScript.updateOfflineSpeed(DownloadDataSender.downloadURL,DownloadDataSender.thunderOfflineSpeed)
        }
        onThunderHightSpeedChange:{
            DownloadingScript.updateHightSpeed(DownloadDataSender.downloadURL,DownloadDataSender.thunderHightSpeed)
        }

        onCompletePercentageChange:{
            if (DownloadDataSender.completePercentage === 100)
            {
                if (DownloadDataSender.downloadURL == "")
                    return;
                //处理qml显示界面
                downloadedPage.addItem(getFileInfo(DownloadDataSender.downloadURL))
                downloadingPage.moveItem(DownloadDataSender.downloadURL)
                //调用C++类做文件处理
                DownloadDataSender.controlItem("dl_downloading","download_finishDownload",DownloadDataSender.downloadURL)
            }
            DownloadingScript.updatePercentage(DownloadDataSender.downloadURL, DownloadDataSender.completePercentage)
        }
        onDownloadStateChange: {
            DownloadingScript.updateFileState(DownloadDataSender.downloadURL, DownloadDataSender.downloadState)
        }
        onFileNameChange:{
            DownloadingScript.updateFileName(DownloadDataSender.downloadURL,DownloadDataSender.fileName);
        }
        onSRefreshDownloadingItem:{
            DownloadingScript.moveItemToTop();
        }
    }

    ListModel {
        id: ingItemModel
    }
    Component {
        id: listDelegate

        DownloadingItem {
            id:delegateItem
            width: ingItemView.width - 30
            //height: 60

            fileName: tmpName
            ingPercentage:tmpPercentage
            iconPath: tmpPath
            fileState: tmpState
            fileURL: tmpURL
            netSpeed: tmpSpeed
            thunderOfflineSpeed: tmpOfflineSpeed
            thunderHightSpeed: tmpHightSpeed
            fileSize: tmpSize
            dlToolsType:tmpDLToolsType
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
        model: ingItemModel
        spacing: 4
        delegate: listDelegate
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
