#PointDownload

**点载,是一个能帮助你方便地从网络上下载各种文件的软件。现在已经支持主流的各种下载协议，包括迅雷的thunder://和QQ旋风的下载协议。
当前提供的软件安装包支持的操作系统有：LinuxDeepin2014, Ubuntu14.04, UbuntuKy14.04.
安装包在[LinuxDeepin论坛页面](http://www.linuxdeepin.com/forum/23/21124) 发布，提供下载
其他Linux发行版本的安装包暂时没有提供，因为开发和维护人员有限，如果您能帮助我们打包和维护其他Linux发行版本的安装包，请与我们联系！**


##开发指南

###开发环境：>=Qt5.2.1
###项目模块：
- 此项目共分为PointDownload、PointPopup、PointChromeExtension和PointFirefoxExtension4个模块，未来可能还会增加或者删除其他模块以支持更多功能的需要。
- PointDownload是主程序部分，负责下载和管理的工作，更详细信息请查阅该模块的READ.MD文件；
- PointPopup是下载前配置弹出窗，负责接受浏览器插件传递的URL信息(或者点击新建按钮由用户填入URL信息),并根据URL获取文件名、文件大小等信息显示，为用户确定下载做准备, 用户确定下载后将信息传递给主程序，由主程序进行下载，更详细信息请查阅该模块的READ.MD文件；
- PointChromeExtension是Chrome扩展模块，更详细信息请参考其中的README.MD说明；
- PointFirefoxExtension是FireFox扩展模块，更详细信息请参考其中的README.MD说明。
