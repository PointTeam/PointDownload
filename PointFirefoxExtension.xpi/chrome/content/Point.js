var Point = {
    ARG_DEF_STR : "",
    PointComponent: null,
    agentName : "",
    referrer : "",
    urls : [],
    cookies : [],
    descs : [],
    cids : [],
    totalTask : 0,
    offLine : false,
    filerExtStr : "",
    candidate : {agents : [], urlArrays : [], taskCount : 0},
    
    apiDownUrl : function(referrer, url, agentName) {
        var isUrlArray = Object.prototype.toString.call(url) === '[object Array]';
        var totalTask = isUrlArray ? url.length : 1;
        this.init(referrer, totalTask, agentName);
        if (isUrlArray) {
            for (var i in url) {
                this.addTask(url[i]);
            }
        } else {
            this.addTask(url);
        }
        return this.callAgent();
    },

    init : function(referrer, totalTask, agentName) {
        this.referrer = referrer || this.ARG_DEF_STR;
        this.urls = [];
        this.cookies = [];
        this.descs = [];
        this.cids = [];
        this.totalTask = totalTask;
        if (!agentName) {
            agentName = PointPref.getDefaultAgent();
        } 
        this.filerExtStr = (this.totalTask > 1 && PointPref.getValue("filterExt")) ? PointPref.getValue("supportExt") : "";
        this.candidate.agents = PointPref.getValue("useCandidate") ? PointPref.getCandidateAgents(this.agentName) : [];
        for (var i in this.candidate.agents) {
            this.candidate.urlArrays[i] = [];
        }
        this.candidate.taskCount = 0;
    },
    
    addTask : function(url, des) {
        if (url == "" || PointPref.invalidReg.test(url)) {
            // Invalid url
            url = this.referrer;
        }
        
        // Nonsupport or filtered url
        if (this.filerExtStr && PointPref.uriSupReg.test(url) && !PointPref.isExtSupURL(url, this.filerExtStr)) {
            --this.totalTask;
            return;     
        }
        var agentsNonsup = PointPref.getUnsupAgents(url);
        if (agentsNonsup.indexOf(this.agentName) != -1) {
            // Use candidate agent to download
            if (this.candidate.agents.length > 0) {
                for (var i in this.candidate.agents) {
                    if (agentsNonsup.indexOf(this.candidate.agents[i]) == -1) {
                        this.candidate.urlArrays[i].push(url);
                        ++this.candidate.taskCount;
                        break;
                    }
                }
            }
            --this.totalTask;
            return;
        }

        this.urls.push(url);
        this.cookies.push(this.getCookie(url));
        if (this.totalTask == 1) {
            des = this.ARG_DEF_STR;
        } else if (!des) {
            des = this.getFileName(url);
        } else {
            des = des.replace(/^\s+|\s+$|[\r\n]+/g,"");
        }
        this.descs.push(des);
        this.cids.push(this.getCid(url, this.agentName, this.offLine));
    },
    
    callAgent : function() {   
        var result = 0;
        
        if (this.urls.length == this.totalTask && this.totalTask > 0 ) {
            try {
                
                // Clear array to free memory
                this.urls.length = this.cookies.length = this.descs.length = this.cids.length = this.totalTask = 0;
            } catch(ex) {
                alert(ex);
                result = -1;
            } 
        } else if (this.candidate.taskCount <= 0) {
            result = -1;
        }

        if (this.candidate.taskCount > 0) {
            result += this.callCandidate();
        } 

        return result == 0;
    },
    
};