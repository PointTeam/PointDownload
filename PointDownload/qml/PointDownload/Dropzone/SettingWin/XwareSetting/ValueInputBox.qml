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
    这是TopPanel的搜索框，没有内容的时候默认为显示File name，有输入内容的时候就自动
    删除File name而显示新内容
Others:

History:
*********************************************************************/
import QtQuick 2.0

FocusScope {
    property string defaultText : "Download URL";
    property bool showPasswd:true
    property bool showDefaultPasswd:true

    clip: true

    id: vInputBox

    signal finishInput()

    TextInput {
        id: defaultInputText
        width: parent.width
        height: parent.height
        enabled: false
        echoMode: showDefaultPasswd?TextInput.Normal : TextInput.Password
        anchors { left: parent.left; leftMargin:2 }
        verticalAlignment: Text.AlignVCenter
        text: defaultText
        color: "gray"
        font.pixelSize: 13
        font.italic: true
    }
    TextInput {
        id: textInput
        width: parent.width
        height: parent.height
        anchors { left: parent.left; leftMargin:2 }
        verticalAlignment: TextInput.AlignVCenter
        focus: true
        font.pixelSize: 14
        selectByMouse: true
        color: "#ffffff"
        selectionColor: "#488bc5"
        echoMode: showPasswd?TextInput.Normal : TextInput.Password
        Keys.onPressed: {
            //Key_Enter通常位于小键盘上
            if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return || event.key === Qt.Key_Tab)
            {
                vInputBox.finishInput()
            }
        }
    }
    states:State {
        name: "hasText"
        when: textInput.text != ''
        PropertyChanges{ target: defaultInputText; opacity: 0 }
    }
    transitions: [
        Transition {
            from: ""
            to: "hasText"
            NumberAnimation { exclude: defaultInputText; properties: "opacity"}
        },
        Transition {
            from: "hasText"
            to: ""
            NumberAnimation {properties: "opacity"}
        }
    ]

    function getInputText()
    {
        if (textInput.text != '')
            return textInput.text
        else
            return defaultText;
    }

    function clearInputText()
    {
        textInput.text = ""
    }
}
