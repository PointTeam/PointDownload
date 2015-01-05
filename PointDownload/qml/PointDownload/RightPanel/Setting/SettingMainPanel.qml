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

Rectangle {
    width: parent.width
    height: parent.height
    color: "#006f7c"

    SettingItem{
        id:dSPathItem
        typePath: "qrc:/images/setting/DSPath"
        itemName: qsTr("Default Storage  Directory")//"默认下载目录"//
        itemType: "DSPath"
        anchors {horizontalCenter: parent.horizontalCenter;top: parent.top; topMargin: 100}
    }

    SettingItem{
        id:dThreadCount
        typePath: "qrc:/images/setting/ThreadCount"
        itemName: qsTr("Max Thread Count")//"默认最大下载线程数"//
        //ThreadCount,MaxJobCount,MaxDSpeed,DSPath
        itemType: "ThreadCount"
        anchors {horizontalCenter: parent.horizontalCenter;top: dSPathItem.bottom; topMargin: 10}
    }

    SettingItem{
        id:mJobCount
        typePath: "qrc:/images/setting/MJob"
        itemName: qsTr("Max Job Count")//"最大允许同时下载任务数"//
        itemType: "MaxJobCount"
        anchors {horizontalCenter: parent.horizontalCenter; top:dThreadCount.bottom; topMargin: 10}
    }

    SettingItem{
        id:mDownloadSpeed
        typePath: "qrc:/images/setting/MDSpeed"
        itemName: qsTr("Max Download Speed")//"最大允许下载速度"//
        itemType: "MaxDSpeed"
        anchors {horizontalCenter: parent.horizontalCenter; top:mJobCount.bottom; topMargin: 10}
    }
}
