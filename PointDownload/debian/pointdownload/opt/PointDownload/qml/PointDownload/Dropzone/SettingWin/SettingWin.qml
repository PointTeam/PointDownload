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

import QtQuick 2.1
import QtQuick.Window 2.1
import QtGraphicalEffects 1.0
import settingControler 1.0
import Singleton.PEventFilter 1.0


Window {
    id:settingWin
    flags:Qt.FramelessWindowHint | Qt.WA_TranslucentBackground

    color: "#00000000"
    width: 260
    height: 320
//    opacity: 0.8

    property string dragIng: "false"
    property int winx:0
    property int winy:height
    property int oldX: 0
    property int oldY: 0

    x:winx
    y:winy

    SettingControler {
        id:settingCtrl
    }

    Image{
        id:mainImg
        width: parent.width
        height: parent.height
        source: "qrc:/images/dropzone/tback"

        Rectangle{
            id:settingTitleRec
            width: parent.width - 20
            height: 40
            radius: 6
            color: "#06abc9"
            anchors {top: parent.top; left: parent.left}

            Text{
                id:settingTitle
                width: 20
                height: 20
                text: "Setting"
                color: "#ffffff"
                font.bold: true
                anchors {left:settingTitleRec.left;leftMargin: settingTitleRec.width / 2 - 20;top:settingTitleRec.top; topMargin: 10}
            }

            Image{
                id:closeImg
                width: 20
                height: 20
                source: "qrc:/images/dropzone/quit"
                anchors {right: settingTitleRec.right; rightMargin: 5}

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        settingWin.close()
                        settingCtrl.setSettingWinShowed(false)
                    }
                }
            }

            MouseArea{
                id:mArea
                anchors {fill: settingTitleRec; leftMargin: 20;rightMargin: 20}
                width: parent.width - 20 * 2
                height: parent.height
                hoverEnabled: true

                onPressed:  {
                    oldX = mouseX + 20;
                    oldY = mouseY;
                    dragIng = "true"
                    mArea.cursorShape=Qt.DragMoveCursor

                }
                onReleased: {
                    dragIng = "false"
                    mArea.cursorShape=Qt.ArrowCursor
                }

                onPositionChanged: {
                    if (dragIng == "true")
                    {
                        winx = PEventFilter.globalX- oldX
                        winy = PEventFilter.globalY - oldY;
                    }
                }
            }
        }

        SettingBody{
            id:settingBody
            width: settingTitleRec.width
            height: parent.height - settingTitleRec.height - 30
//            color: "#f7f8fa"
            anchors {top:settingTitleRec.top;topMargin: settingTitleRec.height - 3;}
        }

    }

    //阴影必须在所有组件之后才会在最底层
    DropShadow {
        anchors.fill: mainImg
        horizontalOffset: 3
        verticalOffset: 3
        radius: 2.0
        samples: 16
        fast: false
        color: "#aa000000"
        source: mainImg
    }
}
