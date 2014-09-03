///////////////////////////////////////////////////////////////////
//	Event handler,require Point.js,pref.js,decode.js
///////////////////////////////////////////////////////////////////

var i = 0;

var RELATIVE_ROOT = '../../shared-modules';
var MODULE_REQUIRES = ['DownloadsAPI'];


Components.utils.import("resource://gre/modules/XPCOMUtils.jsm");

window.addEventListener("load", function(){//监听事件
    PointMain.addContextMenuListener();//监听右键事件
    PointMain.addClickSupport();//监听左键事件
    
}, false);

window.addEventListener("unload", function(){
    PointMain.deleteTempFiles();
}, false);


var PointMain = {
    ctxMenu : null,
    clickVntAdded : false,


    isVideoURL: function(url){
    try{
	var strRegex = "^(http://www.tudou.com/|http://v.yinyuetai.com/|http://v.youku.com/|http://v.ku6.com/|http://v.163.com/|http://www.acfun.com/v/|http://bilibili.kankanews.com/video/av|http://www.jpopsuki.tv/video/|http://video.sina.com.cn/|http://tv.sohu.com/|http://www.56.com/w|http://www.56.com/u|http://www.songtaste.com/song/).+";

    var re=new RegExp(strRegex,"i");

   if (re.test(url))
    {
        return (true);
    }
    else
    {
        return (false);
    }
    }catch(ex){
	alert(ex);
     }
},


 ClickMenu: function(ev) { 
        try {
            var popup = document.getElementById("clipmenu");
            
	    popup.showPopup(ev, "popup", null, null);
        }catch(ex){alert("clickmenu error" + ex);}
    },    

    ondo : function(aEvent){
        try {
	    var b = aEvent.currentTarget;
	    gBrowser.loadOneTab("http://www.linuxdeepin.com/forum/23/21124", null, null, null, true, false);           
        }catch(ex) {alert("error" + ex);}
    },    
    
    deleteTempFiles : function() {
       try{ 
           var file = Components.classes["@mozilla.org/file/directory_service;1"].
               getService(Components.interfaces.nsIProperties).
               get("TmpD", Ci.nsIFile);
           file.append("Point");
           if (file.exists())
               file.remove(true);
       } catch(ex) {}
    },
    
    addClickSupport : function() {
        if (PointPref.getValue("supportClick") != "" ||
            PointPref.getValue("supportExt") != "" && PointPref.getValue("remember")) {
            if (!PointMain.clickVntAdded) {
                var win = window.gBrowser || window;
                win.addEventListener("click", function(ev) {
                    if (ev.button != 0) {
                        return true;
                    }else{

                    }
                    return PointMain.OnLeftClick(ev);
                }, true);

                PointMain.clickVntAdded = true;
            }
        }
    },

    addContextMenuListener : function() {	        
	this.ctxMenu = document.getElementById("contentAreaContextMenu");
        this.ctxMenu.addEventListener("popupshowing", function(event){
            if (event.target == this) {
                PointMain.OnContextMenu();
            }
        }, false);
    },
    
    OnLeftClick : function(ev) {
        var remExt = PointPref.getValue("remember");
	
	
        var link = ev.target;
        if (typeof link.href == "undefined"  && !link.getAttribute("href") && !PointPref.proSupReg.test(link.name)) {
            link = link.parentNode;
            if (!link || typeof link.href == "undefined") {
                return true;
            }
        }
        var url = link.href || link.getAttribute("href") || link.name;
        var download = false;
 

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // create an nsILocalFile for the executable
		///////////*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Click support for associated file
        if (remExt) {
            download = PointPref.isExtSupURL(url);
        }

        // Click support for protocols
        if (!download) {
            var supstr = PointPref.getValue("supportClick");
            download = supstr != "" && PointDecode.isProSupNode(link, url, supstr.split(","));
            if(download) {
                url = PointDecode.getDecodedNode(link);
            }
        } 

        // Async decode will return false when callAgent
        // Currently there are no async decoding method though
        if (download && Point.apiDownUrl(link.ownerDocument.URL, url)) {
            ev.preventDefault();
            ev.stopPropagation();
            return false;
        } else {
            return true;
        }
    },
    
    //检测鼠标所点击的区域是否有link，若有则显示PointDownload载右键中
    OnContextMenu : function() {
        var downloadItem = document.getElementById("PointDownload");
        var sepItem = document.getElementById("PointDownloadUp");
        var downHidden = !PointPref.getValue("downInCxtMenu");
        var downSubMenuShown = PointPref.getValue("downSubMenu");
        var compact = PointPref.getValue("compactMenu");
        
        if (!downHidden) {
            // Show Point link in context menu if needed
            if (gContextMenu.onLink || gContextMenu.onImage) {
                downHidden = false;
            } else {
                var selText = document.commandDispatcher.focusedWindow.getSelection().toString();
                downHidden = !PointPref.isSupURL(selText);
            }
        }

        var itemHidden = [downHidden];
        var itemVisibleCount = 0;
        
        downloadItem.hidden = compact || (downHidden || !downSubMenuShown);
        sepItem.hidden = (itemVisibleCount == 0);
    },
    
    // Firefox may not close context menu and trigger wrong item
    // e.g. Inspect element of Firebug
    _closeCtxMenu : function(event) {
        this.ctxMenu.hidePopup();
        if (event && event.button == 2) {
            event.preventDefault();
            event.stopPropagation();
        }
    },

    OnPointDownload : function(event, type) {//点击右键下载时执行的方法      
	i++;   
	
	var htmlDocument = document.commandDispatcher.focusedWindow.document;//声明
        var url;
        if(type == 1){
	    url = window._content.location.href;
//	    url = window.location.href;
	}
        else if (gContextMenu.onLink) {
            // Get current link URL获取当前链接URL
            var linkNode = gContextMenu.target;
            if (typeof linkNode.href == "undefined" ) {
                linkNode = linkNode.parentNode;
            }
            url = linkNode;
//            url = PointDecode.getDecodedNode(linkNode);
//            alert(url);
        }
        else if (gContextMenu.onImage) {
            // Get current image url获取当前图片的URL
            url = gContextMenu.target.src;
        } else {
            // Get selected url获取选择区域的URL
            url = document.commandDispatcher.focusedWindow.getSelection().toString();
            if (!url || !PointPref.isSupURL(url)) {
                url = this._getUrlsFromClipboard()[0];
            }
            if (!url || !PointPref.isSupURL(url)) {
                url = "http://";
            }
            url = PointDecode.getDecodedUrl(url);
        }

        // create an nsILocalFile for the executable
        const NOTE_PATH = "/opt/Point/PopupWindow/PointPopup";

	
	var file = Components.classes["@mozilla.org/file/local;1"].getService(Components.interfaces.nsILocalFile);

	file.initWithPath(NOTE_PATH);

	
        if (!file.exists()) {
          alert("File does not exist: " + NOTE_PATH);
          return;
        }
		
        // create an nsIProcess
        var process = Components.classes["@mozilla.org/process/util;1"].createInstance(Components.interfaces.nsIProcess);

	try {
	    if (type == 1){
		  if (!PointMain.isVideoURL(url)){
		      alert("m( _ _ )m 非常抱们，我们没有获取到视频链接！\n");
		      return;
		  }
		  var args = ["FIREFOX#..#" + url];
	    }else{
			  
	          var args = ["FIREFOX#..#" + url];
	     }

	    process.init(file);
            process.run(false, args, args.length);
        }
        catch (ex) {
            alert(ex  + "Failed to execute: " + NOTE_PATH);
        }
        process.close();
    },
};
