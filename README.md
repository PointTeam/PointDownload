#PointDownload

**点载,是一个能帮助你方便地从网络上下载各种文件的软件。现在已经支持主流的各种下载协议，包括迅雷的thunder://和QQ旋风的下载协议。
当前提供的软件安装包支持的操作系统有：LinuxDeepin2014, Ubuntu14.04, UbuntuKy14.04.
安装包在[LinuxDeepin论坛页面](http://www.linuxdeepin.com/forum/23/21124) 发布，提供下载
其他Linux发行版本的安装包暂时没有提供，因为开发和维护人员有限，如果您能帮助我们打包和维护其他Linux发行版本的安装包，请与我们联系！**

##程序截图
![DownloadingPage](https://github.com/PointTeam/PointDownload/blob/gh-pages/images/PointDownloadScreenshot/PointDownloadMainUI/downloading.png  "DownloadingPage")

##开发指南

###开发环境：>=Qt5.2.1
###项目模块：
- 此项目共分为PointDownload、PointPopup、PointChromeExtension和PointFirefoxExtension4个模块，未来可能还会增加或者删除其他模块以支持更多功能的需要。
- PointDownload是主程序部分，负责下载和管理的工作，更详细信息请查阅该模块[说明页面](https://github.com/PointTeam/PointDownload/wiki/PointDownload%E4%B8%BB%E7%A8%8B%E5%BA%8F%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97) ；
- PointPopup是下载前配置弹出窗，负责接受浏览器插件传递的URL信息(或者点击新建按钮由用户填入URL信息),并根据URL获取文件名、文件大小等信息显示，为用户确定下载做准备, 用户确定下载后将信息传递给主程序，由主程序进行下载，更详细信息请查阅该模块的[说明页面](https://github.com/PointTeam/PointDownload/wiki/PointPopup-%E5%BC%B9%E5%87%BA%E7%AA%97%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97) ；
- PointChromeExtension是Chrome扩展模块，更详细信息请参考其中的[说明页面](https://github.com/PointTeam/PointDownload/wiki/PointChromeExtension%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97) ；
- PointFirefoxExtension是FireFox扩展模块，更详细信息请参考其中的[说明页面](https://github.com/PointTeam/PointDownload/wiki/PointFirefoxExtension%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97) 。

###其他组件：
- Aria2:请参照[Aria2说明页面](https://github.com/PointTeam/PointDownload/wiki/Aria2%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E) 
- Xware(迅雷)：请参照[Xware(迅雷)说明页面](https://github.com/PointTeam/PointDownload/wiki/Xware(%E8%BF%85%E9%9B%B7)%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E) 
- You-Get：请参照[You-Get说明页面](https://github.com/PointTeam/PointDownload/wiki/%E4%BD%BF%E7%94%A8You-Get%E4%B8%8B%E8%BD%BD%E5%9C%A8%E7%BA%BF%E8%A7%86%E9%A2%91) 
