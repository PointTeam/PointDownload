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

function updateFileName(url,newName)
{
    for (var i = 0; i < ingItemModel.count; i ++)
    {
        var tmpObj;
        tmpObj = ingItemModel.get(i);

        if (tmpObj.tmpURL === url)
        {
            ingItemModel.setProperty(i,"tmpName",newName);
            break;
        }
    }
}

function updateNetSpeed(url,netSpeed)
{
    for (var i = 0; i < ingItemModel.count; i ++)
    {
        var tmpObj;
        tmpObj = ingItemModel.get(i);
        if (tmpObj.tmpURL === url)
        {
            ingItemModel.setProperty(i,"tmpSpeed",netSpeed);
            break;
        }
    }
}

function updateOfflineSpeed(url,speed)
{
    for (var i = 0; i < ingItemModel.count; i ++)
    {
        var tmpObj;
        tmpObj = ingItemModel.get(i);
        if (tmpObj.tmpURL === url)
        {
            ingItemModel.setProperty(i,"tmpOfflineSpeed",speed);
            break;
        }
    }
}

function updateHightSpeed(url,speed)
{
    for (var i = 0; i < ingItemModel.count; i ++)
    {
        var tmpObj;
        tmpObj = ingItemModel.get(i);
        if (tmpObj.tmpURL === url)
        {
            ingItemModel.setProperty(i,"tmpHightSpeed",speed);
            break;
        }
    }
}

function updateFileState(url,state)
{
    for (var i = 0; i < ingItemModel.count; i ++)
    {
        var tmpObj;
        tmpObj = ingItemModel.get(i);
        if (tmpObj.tmpURL === url)
        {
            ingItemModel.setProperty(i,"tmpState",state);
            break;
        }
    }
}

function updatePercentage(url,newPercentage)
{
    for (var i = 0; i < ingItemModel.count; i ++)
    {
        var tmpObj;
        tmpObj = ingItemModel.get(i);
        if (tmpObj.tmpURL === url)
        {
            ingItemModel.setProperty(i,"tmpPercentage",newPercentage);
            break;
        }
    }
}

function addNewItem(infoList)
{
    //info: dlToolsType?:?fileName?:?URL?:?RedirectURL?:?iconName?:?fileSize?:?savePath?:?threadCount?:?maxSpeed?:?readyPercentage?:?state
    var infoArry = infoList.split("?:?");
    if (infoArry.length > 5)
    {
        var sizeByte=0;

        if (infoArry[5] > 1024 * 1024 * 1024)//GB
            sizeByte = (infoArry[5] / (1024 * 1024 * 1024)).toFixed(1) + " GB"
        else if (infoArry[5] > 1024 * 1024)//MB
            sizeByte = (infoArry[5] / (1024 * 1024)).toFixed(1) + " MB"
        else if (infoArry[5] > 1024)//KB
            sizeByte = (infoArry[5] / 1024).toFixed(1) + " KB"
        else
            sizeByte = (infoArry[5] / 1).toFixed(1) + " B"
    }

    console.log(infoArry);
    console.log(infoArry[9])
    console.log(parseFloat(infoArry[9]))

    //从已下载项和垃圾桶传过来的值中没有下载百分比(infoArry[7])的数据
    ingItemModel.append({"tmpDLToolsType":infoArry[0],
                        "tmpName":infoArry[1],
                        "tmpURL":infoArry[2],
                        "tmpPath":infoArry[4],
                        "tmpSize":sizeByte,
                        "tmpPercentage":infoArry[9] === undefined ? 0 : parseFloat(infoArry[9]),
                        "tmpState":infoArry[10] === undefined ? "dlstate_downloading" : infoArry[10],
                        "tmpSpeed": "0KB/S",
                        "tmpOfflineSpeed":"",
                        "tmpHightSpeed":""});
    //把已下载项中的数据删除，包括界面
    downloadedPage.moveItem(infoArry[2]);
    //删除垃圾箱里的数据，包括界面
    downloadTrashPage.moveItem(infoArry[2]);
}

function removeItem(url)
{
    for (var i = 0; i < ingItemModel.count; i ++)
    {
        var tmpObj;
        tmpObj = ingItemModel.get(i);
        if (tmpObj.tmpURL === url)
        {
            ingItemModel.remove(i,1);
            break;
        }
    }
}

function moveItemToTop()
{
    // 把有速度的都移动到最顶端
    var tmpObj;

    for (var i = 0; i < ingItemModel.count; i ++)
    {
        tmpObj = ingItemModel.get(i);

        if (tmpObj.tmpSpeed !== "0 KB/S")
        {
            ingItemModel.move(i,0, 1);
        }
    }
}


function getFileInfo(url)
{
    for (var i = 0; i < ingItemModel.count; i ++)
    {
        var tmpObj;
        tmpObj = ingItemModel.get(i);
        if (tmpObj.tmpURL === url)
        {
            var sizeByte=0;

            if (tmpObj.tmpSize.split(" ").length > 1)
            {
                if (tmpObj.tmpSize.split(" ")[1] === "GB")
                    sizeByte = tmpObj.tmpSize.split(" ")[0] * 1024 * 1024 * 1024;
                else if (tmpObj.tmpSize.split(" ")[1] === "MB")
                    sizeByte = tmpObj.tmpSize.split(" ")[0] * 1024 * 1024;
                else if (tmpObj.tmpSize.split(" ")[1] === "MB")
                    sizeByte = tmpObj.tmpSize.split(" ")[0] * 1024;
            }
            //console.log(tmpObj.tmpName)
            return tmpObj.tmpDLToolsType + "?:?"
                    + tmpObj.tmpName + "?:?"
                    + tmpObj.tmpURL + "?:?"
                    + tmpObj.tmpPath + "?:?"
                    + sizeByte + "?:?"
                    + Qt.formatDateTime(new Date(),"yyyy:MM:dd:hh:mm")
        }
    }
}

