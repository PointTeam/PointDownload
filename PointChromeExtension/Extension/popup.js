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

function isVideoURL(url)
{
    //var strRegex = "^(http://www.tudou.com/|http://v.yinyuetai.com/|http://v.youku.com/|http://v.ku6.com/|http://v.163.com/).+";
    var strRegex = "^(http://www.tudou.com/|http://v.yinyuetai.com/|http://v.youku.com/|http://v.ku6.com/|http://v.163.com/|http://www.acfun.com/v/|http://bilibili.kankanews.com/video/av|http://www.jpopsuki.tv/video/|http://video.sina.com.cn/|http://tv.sohu.com/|http://www.56.com/w|http://www.56.com/u|http://www.songtaste.com/song/).+";

    var re=new RegExp(strRegex,"i");//i 不区分大小写

    if (re.test(url))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}


function clickEnableAll(e) {	 
  if (document.getElementById("enablePointAll").checked)
    chrome.storage.local.set({'globalEnablePointFlag':true});
  else
    chrome.storage.local.set({'globalEnablePointFlag':false});
  
  //window.close();
}

function getFeedBack(e){
    chrome.tabs.create({
                        "url":"http://www.linuxdeepin.com/forum/23/21124"
                       });

    window.close();
}

function downloadVideo(e){
    chrome.tabs.getSelected(null, function(tab) { //<-- "tab" has all the information

        currentPage = tab.url;
        //当网址是可下载的视频网址时，browserAction下拉菜单出现下载视频选项
        if (isVideoURL(tab.url))
        {
            var pointBackgroundPage = chrome.extension.getBackgroundPage();
            pointBackgroundPage.downloadVideo(currentPage);
            window.close();
        }
    });
}
 
//先获取本地存储的信息，如果允许允许插件，则启动弹出窗口
chrome.storage.local.get("globalEnablePointFlag", function(result){
  if (result.globalEnablePointFlag)
  {
    document.getElementById("enablePointAll").checked = true;
  }
  else
  {
    document.getElementById("enablePointAll").checked = false;
  }
		  
 });



document.addEventListener('DOMContentLoaded', function () {
    document.getElementById("enablePointAll").addEventListener('click', clickEnableAll);
    document.getElementById("feedback").addEventListener('click', getFeedBack);
    document.getElementById("downloadVideo").addEventListener('click', downloadVideo);
});
