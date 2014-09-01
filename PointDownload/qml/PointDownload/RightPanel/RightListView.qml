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
/*******************************************************************
Date:   2014.3.20~
Description:
    这是RightMainPanel的下部窗口，由下载项面板组成的BottomMainPanel跟设置面板
    SettingMainPanel组成
Others:
Function list:

History:
*********************************************************************/
import QtQuick 2.0
import "Setting"
import "Bottom"

ListView {
    id:rightListViewPanel
    model: itemModel
    snapMode: ListView.SnapToItem
    orientation: ListView.Horizontal
    boundsBehavior: Flickable.StopAtBounds
    flickDeceleration: 5000
    highlightFollowsCurrentItem: true
    highlightMoveDuration:500
    highlightRangeMode: ListView.StrictlyEnforceRange
    currentIndex: 1

    clip: true

    VisualItemModel
    {
        id: itemModel
//        SettingMainPanel {id: settingPanel; height: rightListViewPanel.height; width: rightListViewPanel.width;}
        BottomMainPanel {id: downloadListPanel;width: rightListViewPanel.width;height: rightListViewPanel.height;}
    }

    //被Top中的Topanel中的settingButton按钮的onclick事件调用
    function setCurrentPage(page)
    {
        rightListViewPanel.currentIndex = page;
    }

    //被RightMainanel中的setDownloadListPage函数调用
    function setDownloadPage(page)
    {
       downloadListPanel.setCurrentPage(page)
    }

    function refresh()
    {
        currentItem.refresh();
    }

    function getDownloadListCount(downloadType)
    {
        return downloadListPanel.getListCountCount(downloadType)
    }
}
