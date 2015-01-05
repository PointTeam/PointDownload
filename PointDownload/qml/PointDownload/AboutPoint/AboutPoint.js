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

var aboutComponent = Qt.createComponent("AboutMain.qml");
var aboutPage;


function fnishCreate(obj)
{
    if (aboutComponent.status === Component.Ready) {
        aboutPage = aboutComponent.createObject(obj);

        if (aboutPage === null) {
            console.log("component createObject failed");
        }
        else
            aboutPage.show();
    }
    else if (aboutComponent.status === Component.Error) {
        console.log("Error loading component:", aboutComponent.errorString());
    }
}

function showAbout(obj)
{
    var aboutComponent = Qt.createComponent("AboutMain.qml")
    if (aboutComponent.status === Component.Ready)
        fnishCreate(obj);
    else if (aboutComponent.status === Component.Error)
    {
        console.log("component Error:", aboutComponent.errorString());
    }
    else{
        aboutComponent.statusChanged.connect(fnishCreate);
    }
}
