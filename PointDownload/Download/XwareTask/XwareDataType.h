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

struct XwareTaskInfo
{
    QString tid; // task ID
    QString name; // name
    QString size;  // size :  xxGB/MB/KB
    QString progress; // progress %
    QString speed; // speed
    QString remainTime;
    XwareTaskState state;
    QString url; // url
    QString highChnlSpeed;
    QString offlineChnlSpeed;
//    QString uploadSpeed;
};


#endif // XWAREDATATYPE_H
