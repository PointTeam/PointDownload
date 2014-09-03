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


    BlueButton {
        id: smallerButton
        imagePath: "qrc:/images/navigation/smaller"
        anchors {left: parent.left; leftMargin: 5; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            onClicked: DLDataConverter.controlItem("dl_search","download_redownloed",MonitorClipBoard.tmpURL)
        }
    }

    Rectangle {
        id: splitLine1
        width: 2
        height: parent.height
        anchors {left: smallerButton.right; leftMargin: 5;}
        color: "#eeeff3"
    }

//    Image {
//        id: searchImg
//        source: "qrc:/images/navigation/search"
//        anchors {left: splitLine1.right; leftMargin: 4; verticalCenter: parent.verticalCenter}
//    }

//    InputBox {
//        id: searchBox
//        boxWidth: 200
//        boxHeigth: parent.height
//        anchors {left: searchImg.right; leftMargin: 5; verticalCenter: parent.verticalCenter; right: splitLine4.left}
//    }


    BlueButton {
        id: quitButton
        imagePath: "qrc:/images/navigation/quit"
        imageWidth: 19
        imageHeigth: 19
        anchors {right: parent.right;/* rightMargin: 13;*/ verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
//            onClicked: {
//                CloseTip.fadeInDelay = 200;
//                CloseTip.fadeOutDelay = 200;
////                CloseTip.tip = "";
//                CloseTip.showTipe(infoMenu);
//            }

            onClicked: {
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
    }

    Rectangle {
        id: splitLine2
        width: 1.5
        height: parent.height
        anchors {right: quitButton.left; /*rightMargin: 10;*/}
        color: "#eeeff3"
    }

    BlueButton {
        id: settingButton
        imagePath: "qrc:/images/navigation/style"
        imageWidth: 19
        imageHeigth: 19
        anchors {right: splitLine2.right; rightMargin: 3; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            onClicked: {
                SettingScript.showSettingWin(topPanel,PEventFilter.globalX,PEventFilter.globalY)
            }
        }
    }

    Rectangle {
        id: splitLine3
        width: 1.5
        height: parent.height
        anchors {right: settingButton.left;/* rightMargin: 10;*/}
        color: "#eeeff3"
    }

    BlueButton {
        id: folderButton
        imagePath: "qrc:/images/navigation/savefolder"
        imageWidth: 20
        imageHeigth: 20
        anchors {right: splitLine3.right; rightMargin: 3; verticalCenter: parent.verticalCenter}
        MouseArea {
            anchors.fill: parent
            onClicked: TopContrl.showSaveFolder()
        }
    }
    Rectangle {
        id: splitLine4
        width: 1.5
        height: parent.height
        anchors {right: folderButton.left;/* rightMargin: 10;*/}
        color: "#eeeff3"
    }
    Rectangle {
        id: splitLine5
        width: 1.5
        height: parent.height
        anchors {right: parent.right;/* rightMargin: 10;*/}
        color: "#eeeff3"
    }

    Image {
        width: parent.width
        height: 2
        source: "qrc:/images/navigation/right-split"
        anchors.bottom: parent.bottom
    }
}
