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
#include "monitorClipBoard.h"
#include <QtQml>
#include "qdebug.h"

MonitorClipBoard::MonitorClipBoard()
{
    //import时使用Singleton.MonitorClipBoard
    qmlRegisterSingletonType<MonitorClipBoard>("Singleton.MonitorClipBoard", 1, 0, "MonitorClipBoard", clipboardObj);

    setTmpURL("");
    clipBoard = QApplication::clipboard();
    connect( clipBoard, SIGNAL( dataChanged() ), this, SLOT( slot_clipDataChange() ) );
}

MonitorClipBoard * MonitorClipBoard::monitorClipBord = NULL;
MonitorClipBoard * MonitorClipBoard::getInstance()
{
    if (monitorClipBord == NULL)
        monitorClipBord = new MonitorClipBoard();
    return monitorClipBord;
}

void MonitorClipBoard::slot_clipDataChange()
{
    setTmpURL(clipBoard->text());
}


QString MonitorClipBoard::getTmpURL()
{
    return tmpURL;
}

void MonitorClipBoard::setTmpURL(QString URL)
{
    tmpURL = URL;
    emit tmpURLChange();
}
