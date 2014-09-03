var PointDecode = {
    // Flashgetx is encoded at least twice, so pre decode it.
    getPreDecodedUrl : function(url) {
        url = url.replace(/ /g, "");
        var isSpecific = /^(flashget|qqdl):\/\//i.test(url);
        if (isSpecific) {
            url = this.getDecodedUrl(url);
        }
        return url;
    },

    getDecodedNode : function(link) {
        var url;
        var cid;
        var htmlDocument = link.ownerDocument;
        var referrer = htmlDocument.URL;
        
        // In special
        var matches;
        if (link.id == "union_download_point" && link.getAttribute("onclick")) {
        
            // point url in hidden element
            if (matches = htmlDocument.querySelector("a[pointhref]")) {
                url = matches.getAttribute("pointhref");
            }
        } else if (link.href && (matches = link.href.match(/^(http:\/\/db\.gamersky\.com\/Soft\/ShowSoftDown\.asp\?UrlID=.*&SoftID=.*)&flag=1/))) {
            // point url getting rid of flag
            url = matches[1];
        } else if (link.href && (matches = link.href.match(/^http:\/\/goxiazai\.(?:com|cc)\/xiazai\.html\?cid=(.*)&f=(point.+)/i))) {
            // point url in arguments of href
            cid = matches[1];
            url = this.getDecodedUrl(decodeURIComponent(matches[2]));
            if (cid) {
                url = url + "?cid=" + cid;
            }
            return url;
        } else if (/^http:\/\/www\.duote\.com\/soft\//i.test(referrer)) {
            if (matches = htmlDocument.getElementById("quickDown")) {
                url = matches.href;
            }
        } else if (!link.getAttribute("pointhref") && (matches = link.getAttribute("oncontextmenu")) && matches.indexOf("pointNetwork_SetHref") != -1) {
            // point url in oncontextmenu attribute
            var input,params,mc;
            if ((input = link.parentNode.firstChild) && (input.type == "checkbox" || input.type == "hidden") && (params = input.value)) { 
                params = params.split("&");
                for (var i=0; i<params.length; ++i) {
                    if (matches = params[i].match(/xzurl=(.*)/)) {
                        url = matches[1];
                        break;
                    } else if (matches = params[i].match(/cid=(.*)/)) {
                        cid = matches[1];
                    } else if (matches = params[i].match(/mc=(.*)/)) {
                        mc = matches[1];
                    }
                }
                
                if (!url) {
                    if (/^http:\/\/www\.ffdy\.cc\/|^http:\/\/www\.kankanba\.com\//i.test(referrer)) {
                        url = "http://point.ffdy.cc/" + cid + "/" + link.innerHTML.replace(/&nbsp;/g, "");
                    } else if (/^http:\/\/(?:www\.)?7369\.cc\//i.test(referrer)) {
                        url = "http://www.7369.com/" + cid + "/" + link.innerHTML.replace(/&nbsp;/g, "");
                    } else if (/^http:\/\/www\.2tu\.cc\//i.test(referrer)) {
                        url = "http://bt.2tu.cc/" + cid + "/" + mc;
                    } 
                }
            }     
        } else if (!link.getAttribute("pointhref") && (matches = link.getAttribute("onclick")) && matches.indexOf("point://") != -1) {
            // point url in onclick attribute
            if (matches = matches.match(/'(point:\/\/.*?)'/)) {
                url = matches[1];
            }
        } else if (!link.getAttribute("fg") && (matches = link.getAttribute("oncontextmenu")) && matches.indexOf("Flashget_SetHref") != -1) {
            // Flashget url in oncontextmenu attribute
            if (matches = matches.match(/Flashget_SetHref_js\(this,(?:'(.+)','.*')|(?:'(flashget:.*)')\)/)) {
                url = matches[1] || matches[2];
            } else if (matches = htmlDocument.defaultView.wrappedJSObject.fUrl) {
                url = matches;
            }
        } else if (link.id == "udown") {
            // Download url in sibling nodes
            url = this.getUDownUrl(link, referrer);
        } 

        // In general
        if (!url) {
            while (link && typeof link.href == "undefined" && !xpointPref.proSupReg.test(link.name)) {
                link = link.parentNode;
            }
            if (!link) {
                url = "";
            } else {
                url = link.getAttribute("pointhref") || 
                    link.getAttribute("fg") || link.getAttribute("qhref") || link.getAttribute("ed2k") || 
                    link.href || link.name;
            }
        }

        url = this.getDecodedUrl(url);
        return url;
    }
    
    
    getDecodedUrl : function(url) {
        try {
            url = url.replace(/ /g, "");
            var oriUrl = url;
            if (/^(?:point|flashget|qqdl|fs2you):\/\//i.test(url)) {
                url = this.decode64(url.replace(/^(?:point|flashget|qqdl|fs2you):\/\/|&.*|\/$/ig, "")).
                    replace(/^AA|ZZ$|\[FLASHGET\]|\|\d+$/g, "");
                if (/^qqdl:\/\//i.test(oriUrl) && url.indexOf("http://192.168.") != -1) {
                    // User oriUrl when it is qqdl://aHR0cDovLzE5Mi4xNjgu
                    url = oriUrl;
                } else if (/^flashget:\/\//i.test(oriUrl)) {
                    // Use oriUrl when it is actually flashgetx://|mhts|, or decode once more
                    url = /http:\/\/.*\/Zmxhc2hnZXR4Oi8vfG1odHN8[^/]*/.test(url) ? oriUrl : this.getDecodedUrl(url);
                } else if(/^ftp:\/\//i.test(url)) {
                    // Decode username,dir when url is like ftp://%E7%BA%A2%E6%97@wt4.hltm.cc:3101/E5%BD%B1%E5.rmvb
                    url = decodeURIComponent(url);
                } else if (url.indexOf(".rayfile.com") != -1 && url.indexOf("http://") == -1) {
                    // Format of cachefile*.rayfile.com
                    url = "http://" + url;
                }
            } 
        } catch (ex) {}

        return url;
    },
}