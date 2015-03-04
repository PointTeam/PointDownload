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
    这是PointDownload右侧窗口，由上部的主要功能按钮、中部的资源使用面板、下部
    的下载项跟设置面板组成
Others:
Function list:

History:
*********************************************************************/

import QtQuick 2.0
import Singleton.PEventFilter 1.0
import "Top"
import "Middle"
import "Bottom"

Rectangle {
    id: rightMainPanel

    color: "#ecf2f6"

    //顶部功能按钮
    TopPanel {
        id: topMenu
        height: 45
        width: parent.width
        anchors {left:parent.left; top:parent.top}
    }

    //中部资源信面板
    MiddlePanel
    {
        id: infoMenu

        anchors.left: parent.left;
        anchors.top: topMenu.bottom;
        anchors.topMargin: 10;
    }

    TaskListView
    {
        id: taskList;

        height: parent.height - topMenu.height - infoMenu.height - anchors.topMargin
        width: parent.width

        anchors.topMargin: 10;
        anchors.top: infoMenu.bottom
        anchors.bottom: parent.bottom
    }

    function getDownloadListCount(type)
    {
        return taskList.getDownloadListCount(type);
    }

    // 设置当前下载view显示的列表
    function setCurrentPage(page)
    {
        taskList.currentIndex = page;
    }
}
