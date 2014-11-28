PointMask为PointDownload做了一个对C语言函数的掩盖和替换
可以自行编译成so文件，但须要在32位的linux系统下进行编译，因为xware是一个32位的固件，所以相应的也须要32位的so文件。
编译命令：
#gcc -Wall -fPIC -shared mask.c -o mask.so -ldl
（编译好的so文件已经包含在xware固件中，在启用迅雷功能时会自行下载，不必再另外编译）

PointMask is to do a mask and replacement for PointDownload baseed on some C function.
It can be compiled into so file, but also need to be compiled in 32-bit Linux systems, because the xware is a 32-bit firmware, so the corresponding also requires a 32-bit so file.
Compile command:
#gcc -Wall -fPIC -shared mask.c -o mask.so -ldl
(The compiled so file has been included in the xware firmware, it will be downloaded with enabling Thunder, do not need another compilation)