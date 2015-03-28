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
        onTaskInfoChange: TaskListScript.updateTaskInfo(taskInfo);
        onTaskComplete: TaskListScript.completeDownload(taskInfo);
        onTaskMoveToTrash: TaskListScript.moveToTrashDownload(taskInfo);
        onTaskDelete: TaskListScript.deleteDownload(taskInfo);
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
