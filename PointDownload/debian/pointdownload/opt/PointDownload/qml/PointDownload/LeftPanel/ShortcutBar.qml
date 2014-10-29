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
        buttonText: qsTr("AlertTone")//"完成提示音"//
        iconSource: settingCtrl.alertToneEnable?"qrc:/images/navigation/Bbluechecked":"qrc:/images/navigation/Bbluenone"
        anchors {top:parent.top; topMargin: 12}

        MouseArea {
            id: beepMouse
            anchors.fill: parent
            onClicked: {
                if (beepButtom.iconSource == "qrc:/images/navigation/Bbluenone")
                {
                    settingCtrl.alertToneEnable = true
                    beepButtom.iconSource = "qrc:/images/navigation/Bbluechecked"
                }
                else
                {
                    settingCtrl.alertToneEnable = false
                    beepButtom.iconSource = "qrc:/images/navigation/Bbluenone"
                }
            }
        }
    }

    ShortcutButton {
        id: closeExitButton
        height: 20
        buttonText: qsTr("C&Q")//"关闭立即退出"//
        iconSource: settingCtrl.exitOnClose?"qrc:/images/navigation/Byellowchecked":"qrc:/images/navigation/Byellownone"
        anchors {top:beepButtom.bottom; topMargin: 10}

        MouseArea {
            id: closeExitMouse
            anchors.fill: parent
            onClicked: {
                if (closeExitButton.iconSource == "qrc:/images/navigation/Byellownone")
                {
                    settingCtrl.exitOnClose = true
                    closeExitButton.iconSource = "qrc:/images/navigation/Byellowchecked"
                }
                else
                {
                    settingCtrl.exitOnClose = false
                    closeExitButton.iconSource = "qrc:/images/navigation/Byellownone"
                }
            }
        }
    }

    ShortcutButton {
        id: enableDropzoneButton
        height: 20
        buttonText: qsTr("Dropzone")//"监控剪切板"//
        iconSource: settingCtrl.enableDropzone?"qrc:/images/navigation/Bredchecked":"qrc:/images/navigation/Brednone"
        anchors {top:closeExitButton.bottom; topMargin: 10}

        MouseArea {
            id: startOnPoweronMouse
            anchors.fill: parent
            onClicked: {
                if (enableDropzoneButton.iconSource == "qrc:/images/navigation/Brednone")
                {
                    settingCtrl.enableDropzone = true
                    enableDropzoneButton.iconSource = "qrc:/images/navigation/Bredchecked"
                }

                else
                {
                    settingCtrl.enableDropzone = false
                    enableDropzoneButton.iconSource = "qrc:/images/navigation/Brednone"
                }
            }
        }
    }
}
