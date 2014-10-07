/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Choldrim <choldrim@foxmail.com>
* Maintainer: Choldrim <choldrim@foxmail.com>
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

#ifndef XWAREDATATYPE_H
#define XWAREDATATYPE_H

#include <QString>

enum XwareTaskState
{
    x_dload,
    x_pause,
    x_wait,  // 等待就绪
    x_other
};

enum XwareLoginResultType
{
    x_LoginSuccess,
    x_UserDoesNotExist,
    x_PasswordError,
    x_UserOrPwdError,
    x_LoginTimeOut,
    x_Logout
};

enum XwareLoginState
{
    LoginNotReady = 0,
    LoginReady,
    Logining,
    Logined,
    LoginedAndBinded
};

struct XwareTaskInfo
{
    QString tid; // task ID
    QString name; // name
    QString size;  // size :  B (without unit)
    QString progress; // progress %
    QString speed; // speed
    QString remainTime;  // seconds
    XwareTaskState state;
    QString url; // url
    QString highChnlSpeed;
    QString offlineChnlSpeed;
//    QString uploadSpeed;
};



/*
taskStateClass: {
    0: "dload",
    8: "wait",
    9: "pause",
    10: "pause",
    11: "finish",
    12: "delete",
    13: "finish",
    14: "wait",
    15: "delete",
    16: "delete",
    37: "wait",
    38: "delete"
},
taskStateText: {
    0: "下载中",
    8: "等待中",
    9: "已停止",
    10: "已暂停",
    11: "已完成",
    12: "下载失败",
    13: "上传中",
    14: "提交中",
    15: "已删除",
    16: "已移至回收站",
    37: "已挂起",
    38: "发生错误"
}

LIST_TASK_VIPCHANNEL_TYPE_FREE3: 0,
LIST_TASK_VIPCHANNEL_TYPE_GREEN: 1,
LIST_TASK_VIPCHANNEL_TYPE_VIP: 2,
LIST_TASK_VIPCHANNEL_TYPE_UNAVAILABLE: -1,

LIST_TASK_VIPCHANNEL_OPENED_NOTUSED: 0,
LIST_TASK_VIPCHANNEL_OPENED_SUBMITTING: 1,
LIST_TASK_VIPCHANNEL_OPENED_ACTIVATED: 2,
LIST_TASK_VIPCHANNEL_OPENED_FAILED: 3,

LIST_TASK_LIXIANCHANNEL_STATE_NOTUSED: 0,
LIST_TASK_LIXIANCHANNEL_STATE_SUBMITTING: 1,
LIST_TASK_LIXIANCHANNEL_STATE_DOWNLOADING: 2,
LIST_TASK_LIXIANCHANNEL_STATE_ACTIVATED: 3,
LIST_TASK_LIXIANCHANNEL_STATE_FAILED: 4,

*/


#endif // XWAREDATATYPE_H
