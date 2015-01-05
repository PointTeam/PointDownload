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

import QtQuick 2.1
import QtQuick.Window 2.1
import Singleton.DataControler 1.0
import Singleton.NormalNotice 1.0
import Singleton.PEventFilter 1.0

Window {
    visible: true
    width: 400
    height: 545
    color: "#69b4ad"
    flags: Qt.FramelessWindowHint

    property int prex;
    property int nextx;
    property int prey;
    property int nexty;
    property int winx:(Screen.width - width) / 2
    property int winy:(Screen.height - height) / 2
    property string dragIng: "false"
    property int oldX: 0
    property int oldY: 0
    property int outSpace: 20
    property string newToolType

    x: winx
    y: winy

    //连接单例的信号
    Connections {
        target: DataControler
        onSFnishGetAllInfo:{
            okRec.color = "#e2567d"
            okRec.enabled = true
            loadingImg.visible = false
        }
        onSIsWrongURL:{
            okRec.color = "#c6c4c4"
            okRec.enabled = false
            loadingImg.visible = false
        }
        onSGettingInfo:
        {
            if (flag)
            {
                loadingImg.visible = true
                okRec.color = "#c6c4c4"
                okRec.enabled = false
            }
            else
            {
                loadingImg.visible = false
                okRec.color = "#e2567d"
                okRec.enabled = true
            }
        }
    }

    //连接单例的信号
    Connections {
        target: PEventFilter
        onSendEnterKeyChange:{
            if (okRec.enabled === true)
            {
                DataControler.sendToMainServer(settingSpinBox.getThreadCount(),
                                               settingSpinBox.getSpeed(),
                                               savePanel.getSavePath(),
                                               newToolType)
                Qt.quit()
            }
        }
        onSendEscKeyChange:{
            Qt.quit()
        }
    }

    Rectangle{
        id:manRectangle
        height: parent.height - outSpace * 2
        width: parent.width - outSpace * 2
        color: "#f1f1f1"
        anchors {verticalCenter: parent.verticalCenter;horizontalCenter: parent.horizontalCenter}

        //标题
        Text{
            id: titleText
            text: qsTr("Download Setting")
            color: "#6d6f6e"
            font.pixelSize: 15
            font.bold: true
            anchors {horizontalCenter: parent.horizontalCenter; top: parent.top; topMargin: 25}
        }

        //线程数和速度限制框
        SettingSpinBox{
            id: settingSpinBox
            anchors {top: titleText.bottom; horizontalCenter: parent.horizontalCenter}
        }

        //URL框
        Text{
            text:qsTr("Download Sources:")
            font.pixelSize: 12
            color: "#008dac"
            anchors {left: urlPanel.left; bottom: urlPanel.top}
        }
        Rectangle{
            id:urlPanel
            width: parent.width - 40
            height: 22
            radius: 2
            clip: true
            border.width: 2
            border.color: "#c6c4c4"
            anchors {horizontalCenter: parent.horizontalCenter; top:settingSpinBox.bottom; topMargin: 20}
            TextInput{
                text:DataControler.fileURL
                color: "#6d6f6e"
                selectionColor: "#59add4"
                selectByMouse: true
                anchors {fill:parent; leftMargin: 5; topMargin: 2; rightMargin: parent.height}
                onTextChanged: {
                    fileListPanel.clearNameList()
                    DataControler.getURLFromBrowser(text)
                }
            }
            Image{
                width: parent.height
                height: parent.height
                source: "qrc:/images/bt-24"
                anchors {right: parent.right; verticalCenter:parent.verticalCenter }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                            //点击之后调用分析bt的方法并返回数据到弹出窗
                        DataControler.selectBTFile()
                    }
                }
            }
        }

        //file name ListElement
        FileNameListPanel{
            id: fileListPanel
            width: parent.width  - 40
            height: 150
            anchors {horizontalCenter: parent.horizontalCenter; top:urlPanel.bottom; topMargin: 25}
        }

        DownloadToolsPanel{
            id:toolsPanel
            width: parent.width - 40
            height: 40
            anchors {left: fileListPanel.left; top:fileListPanel.bottom;topMargin: 5}
            onUpdateToolType: {
                if (newTType=="")
                    newToolType = DataControler.defaultTool
                else
                    newToolType = newTType
            }
        }

        //存储设置
        SavePathPanel{
            id:savePanel
            width: parent.width - 40
            height: 40
            anchors {horizontalCenter: parent.horizontalCenter; top: toolsPanel.bottom; topMargin: 10}
        }

        Rectangle{
            id:bottomRec
            width: parent.width
            height: 50
            color: "#e8e8e8"
            anchors.bottom: parent.bottom

            AnimatedImage {
                id: loadingImg
                source: "qrc:/images/loading"
                playing: true
                opacity: 0.5
                width: 25
                height: 25
                anchors {left: parent.left;leftMargin: 20; verticalCenter: parent.verticalCenter}
            }

            //确定按钮
            Rectangle{
                id:okRec
                width: 80
                height: parent.height - 20
                radius: 20
                color: "#c6c4c4"
                enabled: false
                anchors {right: parent.right;rightMargin: 10; verticalCenter: parent.verticalCenter}

                Text{
                    text:qsTr("Download")
                    color: "#ffffff"
                    font.bold: true
                    font.pixelSize: 13
                    anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
                }


                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        DataControler.sendToMainServer(settingSpinBox.getThreadCount(),
                                                       settingSpinBox.getSpeed(),
                                                       savePanel.getSavePath(),
                                                       newToolType)
                    }
                }
            }


            //取消按钮
            Rectangle{
                id:cancelRec
                width: 80
                height: parent.height - 20
                radius: 20
                color: "#c6c4c4"
                anchors {right: okRec.left;rightMargin: 10; verticalCenter: parent.verticalCenter}

                Text{
                    id:cancelText
                    text:qsTr("Cancel")
                    color: "#9c9c9c"
                    font.bold: true
                    font.pixelSize: 13
                    anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: cancelText.color = "#ffffff"
                    onExited: cancelText.color = "#9c9c9c"
                    onClicked: Qt.quit()
                }
            }
        }


        MouseArea{
            id:mArea
            anchors {top: parent.top; bottom:titleText.bottom}
            width: parent.width
            hoverEnabled: true

            onPressed:  {
                oldX = mouseX + outSpace;
                oldY = mouseY + outSpace;
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


    //以下四个鼠标区域对应四周空白的区域，使空白区域可以在按下鼠标后移动窗口0166
    MouseArea{
        id:leftMArea
        anchors {left: parent.left; top: parent.top; bottom:parent.bottom}
        width: outSpace
        hoverEnabled: true

        onPressed:  {
            oldX = mouseX;
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

    MouseArea{
        id:rightMArea
        anchors {top: parent.top; bottom:parent.bottom; right: parent.right}
        width: outSpace
        hoverEnabled: true

        onPressed:  {
            oldX = mouseX + manRectangle.width + outSpace;
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

    MouseArea{
        id:topMArea
        anchors {top: parent.top; bottom:manRectangle.top;}
        width: parent.width
        height: outSpace
        hoverEnabled: true

        onPressed:  {
            oldX = mouseX;
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

    MouseArea{
        id:bottomMArea
        anchors {bottom: parent.bottom; top:manRectangle.bottom;}
        width: parent.width
        height: outSpace
        hoverEnabled: true

        onPressed:  {
            oldX = mouseX;
            oldY = mouseY + manRectangle.height + outSpace;
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
