#PointDownload主程序模块

##说明：
该模块主要由C++和qml编写，由C++文件，qml文件，资源文件和js文件组成。请使用Qt5.2.1或者以上版本的SDK进行开发，在不同的操作系统的不同桌面环境下可能会出现不同的问题，请根据提示解决，无法解决的请与我们联系

##文件结构：
###C++：
- 	Controler:主要负责与控制有关的模块，如事件监听，退出等
>- 	Message：与消息提醒有关的类
>- 	SettingWin：与设置窗口相关的类
>- 	dldataconverter类：负责C++与下载列表的QML页面进行数据和控制转换
>- 	middlesender类：负责C++与主窗口上方的流量、网速等QML数据转换更新
>- 	monitorclipboard类：负责监听剪切板，并将符合下载链接类型的URL存储起来给弹出窗口使用
>- 	peventfilter类：该类过滤全局的事件，目前只做鼠标坐标的捕捉，未来将会把快捷键功能加入其中,需要在main函数中使用installEventFilter方法注册过滤器
>- 	topcontrl类：负责系统托盘和关闭程序等操作，与QML交互
>- 	urlserver类：开启localsocket，等待弹出窗主动把下载链接和分析后的信息传入主程序中进行下载
- 	Download
>- Aria2Task：负责Aria2后端下载任务
>- PointTask：负责Point后端下载任务
>- XwareTask：负责Xware后端下载任务
>- YouGetTask：负责YouGet后端下载任务
>- UnifiedInterface类：这是主程序最主要的接口，这是一个单例类，下载任务的管理都由这个类来处理
>- DataType.h文件：一些结构体和枚举类型
-	SysData
>- dataflow类：负责下载流量统计
>- getspeed类：负责网速、CPU、磁盘使用率统计
-	XMLHandler
>- downloadxmlhandler类:负责读写下载项（正在下载、已下载、垃圾桶）配置文件
>- settingxmlhandler类：负责读写软件整体配置文件，如是否立即关闭程序、是否启用悬浮创等配置信息
###QML: