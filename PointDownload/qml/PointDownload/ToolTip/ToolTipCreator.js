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

var tool = Qt.createComponent("ToolTip.qml");
var tooltip;
var fadeInDelay;
var fadeOutDelay;
var tip;


function fnishCreate(obj)
{
    if (tool.status === Component.Ready) {
        tooltip = tool.createObject(obj);
        tooltip.text = tip;
        tooltip.fadeInDelay = fadeInDelay;
        tooltip.fadeOutDelay = fadeOutDelay;
//        tooltip.state = "poppedUp";
        tooltip.startTimer();
        if (tooltip === null) {
            console.log("component createObject failed");
        }
    }
    else if (tool.status === Component.Error) {
        console.log("Error loading component:", tool.errorString());
    }
}

function showTipe(obj)
{
    var tool = Qt.createComponent("ToolTip.qml")
    if (tool.status === Component.Ready)
        fnishCreate(obj);
    else if (tool.status === Component.Error)
    {
        console.log("component Error:", tool.errorString());
    }
    else{
        tool.statusChanged.connect(fnishCreate);
    }
}

function close() {
    tooltip.state = "poppedDown";
}
