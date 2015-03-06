/**
 *  Author: sbwtw <sbwtws@gmail.com>
 *
 *  下载任务界面管理的脚本，用于控制所有任务列表
 * */


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

// 为了兼容新代码和旧代码而做转换, 新代码中不再以String类型表示任何不必要的属性
// 这些常量的定义可以在 taskInfo.h 中找到
function convertDLSTATE(dlstate)
{
    if (typeof dlstate === 'number')
        return dlstate;

    console.log('convertDLSTATE called');

    dlstate = dlstate.toUpperCase();

    if (dlstate === 'DLSTATE_SUSPEND')
        return 1;
    if (dlstate === 'DLSTATE_DOWNLOADING')
        return 2;
    if (dlstate === 'DLSTATE_READY')
        return 3;
    if (dlstate === 'DLSTATE_DOWNLOADED')
        return 4;
    if (dlstate === 'DLSTATE_CANCELD')
        return 5;

    return 0;
}

function updateFileState(url,state)
{
    for (var i = 0; i < ingItemModel.count; i ++)
    {
        var tmpObj;
        tmpObj = ingItemModel.get(i);
        if (tmpObj.tmpURL === url)
        {
            ingItemModel.setProperty(i, "tmpState", convertDLSTATE(state));
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

// 格式化文件大小
function formatFileSize(size)
{
    if (size < 10000)
        return size.toFixed(1) + "B";

    size /= 1024;

    if (size < 1024)
        return size.toFixed(2) + "KB";

    size /= 1024;

    if (size < 1024)
        return size.toFixed(2) + "MB";

    size /= 1024;

    return size.toFixed(2) + "GB";
}

function addNewTask(taskInfo)
{
//    console.log(JSON.stringify(taskInfo));

    // 1 暂停 2 正在下载 3 等待下载 4 下载完成 5 垃圾箱
    switch (taskInfo.state)
    {
        case 1:
        case 2:
        case 3:     downloadingModel.append(taskInfo);      break;
        case 4:     downloadedModel.append(taskInfo);       break;
        case 5:     trashModel.append(taskInfo);            break;
        default:    console.log(qsTr('TaskState Wrong.'), JSON.stringify(taskInfo));
    }
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

