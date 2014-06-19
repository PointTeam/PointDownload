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
import Singleton.DownloadDataSender 1.0
import "../../../ToolTip/ToolTipCreator.js" as Tooltip

Rectangle {
    id: menuItem

    property int menuLeftMargin: 25
    property string downloadURL: ""
    property string downloadState: ""

    width: parent.width
    height: 40
    radius: 4
    opacity: 0.8
    color: "#ffffff"

    //        download_suspend,
    //        download_resume,
    //        download_redownload,
    //        download_priority,
    //        download_trash,
    //        download_delete,
    //        download_openFolder

    MenuButton {
        id: menuSuspend
        height: parent.height - 10
        iconPath: downloadState === "Downloading"? "qrc:/images/right/suspend" :
                                                              "qrc:/images/right/resume";
        anchors {left: parent.left;leftMargin: menuLeftMargin; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                Tooltip.fadeInDelay = 200;
                Tooltip.fadeOutDelay = 200;
                Tooltip.tip = menuSuspend.iconPath =="qrc:/images/right/suspend"?qsTr("Pause"):qsTr("Resume");
                Tooltip.showTipe(menuSuspend);
                parent.opacity = 0.8;
            }
            onExited: {
               Tooltip.close();
                parent.opacity = 1;
            }
            onClicked: {
                if (parent.iconPath === "qrc:/images/right/suspend")
                {
                    parent.iconPath = "qrc:/images/right/resume"
                    DownloadDataSender.controlItem("dl_downloading","download_suspend",downloadURL)
                }
                else
                {
                    parent.iconPath = "qrc:/images/right/suspend"
                    DownloadDataSender.controlItem("dl_downloading","download_resume",downloadURL)
                }
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
                Tooltip.fadeInDelay = 200;
                Tooltip.fadeOutDelay = 200;
                Tooltip.tip = qsTr("Priority")//"优先下载";
                Tooltip.showTipe(menuPriority);
                parent.opacity = 0.8;
            }
            onExited: {
               Tooltip.close();
                parent.opacity = 1;
            }
            onClicked: {
                downloadingPage.moveItemToTop(downloadURL);// 在优先下载时，应该把优先项移动到最前面
                DownloadDataSender.controlItem("dl_downloading","download_priority",downloadURL)
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
                Tooltip.fadeInDelay = 200;
                Tooltip.fadeOutDelay = 200;
                Tooltip.tip = qsTr("Open Storage Folder")//"打开存放目录";
                Tooltip.showTipe(menuFolder);
                parent.opacity = 0.8;
            }
            onExited: {
               Tooltip.close();
                parent.opacity = 1;
            }
            onClicked: DownloadDataSender.controlItem("dl_downloading","download_openFolder",downloadURL)
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
                Tooltip.fadeInDelay = 200;
                Tooltip.fadeOutDelay = 200;
                Tooltip.tip = qsTr("Double Click Will Move To Trash")//"双击移动到回收站";
                Tooltip.showTipe(menuTrash);
                parent.opacity = 0.8;
            }
            onExited: {
               Tooltip.close();
                parent.opacity = 1;
            }
            onDoubleClicked:
            {
                //处理qml显示界面
                downloadTrashPage.addItem(downloadingPage.getFileInfo(downloadURL))
                downloadingPage.moveItem(downloadURL)
                //调用C++类做文件处理
                DownloadDataSender.controlItem("dl_downloading","download_trash",downloadURL)
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
                Tooltip.fadeInDelay = 200;
                Tooltip.fadeOutDelay = 200;
                Tooltip.tip = qsTr("Double Click Will Delete,Including File")//"双击删除，包括文件";
                Tooltip.showTipe(menuDelete);
                parent.opacity = 0.8;
            }
            onExited: {
               Tooltip.close();
                parent.opacity = 1;
            }
            onDoubleClicked:
            {
                //处理qml显示界面
                downloadingPage.moveItem(downloadURL)
                //调用C++类做文件处理
                DownloadDataSender.controlItem("dl_downloading","download_delete",downloadURL)
            }
        }
    }
}
