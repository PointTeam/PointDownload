#PointChromeExtension

##功能:
 检测Chrome浏览器的下载动作，捕获下载链接后，启动弹出窗口并将捕获的下载链接传递至弹出窗，其中支持的链接包括：
>- 普通的http、ftp、磁力链接等
>- 迅雷专用链接、QQ旋风等特殊链接
>- You-Get支持的视频网站链接（单击插件图标，使用“下载本页视频”选项下载）

##开发:
>- 	Extension文件夹以及其中包含的文件是扩展的主体部分
>- 	PointExtension.pem是该扩展的私有秘钥，在打包时用到
>-    pointdownload.json是扩展与本地程序通信所需要的配置文件,文件名请不要使用大写字母,请将此文件放置于/etc/opt/chrome/native-messaging-hosts路径下
>- 	nkbchchceepbameamioagcjlhnghdoff.json用于扩展的自动安装，此文件名前缀为此扩展在Chrome上显示的扩展id,将此文件放置于/opt/google/chrome/extensions路径下,Chrome会在每次启动时按照配置信息自动安装该扩展(注意该文件中的“external_version”字段，版本号必须与插件版本号相同).
###==请注意以上列举的文件的读写权限==