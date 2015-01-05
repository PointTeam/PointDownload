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

var menuToolTipComponent = Qt.createComponent("MenuToolTip.qml");
var tipPage;

function showMenuToolTip(obj,tips)
{
    var menuToolTipComponent = Qt.createComponent("MenuToolTip.qml")
    if (menuToolTipComponent.status === Component.Ready)
        fnishCreate(obj,tips);
    else if (menuToolTipComponent.status === Component.Error)
        console.log("component Error:", menuToolTipComponent.errorString());
    else
        menuToolTipComponent.statusChanged.connect(fnishCreate(obj,x,y,tips));
}


function fnishCreate(obj,tips)
{
    if (menuToolTipComponent.status === Component.Ready) {
        tipPage = menuToolTipComponent.createObject(obj, { "toolTips":tips});

        if (tipPage === null)
            console.log("component createObject failed");
        else
            tipPage.startTimer()
    }
    else if (menuToolTipComponent.status === Component.Error)
        console.log("Error loading component:", menuToolTipComponent.errorString());
}

function close()
{
    tipPage.destroy()
}
