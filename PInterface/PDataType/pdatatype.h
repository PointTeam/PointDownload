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
/***********************************************************************
Date:   2014.5.31~
Description:
    App's all enum and structer define

Others:
    请使用驼峰式命名方式,此处数据将在程序全局使用
    所有的文件大小请以Byte为单位，速度以Byte/Second为单位,进度范围0~1

History:
************************************************************************/

#ifndef DATATYPE_H
#define DATATYPE_H

#include <QObject>

class PDataType : public QObject
{
    Q_OBJECT
    Q_ENUMS(DownloadType)
    Q_ENUMS(TaskState)
    Q_ENUMS(OperationType)
    Q_ENUMS(ProtocalType)
    Q_ENUMS(ToolType)

public:
    explicit PDataType(QObject *parent = 0) : QObject(parent){}
    ~PDataType(){}

    enum ToolType
    {
        PToolTypePoint,
        PToolTypeYouGet,
        PToolTypeAria2,
        PToolTypeXware,
        PToolTypeUndefined
    };

    enum DownloadType
    {
        PDLTypeDownloading,
        PDLTypeDownloaded,
        PDLTypeDownloadTrash
    };

    enum TaskState
    {
        PTaskStateDownloading,
        PTaskStateSuspend ,
        PTaskStateBlock ,
        PTaskStateError
    };

    enum ProtocolType{
        HTTP,
        HTTPS,
        FTP,
        BitTorrent,
        Metalink,
        Magnet,
        Ed2k,
        YouGet
    };

    enum OperationType
    {
        PCtrlTypeFinishDownload,
        PCtrlTypeSuspend,
        PCtrlTypeResume,
        PCtrlTypeReDownload,
        PCtrlTypeRaise,
        PCtrlTypeTrash,
        PCtrlTypeDelete,
        PCtrlTypeOpenFolder,
        PCtrlTypeOfflineDownload,
        PCtrlTypeHightSpeedChannel
    };

    enum ProtocalType
    {
        PProtHttp,
        PProtFtp,
        PProtEd2k,
        PProtBt,
        PProtMagnet
    };
};


struct TaskItemInfo
{
    QString fileID;
    int taskDLSpeed;
    int taskULSpeed;
    int thunderOfflineSpeed;
    int thunderHightSpeed;
    PDataType::TaskState taskState;
    double taskProgress;    //0~1
};
Q_DECLARE_METATYPE(TaskItemInfo)

#endif // DATATYPE_H
