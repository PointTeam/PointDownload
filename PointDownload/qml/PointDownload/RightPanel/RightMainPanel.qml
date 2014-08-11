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
    这是PointDownload右侧窗口，由上部的主要功能按钮、中部的资源使用面板、下部
    的下载项跟设置面板组成
Others:
Function list:

History:
*********************************************************************/

import QtQuick 2.0
import "Top"
import "Middle"
import "Bottom"
import "../LeftPanel"

Rectangle {
    id: rightMainPanel
    width: 700
    height: parent.height

    color: "#ecf2f6"

    signal middlePanelPress(int middleX,int middleY)
    signal middlePanelRelease()
    signal middlePanelPositionChange()

    //顶部功能按钮
    TopPanel {
        id: topMenu
        height: 45
        width: parent.width
        anchors {left:parent.left; top:parent.top}
    }

    //中部资源信面板
    MiddlePanel {
        id: infoMenu
        y: topMenu.height
        anchors {left: parent.left;}

        MouseArea{
            id:middleMouse
            anchors.fill: parent
            anchors.bottomMargin: 20
            onPressed:  {
                rightMainPanel.middlePanelPress(mouseX,mouseY)
                middleMouse.cursorShape=Qt.DragMoveCursor
            }
            onReleased: {
                rightMainPanel.middlePanelRelease()
                middleMouse.cursorShape=Qt.ArrowCursor
            }

            onPositionChanged: {
                rightMainPanel.middlePanelPositionChange()
            }
        }
    }

    //包括设置面板跟下载项listview的一个总listview
    RightListView {
        id: rightView
        width: parent.width
        height: parent.height - topMenu.height - infoMenu.height
        anchors.top: infoMenu.bottom
        anchors.topMargin: 10
    }

    //在LeftPanel下的navigationBar中只能读取到其父组建中的id，即是main中定义的一些组建id
    //即可读取到main中的rightPanel（此文件），所以可以再通过这个函数来传递动作
    function setDownloadListPage(page)
    {
        rightView.setDownloadPage(page);
    }

    function getDownloadListCount(downloadType)
    {
        return rightView.getDownloadListCount(downloadType)
    }
}
