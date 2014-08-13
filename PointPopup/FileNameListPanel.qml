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
import Singleton.DataControler 1.0

Rectangle {
    id:fileNameListPanel
    width: 100
    height: 62
    color: "#ffffff"
    border.width: 2
    border.color: "#c6c4c4"

    //连接单例的信号
    Connections {
        target: DataControler
        onSFileNameListChange:{
            addFileNameList(DataControler.fileNameList)
        }
    }

    Rectangle{
        id: fileListTitleRec
        anchors {left: fileItemView.left; bottom: fileItemView.top; bottomMargin: 15}

        Image{
            id:checkImg
            width: 12
            height: 12
            source: "qrc:/images/checked"
            anchors {left: parent.left;leftMargin: 2; verticalCenter: parent.verticalCenter}

            MouseArea{
                anchors.fill: parent
                onClicked: {

                    if (checkImg.source == "qrc:///images/checked")
                    {
                        checkImg.source = "qrc:///images/uncheck"
                        updateCheckState("qrc:/images/uncheck")
                    }
                    else
                    {
                        checkImg.source = "qrc:///images/checked"
                        updateCheckState("qrc:/images/checked")
                    }
                }
            }
        }
        Text{
            text:qsTr("File:")
            font.pixelSize: 12
            color: "#008dac"
            anchors {left: checkImg.right;leftMargin: 2; verticalCenter: parent.verticalCenter}
        }
    }

    ListModel {
        id: nameItemModel
    }
    Component {
        id: listDelegate
        Rectangle{
            Image{
                id:tmpCheckImg
                width: 12
                height: 12
                source: tmpSource
                anchors {left: parent.left; leftMargin: 2}
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        parent.source = parent.source == "qrc:/images/checked"?
                         "qrc:/images/uncheck":"qrc:/images/checked"
                    }
                }
            }

            TextInput{
                id:nameInput
                text:tmpName
                clip: true
                width: 150

                color: "#6d6f6e"
                selectionColor: "#1e1c1f"
                font.pixelSize: 11
                selectByMouse: true
                anchors {left: tmpCheckImg.right; leftMargin: 2;}

            }
            TextInput{
                id:typeInput
                text:tmpType
                clip: true
                width: 55
                color: "#6d6f6e"
                selectionColor: "#1e1c1f"
                font.pixelSize: 11
                selectByMouse: true
                anchors {left: nameInput.right; leftMargin: 10; verticalCenter: nameInput.verticalCenter}

            }
            TextInput{
                id:sizeInput
                text:tmpSize
                clip: true
                width: 60
                color: "#6d6f6e"
                font.pixelSize: 11
                enabled: false
                anchors {left: typeInput.right; leftMargin: 15; verticalCenter: nameInput.verticalCenter}

            }
        }
    }

    ListView {
        id: fileItemView
        clip: true
        anchors{fill: parent; leftMargin: 5; rightMargin: 5; topMargin: 5; bottomMargin: 5}
        model: nameItemModel
        spacing: 15
        delegate: listDelegate
    }

    function updateCheckState(iconPath)
    {
        for (var i = 0; i < nameItemModel.count; i ++)
        {
            var tmpObj;
            tmpObj = nameItemModel.get(i);
            tmpObj.tmpSource = iconPath
        }
    }

    function addFileNameList(nameList)
    {
        nameItemModel.clear()

        if (nameList === "")
        {
            return;
        }

        var infoArry = nameList.split("?:?");
        for (var i = 0; i < infoArry.length; i++)
        {
            var nameArry = infoArry[i].split("@");
            if (nameArry.length === 3)
            {
                var sizeByte=0;

                if (nameArry[1] > 1024 * 1024 * 1024)//GB
                    sizeByte = (nameArry[1] / (1024 * 1024 * 1024)).toFixed(1) + " GB"
                else if (nameArry[1] > 1024 * 1024)//MB
                    sizeByte = (nameArry[1] / (1024 * 1024)).toFixed(1) + " MB"
                else if (nameArry[1] > 1024)//KB
                    sizeByte = (nameArry[1] / 1024).toFixed(1) + " KB"
                else
                    sizeByte = (nameArry[1] / 1).toFixed(1) + " B"
            }

            //从已下载项和垃圾桶传过来的值中没有下载百分比(nameArry[7])的数据
            nameItemModel.append({"tmpType":nameArry[0],
                                "tmpSource":"qrc:/images/checked",
                                "tmpName":nameArry[2],
                                "tmpPath":nameArry[4],
                                "tmpSize":sizeByte});
        }
    }

    function clearNameList()
    {
        nameItemModel.clear()
    }

    function getNameListLength()
    {
        return nameItemModel.count
    }
}
