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
    这是PointDownload的主窗口，由左边菜单面板跟右边下载与设置面板组成
Others:
Function list:

History:
*********************************************************************/

import QtQuick 2.0
import QtQuick.Window 2.1
import Singleton.PEventFilter 1.0
import Singleton.NormalNotice 1.0
import Singleton.TopContrl 1.0

import settingControler 1.0

import "AboutPoint/AboutPoint.js" as AboutPage
import "Dropzone/Dropzone.js" as DropzonePage
import "Message/NormalNoticePage.js" as NormalNoticePage
import "Dropzone/SettingWin/SettingWin.js" as SettingScript

import "AboutPoint"
import "LeftPanel"
import "RightPanel"

Window {
    id: mainWindow
    flags: Qt.FramelessWindowHint
    visible: true
    color: "#00ffffff"
    title: qsTr("PointDownload")
    width: Screen.width < 1641?820:Screen.width / 2
    height: Screen.height < 800? Screen.height * 4 / 5 - 50: Screen.height * 3 / 5 - 30

    property int prex;
    property int nextx;
    property int prey;
    property int nexty;
    property int winx:(Screen.width - width) / 2
    property int winy:(Screen.height - height) / 2

    property bool dragIng: false
    property int tmpX: 0
    property int tmpY: 0
    x: winx
    y: winy

    //连接单例的信号
    Connections {
        target: TopContrl;
        onSignalShowMainWindow: mainWindow_show();
        onSignalHideMainWindow: mainWindow_hide();
        onSignalShowAboutPoint: mainWindow_showAbout();
    }

    Connections{
        target: NormalNotice;
        onSignalShowMessage: NormalNoticePage.showNormalNoticePage(undefined, title, noticeTitleColor, message);
    }

    SettingControler {id: settingCtrl}

    Rectangle {
        id:mainUI

        width: mainWindow.width;
        height: mainWindow.height;

        color: "#00ffffff"

        //左边面板，与父组建高度相同，宽度为固定值
        LeftMainPanel {
            id: leftPanel
            anchors {left: parent.left; top: parent.top;}
            height: mainWindow.height
            width: 120
        }

        //右侧面板，面板分成顶部，中部跟底部三部分
        //顶部是关闭搜索等主要功能按键
        //中部是磁盘使用率等数据
        //底部是下载项的集和跟设置面板
        RightMainPanel {
            id: rightPanel
            anchors.left: leftPanel.right;
            anchors.top: mainWindow.top;
            anchors.right: mainWindow.right;
            anchors.bottom: mainWindow.bottom;

            height: mainWindow.height;
            width: mainWindow.width - 120;
        }

        MouseArea{
            id:mArea
            anchors {top:parent.top; left: parent.left}
            width: leftPanel.width
            height: leftPanel.width / 3
            hoverEnabled: true

            onPositionChanged: mainWindowDrag_changed(mouseX, mouseY);
            onPressed: {mainWindowDrag_pressed(mouseX, mouseY); cursorShape = Qt.DragMoveCursor;}
            onReleased: {mainWindowDrag_released(); cursorShape = Qt.ArrowCursor;}
        }

        MouseArea {
            id:mArea2
            anchors {bottom: parent.bottom; left: parent.left}
            width: leftPanel.width
            height: leftPanel.height - leftPanel.width / 3 - 280//2014.5.18 add
            hoverEnabled: true

            onPositionChanged: mainWindowDrag_changed(mouseX, mouseY);
            onPressed: {mainWindowDrag_pressed(mouseX, mouseY); cursorShape = Qt.DragMoveCursor;}
            onReleased: {mainWindowDrag_released(); cursorShape = Qt.ArrowCursor;}
        }
    }

    function mainWindow_destroy()
    {
        TopContrl.destroyAll();
    }

    function mainWindow_showAbout()
    {
        AboutPage.showAbout(this);
    }

    function mainWindow_hide()
    {
        mainWindow.hide();
        mainWindow.flags |= Qt.ToolTip;

        if (settingCtrl.enableDropzone)
            DropzonePage.showDropzone(this);
    }

    function mainWindow_show()
    {
        mainWindow.show();
        mainWindow.flags &= ~Qt.ToolTip;

        DropzonePage.destroyDropzone();
    }

    function mainWindowDrag_changed(mouseX, mouseY)
    {
        if (dragIng !== true)
            return;

        x += mouseX - tmpX;
        y += mouseY - tmpY;
    }

    function mainWindowDrag_released()
    {
        dragIng = false;
    }

    function mainWindowDrag_pressed(mouseX, mouseY)
    {
        tmpX = mouseX;
        tmpY = mouseY;

        dragIng = true
    }
}
