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

import QtQuick 2.0

ListView {
    id:rightListViewPanel
    model: itemModel
    snapMode: ListView.SnapToItem
    orientation: ListView.Vertical
    boundsBehavior: Flickable.StopAtBounds
    flickDeceleration: 5000
    highlightFollowsCurrentItem: true
    highlightMoveDuration:500
    highlightRangeMode: ListView.StrictlyEnforceRange

    clip: true

    VisualItemModel
    {
        id: itemModel
        SoftwarePanel {id: softwarePanel}
        AboutPanel {id: aboutPanel}
        HelpUsPanle {id: helpUsPanel}
    }

    onCurrentItemChanged: {
        switch(rightListViewPanel.currentIndex)
        {
        case 0:
            leftSlider.state = "softwareGetMouse"
            break;
        case 1:
            leftSlider.state = "aboutGetMouse"
            break;
        case 2:
            leftSlider.state = "helpUsGetMouse"
        }
    }

    //被Top中的Topanel中的settingButton按钮的onclick事件调用
    function setCurrentPage(page)
    {
        rightListViewPanel.currentIndex = page;
    }

    function refresh()
    {
        currentItem.refresh();
    }
}
