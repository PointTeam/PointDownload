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

var tool = Qt.createComponent("SliderWin.qml");
var tooltip;
var fadeInDelay;
var fadeOutDelay;
var maxCount;
var miniCount;
var stepSize;
var currentValue;
var color;
var winType;


function fnishCreate(obj)
{
    if (tool.status === Component.Ready) {
        tooltip = tool.createObject(obj);
        tooltip.fadeInDelay = fadeInDelay;
        tooltip.fadeOutDelay = fadeOutDelay;
        tooltip.maxCount = maxCount;
        tooltip.miniCount = miniCount;
        tooltip.sliderStep = stepSize;
        tooltip.currentVlaue = currentValue;
        tooltip.grooveColor = color;
        tooltip.winType = winType;

        tooltip.state = "poppedUp";
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
    var tool = Qt.createComponent("SliderWin.qml")
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
    //如果数据未定义，则证明弹出窗口已经自己销毁，不需要重复销毁
    if (tooltip.maxCount !== undefined)
    {
        tooltip.updateValue();
        tooltip.state = "poppedDown";

        return true;
    }
    else
        return false;//返回false证明窗口是被弹出窗口自身销毁了，设置窗口需要重新生成弹出窗口
}
