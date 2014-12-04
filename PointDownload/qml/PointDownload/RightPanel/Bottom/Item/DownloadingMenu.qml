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
    正在下载项的菜单，被DownloadingItem使用，包括暂停，恢复下载、删除等操作
Others:

History:
**********************************************************************/

import QtQuick 2.0
import Singleton.DLDataConverter 1.0
import "../../../ToolTip/MenuTooltipCreator.js" as MenuToolTip

Rectangle {
    id: menuItem

    property int menuLeftMargin: 25
    property string downloadURL: ""
    property string downloadState: ""
    property string offlineSpeed:""
    property string hightSpeed:""

    width: parent.width
    height: 40
    radius: 4
    opacity: 0.8
    color: "#ffffff"
    //连接单例的信号
    Connections {
        target: DLDataConverter
        //当c++中的DLDataConverter类触发以下信号时，更改相应属性
        onSDLStateChange: {
            if (dlURL == downloadURL && (dlState === "download_suspend" ||
                                         dlState === "download_resume"))
            {
                menuSuspend.setDownloadIcon(dlState);
            }
        }
    }


    MenuButton {
        id: menuSuspend
        height: parent.height - 10
        iconPath: downloadState === "dlstate_downloading" ? "qrc:/images/right/suspend"
                                                          : "qrc:/images/right/resume";
        anchors {left: parent.left;leftMargin: menuLeftMargin; verticalCenter: parent.verticalCenter}

        function setDownloadIcon(stat) {
            if (stat === "download_suspend")
                menuSuspend.iconPath = "qrc:/images/right/resume"
            else if (stat === "download_resume")
                menuSuspend.iconPath = "qrc:/images/right/suspend"
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                MenuToolTip.showMenuToolTip(menuSuspend,menuSuspend.iconPath =="qrc:/images/right/suspend"?qsTr("Pause"):qsTr("Resume"))
                parent.opacity = 0.8;
            }
            onExited: {
               MenuToolTip.close();
                parent.opacity = 1;
            }
            onClicked: {
                console.log(menuSuspend.iconPath);
                if (menuSuspend.iconPath === "qrc:/images/right/resume")
                    DLDataConverter.controlItem("dl_downloading","download_resume",downloadURL)
                else if (menuSuspend.iconPath === "qrc:/images/right/suspend")
                    DLDataConverter.controlItem("dl_downloading","download_suspend",downloadURL)
            }
        }
    }

    MenuButton {
        id: menuPriority
        height: parent.height - 10
        iconPath: "qrc:/images/right/priority"
        anchors {left: menuSuspend.right; leftMargin: menuLeftMargin; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                MenuToolTip.showMenuToolTip(menuPriority,qsTr("Priority"))
                parent.opacity = 0.8;
            }
            onExited: {
               MenuToolTip.close();
                parent.opacity = 1;
            }
            onClicked: {
                downloadingPage.moveItemToTop(downloadURL);// 在优先下载时，应该把优先项移动到最前面
                DLDataConverter.controlItem("dl_downloading","download_priority",downloadURL)
                sortTimer.start();
            }
        }
    }
    MenuButton {
        id: menuFolder
        height: parent.height - 10
        iconPath: "qrc:/images/right/folder"
        anchors {left: menuPriority.right; leftMargin: menuLeftMargin; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                MenuToolTip.showMenuToolTip(menuFolder,qsTr("Open Storage Folder"))
                parent.opacity = 0.8;
            }
            onExited: {
               MenuToolTip.close();
                parent.opacity = 1;
            }
            onClicked: DLDataConverter.controlItem("dl_downloading","download_openFolder",downloadURL)
        }
    }
    MenuButton {
        id: menuTrash
        height: parent.height - 10
        iconPath: "qrc:/images/right/trash"
        anchors {left: menuFolder.right; leftMargin: menuLeftMargin; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                MenuToolTip.showMenuToolTip(menuTrash,qsTr("Double Click Will Move To Trash"))
                parent.opacity = 0.8;
            }
            onExited: {
               MenuToolTip.close();
                parent.opacity = 1;
            }
            onDoubleClicked:
            {
                //处理qml显示界面
                downloadTrashPage.addItem(downloadingPage.getFileInfo(downloadURL))
                downloadingPage.moveItem(downloadURL)
                //调用C++类做文件处理
                DLDataConverter.controlItem("dl_downloading","download_trash",downloadURL)
            }
        }
    }
    MenuButton {
        id: menuDelete
        height: parent.height - 10
        iconPath: "qrc:/images/right/delete"
        anchors {left: menuTrash.right; leftMargin: menuLeftMargin; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                MenuToolTip.showMenuToolTip(menuDelete,qsTr("Double Click Will Delete,Including File"))
                parent.opacity = 0.8;
            }
            onExited: {
               MenuToolTip.close();
                parent.opacity = 1;
            }
            onDoubleClicked:
            {
                //处理qml显示界面
                downloadingPage.moveItem(downloadURL)
                //调用C++类做文件处理
                DLDataConverter.controlItem("dl_downloading","download_delete",downloadURL)
            }
        }
    }

    MenuButton{
        id:menuOfflineDownload
        visible: (downloadingItem.dlToolsType == "Xware" || downloadingItem.dlToolsType == "xware")?true:false
        height: parent.height - 10
        iconPath: "qrc:/images/right/offlinedownload"
        anchors {right:offlineDownloadText.left; rightMargin: 6; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                MenuToolTip.showMenuToolTip(menuOfflineDownload,qsTr("Thunder Offline Download"))
                parent.opacity = 0.8;
            }
            onExited: {
               MenuToolTip.close();
                parent.opacity = 1;
            }
            onClicked: DLDataConverter.controlItem("dl_downloading","download_offlineDownload",downloadURL)
        }
    }
    Text{
        id:offlineDownloadText
        text:offlineSpeed
        visible: parent.height == 0?false:true
        font.pixelSize: 11
        color: "#48484b"
        horizontalAlignment: Text.AlignHCenter
        anchors {right:menuHightSpeed.left; rightMargin: 30; verticalCenter: parent.verticalCenter}
    }

    MenuButton{
        id:menuHightSpeed
        visible: (downloadingItem.dlToolsType == "Xware" || downloadingItem.dlToolsType == "xware")?true:false
        height: parent.height - 10
        iconPath: "qrc:/images/right/hightspeed"
        anchors {right: hightSpeedText.left;rightMargin: 6; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                MenuToolTip.showMenuToolTip(menuHightSpeed,qsTr("Thunder High-speed Channel"))
                parent.opacity = 0.8;
            }
            onExited: {
               MenuToolTip.close();
                parent.opacity = 1;
            }
            onClicked: DLDataConverter.controlItem("dl_downloading","download_hightSpeedChannel",downloadURL)
        }
    }
    Text{
        id:hightSpeedText
        text: hightSpeed
        visible: parent.height == 0?false:true
        font.pixelSize: 11
        color: "#48484b"
        horizontalAlignment: Text.AlignHCenter
        anchors {right:parent.right; rightMargin: 30; verticalCenter: parent.verticalCenter}
    }
}
