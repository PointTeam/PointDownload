/**
 *  Author: sbwtw <sbwtws@gmail.com>
 *
 *  下载任务界面管理的脚本，用于控制所有任务列表
 * */

// global variable
var DLSTATE_UNDEF       = 0;
var DLSTATE_SUSPEND     = 1;
var DLSTATE_DOWNLOADING = 2;
var DLSTATE_READY       = 3;
var DLSTATE_DOWNLOADED  = 4;
var DLSTATE_TRASH       = 5;
var DLSTATE_REMOVE      = 6;

function restartDownload(taskInfo)
{
    downloadedModel.remove(taskInfo);
    trashModel.remove(taskInfo);
    downloadingModel.append(taskInfo);
}

function completeDownload(taskInfo)
{
    downloadingModel.remove(taskInfo);
    downloadedModel.append(taskInfo);
}

function moveToTrashDownload(taskInfo)
{
    downloadingModel.remove(taskInfo);
    trashModel.append(taskInfo);
}

function deleteDownload(taskInfo)
{
    downloadingModel.remove(taskInfo);
    downloadedModel.remove(taskInfo);
    trashModel.remove(taskInfo);
}

// 更新任务信息，只有下载中任务需要更新信息
function updateTaskInfo(taskInfo)
{
//    console.log(JSON.stringify(taskInfo));

    for (var i = 0; i !== downloadingModel.count; ++i)
    {
        if (downloadingModel.get(i).name === taskInfo.name)
        {
            downloadingModel.set(i, taskInfo);
            break;
        }
    }
}

function addNewTask(taskInfo)
{
//    console.log(JSON.stringify(taskInfo));

    switch (taskInfo.status)
    {
    case DLSTATE_SUSPEND:
    case DLSTATE_DOWNLOADING:
    case DLSTATE_READY:         downloadingModel.append(taskInfo);      break;
    case DLSTATE_DOWNLOADED:    downloadedModel.append(taskInfo);       break;
    case DLSTATE_TRASH:         trashModel.append(taskInfo);            break;
    default:    console.log(qsTr('TaskState Wrong.'), JSON.stringify(taskInfo));
    }
}
