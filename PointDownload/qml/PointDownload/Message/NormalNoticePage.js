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

var normalNoticePageComponent = Qt.createComponent("NormalNoticePage.qml");
var normalNoticePage;

var messageTitle = ""
var titleColor = ""
var message = ""


function fnishCreate(obj)
{
    if (normalNoticePageComponent.status === Component.Ready) {
        normalNoticePage = normalNoticePageComponent.createObject(obj, {"messageTitle": messageTitle, "titleColor": titleColor, "message":message});

        if (normalNoticePage === null) {
            console.log("component createObject failed");
        }
        else
            normalNoticePage.show();
    }
    else if (normalNoticePageComponent.status === Component.Error) {
        console.log("Error loading component:", normalNoticePageComponent.errorString());
    }
}

function showNormalNoticePage(obj,tmpTitle,tmpColor,tmpMessage)
{
    messageTitle = tmpTitle
    titleColor = tmpColor
    message = tmpMessage

    var normalNoticePageComponent = Qt.createComponent("NormalNoticePage.qml")
    if (normalNoticePageComponent.status === Component.Ready)
        fnishCreate(obj);
    else if (normalNoticePageComponent.status === Component.Error)
    {
        console.log("component Error:", normalNoticePageComponent.errorString());
    }
    else{
        normalNoticePageComponent.statusChanged.connect(fnishCreate);
    }
}

function destroyNormalNoticePage()
{
    normalNoticePage.destroy()
}
