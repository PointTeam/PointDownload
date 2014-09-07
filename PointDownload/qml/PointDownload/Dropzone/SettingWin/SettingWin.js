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

var settingWinComponent = Qt.createComponent("SettingWin.qml");
var settingPage;
var pageX = 0
var pageY = 0


function fnishCreate(obj)
{
    if (settingWinComponent.status === Component.Ready) {
        settingPage = settingWinComponent.createObject(obj, {"winx": pageX, "winy": pageY});

        if (settingPage === null) {
            console.log("component createObject failed");
        }
        else
            settingPage.show();
    }
    else if (settingWinComponent.status === Component.Error) {
        console.log("Error loading component:", settingWinComponent.errorString());
    }
}

function showSettingWin(obj,x,y)
{
    pageX = x
    pageY = y

    var settingWinComponent = Qt.createComponent("SettingWin.qml")
    if (settingWinComponent.status === Component.Ready)
        fnishCreate(obj);
    else if (settingWinComponent.status === Component.Error)
    {
        console.log("component Error:", settingWinComponent.errorString());
    }
    else{
        settingWinComponent.statusChanged.connect(fnishCreate);
    }
}

function destroySettingWin()
{
    settingPage.close()
}
