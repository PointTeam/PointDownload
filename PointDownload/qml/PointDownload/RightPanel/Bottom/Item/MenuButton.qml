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
    DownloadingMenu的单个菜单按钮组件
Others:

History:
**********************************************************************/
import QtQuick 2.0

Rectangle {

    id: menuButton

    property string iconPath: ""

    width: 30
    height: 30
    radius: 4
    color: "#32738e"

    Image {
        source: iconPath
        height: parent.width -10
        width: parent.height - 10
        anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: parent.opacity = 0.6
        onExited: parent.opacity = 1
        onPressed: parent.opacity = 1
        onReleased: parent.opacity = 0.6
    }
}
