/**
 *  Author: sbwtw <sbwtws@gmail.com>
 *
 *  数据格式化工具函数库
 * */

// 格式化文件大小
function formatFileSize(size)
{
    if (size < 10000)
        return size.toFixed(0) + "B";

    size /= 1024;

    if (size < 1024)
        return size.toFixed(2) + "KB";

    size /= 1024;

    if (size < 1024)
        return size.toFixed(2) + "MB";

    size /= 1024;

    return size.toFixed(2) + "GB";
}

// 格式化下载速度
function formatDownloadSpeed(size)
{
    if (size < 10000)
        return size.toFixed(0) + " B/s";

    size /= 1024;

    if (size < 1024)
        return size.toFixed(0) + " KB/s";

    size /= 1024;

    return size.toFixed(2) + " MB/s";
}
