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

import QtQuick 2.0
import settingControler 1.0
import "./PopupWin/SliderWinCreater.js" as Tooltip
Rectangle {
    id: settingItem
    width: 300
    height: 30
    color: parent.color

    state: "loseMouse"

    property string typePath: ""
    property string itemType: ""//ThreadCount,MaxJobCount,MaxDSpeed,DSPath
    property string itemName:""
    property string countText: ""
    property string showed:"false"

    SettingControler{
        id:settingCtrl;
    }

    Image {
        id: settingType
        source: typePath;
        width: 22
        height: 22
        anchors {left: parent.left; verticalCenter: parent.verticalCenter}
    }

    Text {
        id: itemText
        text: itemName + countText;
        width: 100
        font.pixelSize: 13
        font.bold: true
        color: "#ffffff"
        height: settingType.height
        anchors {left: settingType.right; leftMargin: 10; top:settingType.top; topMargin: 2}
    }

    Image {
        id: settingButton
        source: "qrc:/images/setting/SettingButton"
        width: 20
        height: 20
        anchors {right: parent.right;verticalCenter: parent.verticalCenter}

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onExited: settingItem.state = "loseMouse"
            onEntered: settingItem.state = "gotMouse"
            onClicked: {
                if (itemType == "DSPath")
                    settingCtrl.selectSavePath("Other");
                else if (itemType == "ThreadCount")
                {
                    if (showed == "false")
                    {
                        createThreadWin();
                    }
                    else
                    {
                        if (Tooltip.close())
                            showed = "false";
                        else
                            createThreadWin();
                    }
                }
                else if (itemType == "MaxJobCount")
                {
                    if (showed == "false")
                    {
                        createJobWin();
                    }
                    else
                    {
                        if (Tooltip.close())
                            showed = "false";
                        else
                            createJobWin();
                    }
                }
                else if (itemType == "MaxDSpeed")
                {
                    if (showed == "false")
                    {
                        createSpeedWin();
                    }
                    else
                    {
                        //如果Tooltip.close()返回false则子窗口已经自我销毁，所以再次点击的时候应该是直接生成子窗口
                        if (Tooltip.close())
                            showed = "false";
                        else
                            createSpeedWin();
                    }
                }
            }
        }
    }

    states:[
        State{
            name: "gotMouse"
            PropertyChanges {target: settingButton; rotation: 180}
        },
        State{
            name: "loseMouse"
            PropertyChanges {target: settingButton; rotation: 0}
        }

    ]

    transitions: [
        Transition {
            from: "*";to: "*"
            PropertyAnimation {
                properties: "rotation"; duration: 700
                easing.type: "OutBounce"
            }
        }
    ]

    function createThreadWin()
    {
        settingCtrl.initData();
        Tooltip.fadeInDelay = 200;
        Tooltip.fadeOutDelay = 200;
        Tooltip.maxCount = 10;
        Tooltip.miniCount = 1;
        Tooltip.currentValue = settingCtrl.defaultThreadCount
        Tooltip.stepSize = 1;
        Tooltip.color = "#ecb752";
        Tooltip.winType = "ThreadCount";
        Tooltip.showTipe(itemText);
        showed = "true"
    }

    function createJobWin()
    {
        settingCtrl.initData();
        Tooltip.fadeInDelay = 200;
        Tooltip.fadeOutDelay = 200;
        Tooltip.maxCount = 20;
        Tooltip.miniCount = 1;
        Tooltip.currentValue = settingCtrl.maxJobCount
        Tooltip.stepSize = 1;
        Tooltip.color = "#f04747";
        Tooltip.winType = "MaxJobCount";
        Tooltip.showTipe(itemText);
        showed = "true"
    }

    function createSpeedWin()
    {
        //重新获取心数据
        settingCtrl.initData();
        Tooltip.fadeInDelay = 200;
        Tooltip.fadeOutDelay = 200;
        Tooltip.maxCount = 200000;
        Tooltip.miniCount = 1;
        Tooltip.currentValue = settingCtrl.maxDownloadSpeed
        Tooltip.stepSize = 100;
        Tooltip.color = "#0db0cf";
        Tooltip.winType = "MaxDSpeed";
        Tooltip.showTipe(itemText);
        showed = "true"
    }
}
