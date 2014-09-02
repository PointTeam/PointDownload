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
    这是PointDownload的主窗口，由左边菜单面板跟右边下载与设置面板组成
Others:
Function list:

History:
*********************************************************************/

import QtQuick 2.0
import QtQuick.Window 2.1
import Singleton.PEventFilter 1.0
import Singleton.NormalNotice 1.0

import "Message/NormalNoticePage.js" as NormalNoticePage
//import "AboutPoint/AboutPoint.js" as AboutPage

import "AboutPoint"
import "LeftPanel"
import "RightPanel"

Window {
    id: mainWindow
    flags: Qt.FramelessWindowHint
    visible: true
    color: "#00ffffff"
    title: qsTr(" ")
    width: Screen.width < 1641?820:Screen.width / 2
    height: Screen.height < 800? Screen.height * 4 / 5 : Screen.height * 3 / 5

    property int prex;
    property int nextx;
    property int prey;
    property int nexty;
    property int winx:(Screen.width - width) / 2
    property int winy:(Screen.height - height) / 2
    property string dragIng: "false"
    property int oldX: 0
    property int oldY: 0
    x: winx
    y: winy

    Connections{
        target: NormalNotice

        onSignalShowMessage:{
            NormalNoticePage.showNormalNoticePage(mainUI,title,noticeTitleColor,message)
        }
    }

    Rectangle {
        id:mainUI

        width: parent.width
        height: parent.height
        color: "#00ffffff"


        //左边面板，与父组建高度相同，宽度为固定值
        LeftMainPanel {
            id: leftPanel
            anchors {left: parent.left; top: parent.top;}
            height: parent.height
            width: 120
        }

        //右侧面板，面板分成顶部，中部跟底部三部分
        //顶部是关闭搜索等主要功能按键
        //中部是磁盘使用率等数据
        //底部是下载项的集和跟设置面板
        RightMainPanel {
            id: rightPanel
            anchors {left: leftPanel.right; top:parent.top}
            height: parent.height
            width: parent.width - leftPanel.width
            onMiddlePanelPress: {
                oldX = middleX;
                oldY = middleY;
                dragIng = "true"
            }
            onMiddlePanelRelease: {
                dragIng = "false"
            }
            onMiddlePanelPositionChange: {
                if (dragIng == "true")
                {
                    winx = PEventFilter.globalX- oldX - leftPanel.width
                    winy = PEventFilter.globalY - oldY - 45; //45 = topMenu.height
                }
            }
        }

        MouseArea{
            id:mArea
            anchors {top:parent.top; left: parent.left}
            width: leftPanel.width
            height: leftPanel.width
            hoverEnabled: true

            onPressed:  {
                oldX = mouseX;
                oldY = mouseY;
                dragIng = "true"
                mArea.cursorShape=Qt.DragMoveCursor

            }
            onReleased: {
                dragIng = "false"
                mArea.cursorShape=Qt.ArrowCursor
            }

            onPositionChanged: {
                if (dragIng == "true")
                {
                    winx = PEventFilter.globalX- oldX
                    winy = PEventFilter.globalY - oldY;
                }
            }
        }

        MouseArea {
            id:mArea2
            anchors {bottom: parent.bottom; left: parent.left}
            width: leftPanel.width
            height: leftPanel.height - leftPanel.width - 260//2014.5.18 add
            hoverEnabled: true

            onPressed:  {
                oldX = mouseX;
                oldY = mouseY + leftPanel.width + 260;
                dragIng = "true"
                mArea2.cursorShape=Qt.DragMoveCursor
            }
            onReleased: {
                dragIng = "false"
                mArea2.cursorShape=Qt.ArrowCursor
            }

            onPositionChanged: {
                if (dragIng == "true")
                {
                    winx = PEventFilter.globalX- oldX
                    winy = PEventFilter.globalY - oldY;
                }
            }
        }
    }

}
