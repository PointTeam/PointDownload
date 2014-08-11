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
//Date: 2014.3.12
//Description: This is a javaScript file use for handle contextMenus action
//When click the contextMenus, it will sent the infomation to native app

//connect to native app
var port = null;
var nativeHostName = "pointdownload";
var downloadID = null;
var showPopup = true;


//onNativeDisconnect
function onDisconnected()
{
//    alert("连接到Point服务失败: " + chrome.runtime.lastError.message);
    port = null;
}

//connect to native host and get the communicatetion port
function connectToNativeHost()
{
    port = chrome.runtime.connectNative(nativeHostName);
    port.onDisconnect.addListener(onDisconnected);
}

////|ftp|rtsp|mms
//function isNormalHttpURL(str_url){
//    var strRegex = "^((https|http|chrome)?://)"
//            + ".*\.(exe|asf|avi|exe|iso|mp3|mpeg|mpg|mpga|ra|rar|rm|rmvb|tar|wma|wmp|wmv|mov|zip|3gp|"
//            +"chm|mdf|torrent|jar|msi|arj|bin|dll|psd|hqx|sit|lzh|gz|tgz|xlsx|xls|doc|docx|ppt|pptx|flv|swf|mkv|"
//            +"tp|ts|flac|ape|wav|aac|txt|dat|7z|ttf|bat|xv|xvx|pdf|mp4|apk|ipa|epub|mobi|deb|sisx|cab|pxl|run|rpm|deb|dmg)"
//            +"($|[?]{1}.*$)";

//    var re=new RegExp(strRegex,"i");//i 不区分大小写

//    if (re.test(str_url))
//    {
//        return (true);
//    }
//    else
//    {
//        return (false);
//    }
//}


function isThunderURL(url)
{
    var strRegexThunder = "^(thunder)?://+";
    var reThunder = new RegExp(strRegexThunder,"i");

    if (reThunder.test(url))
        return true;
    else
        return false;
}

function getClickHandler() {
    return function(info, tab) {
        if (showPopup)
        {
            connectToNativeHost();
            //getDownloadID(info.linkUrl);
            port.postMessage(info.linkUrl);
        }
    };
};

function downloadVideo(url)
{
    connectToNativeHost();
    port.postMessage(url);
}

chrome.webRequest.onBeforeRequest.addListener(function(details) {
    if(isThunderURL(details.url))//这时浏览器不会建立下载,所以要用这种方式监听
    {
        if (showPopup)
        {
            connectToNativeHost();
            port.postMessage(details.url);
            return {redirectUrl:currentPage};
        }
        else
            return {redirectUrl:details.url};
    }
},
{urls: ["<all_urls>"],types:[ "main_frame"]},
["blocking"]);

chrome.downloads.onCreated.addListener(
    function callback(item)
    {
        if (item.state === "complete" || item.state === "interrupted")
        {
            // 此api的一个坑，首次安装会将下载列表已下载过的东西全部下一遍
            // console.debug("%s %s %s", item.state, " :", item.url);
            return;
        }
//        if (!isNormalHttpURL(item.url))
//        {
//            return;
//        }
        if (showPopup)
        {
            connectToNativeHost();
            port.postMessage(item.url);
            // 取消chrome默认下载
            chrome.downloads.cancel(item.id);
        }
    }
);

chrome.tabs.onUpdated.addListener(function(tabId,changeInfo,tab)
{
    chrome.tabs.getSelected(null, function(tab) { //<-- "tab" has all the information
        currentPage = tab.url;
    });
});


chrome.contextMenus.create({
                               "title" : "使用Point下载",
                               "type" : "normal",
                               "id": "FastDownloadMenu",
                               "contexts" : ["link"],
                               //"targetUrlPatterns":["*://*/*.*"],
                               "enabled": true,
                               "onclick" : getClickHandler()
                           });

chrome.browserAction.setPopup({popup: "popup.html"});

//启动时初始化showPopup变量，先获取本地存储的信息
chrome.storage.local.get("globalEnablePointFlag", function(result){
    if (result.globalEnablePointFlag)
    {
        showPopup = true;
    }
    else
    {
        showPopup = false;

    }
});

chrome.storage.onChanged.addListener(function(changes,areaName)
{
    if (changes["globalEnablePointFlag"].newValue)
    {
        showPopup = true;
    }
    else
    {
        showPopup = false;
    }

});
