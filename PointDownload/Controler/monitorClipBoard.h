/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     起点 <88231398@qq.com>
* Maintainer: 起点 <88231398@qq.com>
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
Date:   2014.4.30
Description:
    这个类(单例)负责监控粘贴板上的内容,若粘贴板上的内容为有效URL时，发射有效信号
Others:
Function list:
History:
************************************************************************/
#ifndef MONITORCLIPBOARD_H
#define MONITORCLIPBOARD_H

#include <qobject.h>
#include <QClipboard>
#include <QtWidgets/qapplication.h>
#include "Controler/downloaddatasender.h"
#include "XMLHandler/xmloperations.h"

class MonitorClipBoard : public QObject
{
    Q_OBJECT
public:
    explicit MonitorClipBoard();

public slots:
    void slot_clipDataChange();

private:
    QClipboard * clipBoard;                                        //粘贴板

};

#endif // MONITORCLIPBOARD_H
