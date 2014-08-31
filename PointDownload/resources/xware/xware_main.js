// http://yuancheng.xunlei.com/3/

var spliterBtwData = "#..#";
var spliterEnd = "#.^_^.#";
var pointReflashDownloadListIntervalId = 0;  // timer id (feedback the tasks information)
var pointIsReflashDownloadListTimerStarted = false;  // is the timer start

// ======================= Bind Singals ======================= //
Point.sJSGetAllBindedPeerIds.connect(pointSlotGetAllBindedPeerIds);
Point.sJSReflashDownloadList.connect(pointSlotReflashDownloadList);

// add new task
Point.sJSAddNewDownloadTask.connect(pointAddNewDownloadTask);
//Point.sAddNewBTDownloadTask.connect(pointAddNewBTDownloadTask);

// task controller
Point.sJSSuspendDownloadingTask.connect(pointSuspendDownloadingTask);
Point.sJSResumeDownloadingTask.connect(pointResumeDownloadingTask);
Point.sJSRemoveDownloadingTask.connect(pointRemoveDownloadingTask);
Point.sJSEntryOfflineChannel.connect(pointEntryOfflineChannel);
Point.sJSEntryHighSpeedChannel.connect(pointEntryHighSpeedChannel);
Point.sJSUrlParse.connect(pointUrlParse);

// logout
Point.sJSLogout.connect(pointLogout);
// ======================================================== //

// parse url like magent, ftp ...
function pointUrlParse(url)
{
    var taskFileList = "";
    var fileName = "";
    var fileSize = "";
    var isMagnet = false;

    if(url.indexOf("magnet") >= 0)
    {
        isMagnet = true;
    }

    App.set("dialogs.createTask.show", true);  // this can be removed
    $("#d-create-task-url").val(url).keyup().get(0).focus();
    App.set("dialogs.createTask.confirmEVT", true);

    setTimeout(
    function()
    {
        $("#d-create-task-file-list > li").each
        (
            function ()
            {
                if(isMagnet)
                {
                    fileName = $(this).find(".pop_al_02").html();
                }
                else
                {
                    fileName = $(this).find("p > input").attr("value");
                }

                fileSize = $(this).find(".pop_al_03").html();
                taskFileList += fileName + spliterBtwData + fileSize + spliterEnd;
            }
        );
        Point.feedbackURLParse(taskFileList);
        App.set("dialogs.createTask.show", false);
    }, 1500
    );
}

function pointAddNewDownloadTask(url, storage, fileList)
{
    Point.justForJSTest("----------------- pointAddNewDownloadTask -----------------------");
    Point.justForJSTest(url);

    isAddNewDownloadTask = true;
    App.set("dialogs.createTask.show", true);  // this can be removed
    $("#d-create-task-url").val(url).keyup().get(0).focus();
    App.set("dialogs.createTask.confirmEVT", true);

    // storage    fileList
    setTimeout(
    function()
    {
        App.set("dialogs.createTask.confirmEVT", true);

        Point.justForJSTest("----------------- download -----------------------");

    }, 1500
    );


    Point.justForJSTest("----------------- end -----------------------");

}

function pointAddNewBTDownloadTask(btFilePath, storage, fileList)
{

}

// ================================== task controller ==================================== //
function pointSuspendDownloadingTask(tid)
{
    // debugger
    Point.justForJSTest("----------------- suspend -----------------------" + tid);
    App.set("task.pause", tid);
}

function pointResumeDownloadingTask(tid)
{
    // debugger
    Point.justForJSTest("----------------- resume -----------------------" + tid);

    App.set("task.start", tid);
}

function pointRemoveDownloadingTask(tid)
{
    // debugger
    Point.justForJSTest("----------------- remove -----------------------" + tid);

    App.set("task.remove", tid);
}

function pointEntryOfflineChannel(tid)
{
    // debugger
    Point.justForJSTest("----------------- Entry Offline Channel -----------------------" + tid);

    App.set("task.activeLixian", tid);
}

function pointEntryHighSpeedChannel(tid)
{
    // debugger
    Point.justForJSTest("----------------- Entry High Speed Channel -----------------------" + tid);

    App.set("task.activeGaosu", tid);
}

// ================================================================================== //

function pointSlotGetAllBindedPeerIds()
{
    var peerList = "";
    $("#d-create-task-downloader-list>li").each(
    function()
    {
        peerList += $(this).attr("data-pid") + spliterBtwData;
    });

    Point.setAllBindedPeerIds(peerList);
}

function pointRefashDloadListTimer()
{
    var allTaskInfo = '';

    $("#task-list>div").each(
    function()
    {
        var $taskDiv, tid, taskName, size, progress, speed, remain, state, url, highSpeed, offlineSpeed, ta = G("task.all");;
        tid = $(this).attr("data-tid");
        $taskDiv = $("#task-list > div[data-tid="+tid+"]");
        taskName = $taskDiv.find(".rw_u02").find(".rw_p_name").html();
        size = $taskDiv.find(".rw_u02").find(".rw_sp_size").html();
        progress = $taskDiv.find(".rw_u03").find(".rw_pr_num").html();
        speed = $taskDiv.find(".rw_u03").find(".rw_pr_speed").html();
        remain = $taskDiv.find(".rw_u03").find(".rw_pr_time").html();
        state = $taskDiv.find(".rw_u02>div>i").attr("class");
        url = ta[tid].url;

        var $taskDiv2 = $("#task-list > div[data-tid="+tid+"] > div.rw_u_add > div.rw_u03 > div.rw_u_btn");
        highSpeed = $taskDiv2.find("span.fail_gs > span").html();
        offlineSpeed = $taskDiv2.find("span.fail_lx > span").html();

        var allTaskInfo_temp = tid+spliterBtwData+taskName+spliterBtwData+size+spliterBtwData+progress
                +spliterBtwData+speed+spliterBtwData+remain+spliterBtwData+state+spliterBtwData+url
                +spliterBtwData+highSpeed+spliterBtwData+offlineSpeed+spliterEnd;
        allTaskInfo += allTaskInfo_temp;
    }
    );

    Point.feedbackDownloadList(allTaskInfo);
}


function pointSlotReflashDownloadList()
{
    Point.justForJSTest("... start feedbacking task info ...");

    if(!pointIsReflashDownloadListTimerStarted)
    {
        // setInterval
        pointReflashDownloadListIntervalId = setInterval("pointRefashDloadListTimer()", 1000);
        pointIsReflashDownloadListTimerStarted = true;
    }
}

// stop feedback the task content
function pointStopPointInterval()
{
    window.clearInterval(pointReflashDownloadListIntervalId);
}

function pointSetDefaultMachine(peerId)
{
    $("#manage-list > li[data-pid="+peerId+"]").click();
}

function pointBindNewMachine(code)
{
    if(code === "")
    {
        Point.justForJSTest("  machine code is empty, return  ");
        return;
    }

    $pop_sjbox_div = $("#d-add-downloader-panels > div.pop_addd_unit > div.pop_de_inp > div.pop_sjbox");
    $pop_sjbox_div.find(".sel_txt > input.sel_inptxt").val(code).blur().trigger('input');
    $pop_sjbox_div.find("a.btn_inp").click();
}

function pointLogout()
{
    // debugger
    Point.justForJSTest("----------------- logOut -----------------------");

    App.set("exit", true);
}

function pointUnbindMachine(code)
{

}

