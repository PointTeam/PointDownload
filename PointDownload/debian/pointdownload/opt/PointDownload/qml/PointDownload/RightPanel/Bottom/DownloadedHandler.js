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

function addNewItem(infoList)
{
    if (infoList === undefined)
        return;
    //info: dlToolsType?:?fileName?:?URL?:?iconName?:?fileSize?:?completeDate
    var infoArry = infoList.split("?:?");
    var fileSize = infoArry[4];

    if (fileSize > 1024*1024*1024)
        fileSize = (fileSize / (1024 * 1024 * 1024)).toFixed(1) + "GB"
    else if (fileSize > 1024 * 1024)
        fileSize = (fileSize / (1024 * 1024)).toFixed(1) + "MB"
    else if (fileSize > 1024)
        fileSize = (fileSize / 1024).toFixed(1) + "KB"
    else
        fileSize = (fileSize / 1).toFixed(1) + "B"
    edItemModel.append({"tmpDLToolsType":infoArry[0],
                         "tmpName":infoArry[1],
                        "tmpURL":infoArry[2],
                        "tmpPath":infoArry[3],
                        "tmpSize":fileSize,
                       "tmpDate":infoArry[5]})
}

function removeItem(url)
{
    for (var i = 0; i < edItemModel.count; i ++)
    {
        var tmpObj;
        tmpObj = edItemModel.get(i);
        if (tmpObj.tmpURL === url)
        {
            edItemModel.remove(i,1);
            break;
        }
    }
}


function getFileInfo(url)
{
    for (var i = 0; i < edItemModel.count; i ++)
    {
        var tmpObj;
        var totalSize = 0;
        tmpObj = edItemModel.get(i);

        if (tmpObj.tmpURL !== url)
            continue;

        if (tmpObj.tmpSize.indexOf("GB") > 0)
        {
            totalSize =    tmpObj.tmpSize.substring(0,tmpObj.tmpSize.indexOf("GB") - 1) * 1024 * 1024 * 1024
        }
        else if (tmpObj.tmpSize.indexOf("MB") > 0)
        {
            totalSize =    tmpObj.tmpSize.substring(0,tmpObj.tmpSize.indexOf("MB")- 1 ) * 1024 * 1024
        }
        else if (tmpObj.tmpSize.indexOf("KB") > 0)
        {
            totalSize =    tmpObj.tmpSize.substring(0,tmpObj.tmpSize.indexOf("KB")- 1 ) * 1024
        }
        else if (tmpObj.tmpSize.indexOf("B") > 0)
        {
            totalSize =    tmpObj.tmpSize.substring(0,tmpObj.tmpSize.indexOf("B")- 1 ) * 1
        }

        return tmpObj.tmpDLToolsType + "?:?"
                + tmpObj.tmpName + "?:?"
                + tmpObj.tmpURL + "?:?"
                + tmpObj.tmpPath + "?:?"
                + totalSize;
    }
}
