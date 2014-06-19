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
Rectangle {
    id: shortcutBar

    width: parent.width

    SettingControler{id:settingCtrl}

    ShortcutButton {
        id: beepButtom
        height: 20
        buttonText: qsTr("Tone")//"完成提示音"//
        iconSource: settingCtrl.beepEnable == "true"?"qrc:/images/navigation/Bbluechecked":"qrc:/images/navigation/Bbluenone"
        anchors {top:parent.top; topMargin: 12}

        MouseArea {
            id: beepMouse
            anchors.fill: parent
            onClicked: {
                if (beepButtom.iconSource == "qrc:/images/navigation/Bbluenone")
                {
                    settingCtrl.updateBeep("true")
                    beepButtom.iconSource = "qrc:/images/navigation/Bbluechecked"
                }
                else
                {
                    settingCtrl.updateBeep("false")
                    beepButtom.iconSource = "qrc:/images/navigation/Bbluenone"
                }
            }
        }
    }

    ShortcutButton {
        id: closeExitButton
        height: 20
        buttonText: qsTr("C&Q")//"关闭立即退出"//
        iconSource: settingCtrl.exitOnClose == "true"?"qrc:/images/navigation/Byellowchecked":"qrc:/images/navigation/Byellownone"
        anchors {top:beepButtom.bottom; topMargin: 10}

        MouseArea {
            id: closeExitMouse
            anchors.fill: parent
            onClicked: {
                if (closeExitButton.iconSource == "qrc:/images/navigation/Byellownone")
                {
                    settingCtrl.updateExitOnClose("true")
                    closeExitButton.iconSource = "qrc:/images/navigation/Byellowchecked"
                }
                else
                {
                    settingCtrl.updateExitOnClose("false")
                    closeExitButton.iconSource = "qrc:/images/navigation/Byellownone"
                }
            }
        }
    }

    ShortcutButton {
        id: startOnPoweronButton
        height: 20
        buttonText: qsTr("Clipboard")//"监控剪切板"//
        iconSource: settingCtrl.clipboard === "true"?"qrc:/images/navigation/Bredchecked":"qrc:/images/navigation/Brednone"
        anchors {top:closeExitButton.bottom; topMargin: 10}

        MouseArea {
            id: startOnPoweronMouse
            anchors.fill: parent
            onClicked: {
                if (startOnPoweronButton.iconSource == "qrc:/images/navigation/Brednone")
                {
                    settingCtrl.updateClipboard("true")
                    startOnPoweronButton.iconSource = "qrc:/images/navigation/Bredchecked"
                }

                else
                {
                    settingCtrl.updateClipboard("false")
                    startOnPoweronButton.iconSource = "qrc:/images/navigation/Brednone"
                }
            }
        }
    }
}
