////////////////////////////////////////////////////////////
//	Save as file dialog,require Point.js,pref.js
////////////////////////////////////////////////////////////
window.addEventListener("load", function() {
    function $() {
        return elements;
    }

    function forceNormal() {
        
    }
        
    function copyUrl() {
        var gClipboardHelper = Components.classes["@mozilla.org/widget/clipboardhelper;1"].
                getService(Components.interfaces.nsIClipboardHelper);
        gClipboardHelper.copyString(dialog.mLauncher.source.spec);
    }

    function download(agentName) {

    }

	var acceptBtn = document.documentElement.getButton("accept"); 
     
   	 var pointdownloadBtn = document.createElement("button");

	if (pointdownloadBtn && acceptBtn) {
            var btns = acceptBtn.parentNode.childNodes;
            for (var i = btns.length-1; i >= 0; --i) {
                if (btns[i].getAttribute("dlgtype") == "accept") { 
		    acceptBtn.parentNode.insertBefore(pointdownloadBtn, btns[i]);
                    break;
                    }
                }

   	 	pointdownloadBtn.id = "pointdownloadBtn";
   	 	pointdownloadBtn.label = "Point";
   	 	pointdownloadBtn.className = acceptBtn.className;
		pointdownloadBtn.addEventListener("click", function(event) {
                if (event.target == this) {
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
		var url = dialog.mLauncher.source.spec + "#..#FIREFOX";
            	var args = [url];

            	process.init(file);
            	process.run(false, args, args.length);
		
		var de = document.documentElement;
                de.removeAttribute("ondialogaccept");
                de.removeAttribute("onblur");
                de.removeAttribute("onfocus");
                de.cancelDialog();

            	//process.run(false, args, args.length);
            	//process.runAsync(args, args.length, null, false)
        	}
        	catch (ex) {
            	alert("Failed to execute: " + NOTE_PATH + "  " + ex);
        	}
        	process.close();
                }
            }, false);
	}
}, false); // End load function
