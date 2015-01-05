/***********************************************************************
*PointDownload
*Copyright (C) 2014~2015  PointTeam
*
* Author:     Match <2696627729@qq.com>
* Maintainer: Match <2696627729@qq.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

#ifndef DATATYPE_H
#define DATATYPE_H

enum DownloadType
{
    dl_downloading,
    dl_downloaded,
    dl_trash,
    dl_search
};

enum DownloadState
{
    dlstate_downloading,
    dlstate_suspend,
    dlstate_ready
};

enum OperationType
{
    download_suspend,
    download_resume,
    download_redownload,
    download_priority,
    download_trash,
    download_delete,
    download_openFolder,
    download_offlineDownload,
    download_hightSpeedChannel,
    download_finishDownload
};

enum ProtocalType
{
    point_http,
    point_ftp,
    point_ed2k,
    point_bt
};

struct DownloadingItemInfo
{
    QString downloadURL;
    QString downloadSpeed;
    QString uploadSpeed;
    QString thunderOfflineSpeed;
    QString thunderHightSpeed;
    DownloadState downloadState;
    double downloadPercent;
};

#endif // DATATYPE_H
