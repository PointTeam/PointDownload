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
    这是RightMainPanel的顶部窗口，由最小化按钮、文件查找框、打开存储路径按钮、
    设置按钮、关闭按钮组成
Others:

History:
*********************************************************************/

import QtQuick 2.0
import QtQuick.Window 2.0
import settingControler 1.0
import Singleton.TopContrl 1.0
import Singleton.PEventFilter 1.0
import Singleton.DLDataConverter 1.0
import Singleton.MonitorClipBoard 1.0
//import "../../ToolTip/CloseTipCreator.js" as CloseTip
import "../../AboutPoint/AboutPoint.js" as AboutPage
import "../../Dropzone/Dropzone.js" as DropzonePage
import "../../Dropzone/SettingWin/SettingWin.js" as SettingScript

Rectangle {
    id: topPanel
    width: parent.width
    height: 50
    color: "#ffffff"

    //连接单例的信号
    Connections {
        target: TopContrl
        onSignalShowMainWindow:{
            mainWindow.show()
            DropzonePage.destroyDropzone()
        }

        onSignalHideMainWindow:{
            mainWindow.hide()
            if (settingCtrl.enableDropzone)
                DropzonePage.showDropzone(topPanel)
        }

        onSignalShowAboutPoint:AboutPage.showAbout(topPanel)
    }
    SettingControler {
        id: settingCtrl

    }

    Rectangle {
        id: spaceRec
        anchors {top: parent.top; horizontalCenter: parent.horizontalCenter}
        width: parent.width
        height: 3
        color: "#eeeff3"
    }

    Rectangle {
        id: splitLine0
        width:1.5
        height: parent.height
        anchors {left: parent.left; }
        color: "#eeeff3"
    }

    BlueButton {
        id: settingButton
        imagePath: "qrc:/images/navigation/style"
        imageWidth: 19
        imageHeigth: 19
        anchors {left: splitLine0.right;verticalCenter: parent.verticalCenter}
        onSBlueButtonClick: {
            if (settingCtrl.getSettingWinShowed())
            {
                SettingScript.destroySettingWin()
                settingCtrl.setSettingWinShowed(false)
            }

            else
            {
                SettingScript.showSettingWin(topPanel,PEventFilter.globalX + 30,PEventFilter.globalY)
                settingCtrl.setSettingWinShowed(true)
            }
        }
    }

    Rectangle {
        id: splitLine1
        width: 1.5
        height: parent.height
        anchors {left: settingButton.right; }
        color: "#eeeff3"
    }

    BlueButton {
        id: quitButton
        imagePath: "qrc:/images/navigation/quit"
        imageWidth: 19
        imageHeigth: 19
        anchors {right: parent.right; verticalCenter: parent.verticalCenter}
        onSBlueButtonClick: {
            settingCtrl.initData()
            if (settingCtrl.exitOnClose)
            {
                TopContrl.destroyAll()
            }
            else
            {
                TopContrl.hideMainWindow()
            }
        }
    }

    Rectangle {
        id: splitLine2
        width: 1.5
        height: parent.height
        anchors {right: quitButton.left;}
        color: "#eeeff3"
    }

    BlueButton {
        id: newTaskButton
        imagePath: "qrc:/images/navigation/plus"
        imageWidth: 19
        imageHeigth: 19
        anchors {right: splitLine2.right; rightMargin: 3; verticalCenter: parent.verticalCenter}
        onSBlueButtonClick: DLDataConverter.controlItem("dl_search","download_redownloed",MonitorClipBoard.tmpURL)
    }

    Rectangle {
        id: splitLine3
        width: 1.5
        height: parent.height
        anchors {right: newTaskButton.left;}
        color: "#eeeff3"
    }

    BlueButton {
        id: folderButton
        imagePath: "qrc:/images/navigation/savefolder"
        imageWidth: 20
        imageHeigth: 20
        anchors {right: splitLine3.right; rightMargin: 3; verticalCenter: parent.verticalCenter}
        onSBlueButtonClick: TopContrl.showSaveFolder()
    }
    Rectangle {
        id: splitLine4
        width: 1.5
        height: parent.height
        anchors {right: folderButton.left;}
        color: "#eeeff3"
    }

    Rectangle {
        id: splitLine5
        width: 1.5
        height: parent.height
        anchors {right: parent.right;}
        color: "#eeeff3"
    }

    Image {
        width: parent.width
        height: 2
        source: "qrc:/images/navigation/right-split"
        anchors.bottom: parent.bottom
    }
}
