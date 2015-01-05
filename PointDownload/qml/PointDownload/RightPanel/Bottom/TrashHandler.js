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

function addNewItem(infoList)
{
    //info: dlToolsType?:?fileName?:?URL?:?iconName?:?fileSize?:?completeDate
    var infoArry = infoList.split("?:?");
    if (infoArry.length > 4)
    {
        var sizeByte=0;

        if (infoArry[4] > 1024 * 1024 * 1024)//GB
            sizeByte = (infoArry[4] / (1024 * 1024 * 1024)).toFixed(1) + " GB"
        else if (infoArry[4] > 1024 * 1024)//MB
            sizeByte = (infoArry[4] / (1024 * 1024)).toFixed(1) + " MB"
        else if (infoArry[4] > 1024)//KB
            sizeByte = (infoArry[4] / 1024).toFixed(1) + " KB"
        else
            sizeByte = (infoArry[4] / 1).toFixed(1) + " B"
    }
    trashItemModel.append({"tmpDLToolsType":infoArry[0],
                         "tmpName":infoArry[1],
                        "tmpURL":infoArry[2],
                        "tmpPath": infoArry[3],
                        "tmpSize":sizeByte})
}

function removeItem(url)
{
    for (var i = 0; i < trashItemModel.count; i ++)
    {
        var tmpObj;
        tmpObj = trashItemModel.get(i);
        if (tmpObj.tmpURL === url)
        {
            trashItemModel.remove(i,1);
            break;
        }
    }
}



function getFileInfo(url)
{
    for (var i = 0; i < trashItemModel.count; i ++)
    {
        var tmpObj;
        tmpObj = trashItemModel.get(i);
        if (tmpObj.tmpURL === url)
        {
            return tmpObj.tmpName + "?:?"
                    + tmpObj.tmpURL + "?:?"
                    + tmpObj.tmpPath + "?:?"
                    + tmpObj.tmpSize;
        }
    }
}
