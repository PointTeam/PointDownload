location == "chrome://browser/content/browser.xul" && (function(){
	var navigator = document.getElementById("navigator-toolbox");
	if (!navigator || navigator.palette.id !== "BrowserToolbarPalette") return;
	var btn = document.createElement("toolbarbutton");
	btn.id = "pluginButton";
	btn.setAttribute("label", "plugin");
	btn.setAttribute("type", "menu");
	btn.setAttribute("tooltiptext", "plugin");
	btn.appendChild(document.createElement("menupopup")).addEventListener("popupshowing", showPluginList,false)
	btn.setAttribute("class", "toolbarbutton-1 chromeclass-toolbar-additional");
	btn.setAttribute("removable", "true");
	btn.style.listStyleImage = "url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABIAAAASCAYAAABWzo5XAAAABHNCSVQICAgIfAhkiAAAAAlwSFlzAAALEgAACxIB0t1+/AAAABx0RVh0U29mdHdhcmUAQWRvYmUgRmlyZXdvcmtzIENTNXG14zYAAAN/SURBVDiNrZNNTCtlFIbP930z3/y0nVbaSktbkBaEhB/rRQgsIXEh0RioS3euDSYk7NiyM5Howg1udOHKjbiBEqO5iXRjiiCBe7lG/gy3vTTDnU5nOn/HhUK4QnTjuzw5eXLe855DEBH+KUIIRCKRLsZYr+d5R81m8+l9fbdF7ytGo9GXRVH8VBTFh6FQ6MtCodDzrxQAEO4rTkxMdOi6/sA0Tcjlcvnh4eE+ADj+TxAhRJIkSUFE33EcXFlZQV3Xjw8ODl6ZmpraXlhYqBJCpEgkIhmGQQHARET3NoggImSz2fdN03wnCIJWu9320+m0UiwWRxVFKdTr9Z+q1eqmaZoaYyzDGJM451+MjIxsbm1t4QsTDQ0NvXd4ePju9UIZY1Cr1RqdnZ0XV1dXb6iqOqMoCriuC4lEArLZ7K9LS0tbAOC/AEqlUtx13VNBEIgoikgpBVmWKWNMSqfTzWg02qKUouM4QUdHR1dvb68+PT3t37YmAABQSmVZlhVN05ht244kSS7nHHzfJ6FQCMLhcEApRcuyGPlLzwghoKpqwTTNJzegsbGxC8uy+gYHBy+q1WqqUqnwIAg8QRAQAAgAkCAIQBRF3zAMs1wuv6mq6muSJD2IxWLf6Lr+Ofl7L2MA0A8Aj3d3d99aXV1dPD099ZLJZDsIAoqIQAgBSmmg63pwdnaWuLy85K7rWpxz4+TkpOs6/gMAeIyIzzc2NgTP8z7inPNWq2VTSpFzDgBA2u02IYTQUqn0RxAE2t7eXjSTyQg31jKZzGe6rneqqvp1d3f3dDqd5pxzixCiua7r2rbd1jQNbdummqZpo6OjH09OTl6en5/PxmKx72/uaH5+fmdnZ6fPcRxbVVXM5XI4MzPDi8Xi06Ojo3ClUuGWZVmIKCiKklIU5YO1tbWvACAJAA0AsAQAgP7+/t91XU96niczxlhPT8/zUqn0ycDAwLeGYbxeq9U+rFareVmWW61WCyzLShBCHEQ8v46fAgDIsnwsSRLE4/FWNBpljUaDLS8v/wAAvywuLj7a39+XKaXE87zAMAyo1+uh8fFxfueO8vn8z41G423f9wkims1mU0DEYQB4uL29/Wo8Hs8XCoXLRCJhh8PhQJZlKxaL4R3Q3Nzcj7Ozs98BwEsAIPq+D77v/wYAsL6+bjLGnnDOH1FKjwkhNmNss1wu333a/0N/AuMBkm1f8YP0AAAAAElFTkSuQmCC)";
	navigator.palette.appendChild(btn);
	var toolbars = document.querySelectorAll("toolbar");
	Array.slice(toolbars).forEach(function (toolbar) {
		var currentset = toolbar.getAttribute("currentset");
		if (currentset.split(",").indexOf("pluginButton") < 0) return;
		toolbar.currentSet = currentset;
		try {
			BrowserToolboxCustomizeDone(true);
		} catch (ex) {
		}
	});

	function showPluginList(node){
		node = node.target;
		while (node.hasChildNodes()) {
			node.removeChild(node.lastChild);
		}
		var AddonManager = Components.utils.import('resource://gre/modules/AddonManager.jsm').AddonManager;
		AddonManager.getAddonsByTypes(["plugin"], function(plugin){
			var item = [];
			for(var i=0;i<plugin.length;i++){
				item[i] = node.appendChild(document.createElement("menuitem"));
				item[i].setAttribute("label",plugin[i].name);
				item[i].setAttribute("type","checkbox");
				item[i].setAttribute("checked", !plugin[i].userDisabled);
				item[i].setAttribute("Disabled", plugin[i].appDisabled);
				item[i].setAttribute("pluginID", plugin[i].id);
				item[i].onclick = function(evt){
					AddonManager.getAddonByID(evt.target.getAttribute("pluginID"), function(p) {
						p.userDisabled = p.userDisabled ? false : true;
					});
				}
			}
		});
	}
})();