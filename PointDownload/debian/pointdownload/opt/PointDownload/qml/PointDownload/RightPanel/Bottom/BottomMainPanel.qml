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
    所有下载项面板的主面板，被RightListView使用
Others:

History:
**********************************************************************/

import QtQuick 2.0

ListView {
    id:bottomMainPanel
    model: itemModel
    snapMode: ListView.SnapToItem
    orientation: ListView.Vertical
    boundsBehavior: Flickable.StopAtBounds
    flickDeceleration: 5000
    highlightFollowsCurrentItem: true
    highlightMoveDuration:500
//    highlightRangeMode: ListView.StrictlyEnforceRange

    clip: true

    VisualItemModel
    {
        id: itemModel

        //SearchPanel {id: searchPage; height: bottomMainPanel.height; width: bottomMainPanel.width;}
        DownloadingPanel {id: downloadingPage; height: bottomMainPanel.height; width: bottomMainPanel.width;}
        DownloadedPanel {id: downloadedPage; height: bottomMainPanel.height; width: bottomMainPanel.width;}
        DownloadTrashPanel {id: downloadTrashPage; height: bottomMainPanel.height; width: bottomMainPanel.width;}
    }

    // 设置当前需要显示的面板，被RightListView的setDownloadPage方法调用
    function setCurrentPage(page)
    {
        bottomMainPanel.currentIndex = page;
    }

    function refresh()
    {
        currentItem.refresh();
    }

    function getListCountCount(downloadType)
    {
        if (downloadType === "Downloading")
            return downloadingPage.getListCount()
        else if (downloadType === "Downloaded")
            return downloadedPage.getListCount()
        else
            return downloadTrashPage.getListCount()
    }
}
