/***********************************************************************
*PointDownload
*Copyright (C) 2014~2015  PointTeam
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
/*******************************************************************
Date:   2014.3.20~
Description:
    所有下载项面板的主面板，被RightListView使用
Others:

History:
**********************************************************************/

import QtQuick 2.0
import Singleton.DLDataConverter 1.0

import "../Bottom"
import "TaskListHandler.js" as TaskListScript

ListView {
    id: taskList
    model: itemModel
    clip: true
    highlightFollowsCurrentItem: true
    flickDeceleration: 5000
    highlightMoveDuration:500
    highlightRangeMode: ListView.StrictlyEnforceRange
    // ListView.SnapToItem 会导致下载列表初始显示不正确
    //snapMode: ListView.SnapToItem
    orientation: ListView.Vertical
    boundsBehavior: Flickable.StopAtBounds

    VisualItemModel
    {
        id: itemModel;

        DownloadingPanel {
            width: taskList.width;
            height: taskList.height;

            ListModel {id: downloadingModel;}
        }

        DownloadedPanel {
            width: taskList.width;
            height: taskList.height;

            ListModel {id: downloadedModel;}
        }

        DownloadTrashPanel {
            width: taskList.width;
            height: taskList.height;

            ListModel {id: trashModel;}
        }
    }

    //连接单例的信号
    Connections {
        target: DLDataConverter

        onTaskAdded: TaskListScript.addNewTask(taskInfo);

//        onSDLSpeedChange: {
//            DownloadingScript.updateNetSpeed(dlURL, dlSpeed)
//        }
//        onSThunderOfflineSpeedChange:{
//            DownloadingScript.updateOfflineSpeed(dlURL, offlineSpeed)
//        }
//        onSThunderHightSpeedChange:{
//            DownloadingScript.updateHightSpeed(dlURL,hightSpeed)
//        }
//        onSDLStateChange: {
//            DownloadingScript.updateFileState(dlURL, dlState)
//        }
//        onSFileNameChange:{
//            if (dlType == "dl_downloading")
//            DownloadingScript.updateFileName(dlURL,fileName);
//        }
//        onSRefreshDownloadingItem:{
//            DownloadingScript.moveItemToTop();
//        }
//        onSDLProgressChange:{
//            console.log('asd');
//            // 这里可能存在精度问题导致永远不会达到 100
//            // 判断下载完成不应该简单以百分比确定因为有时文件总大小不可获取
//            if (progress >= 99.99)
//            {
//                if (dlURL == "")
//                    return;
//                //处理qml显示界面
//                downloadedPage.addItem(getFileInfo(dlURL))
//                downloadingPage.moveItem(dlURL)
//            }

//            // 这里有点问题 不能显示 xx.x0% 或者 xx.00%这样的数值 因为底层的数据格式问题
//            DownloadingScript.updatePercentage(dlURL, Number(Number(progress).toFixed(2)));
//        }
//        onSControlFeedback: {

//        }
    }

    function getDownloadListCount(downloadType)
    {
        if (downloadType === "Downloading")
            return downloadingModel.count
        else if (downloadType === "Downloaded")
            return downloadedModel.count
        else
            return trashModel.count
    }
}
