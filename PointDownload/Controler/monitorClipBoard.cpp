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
#include "qdebug.h"

MonitorClipBoard::MonitorClipBoard()
{
    clipBoard = QApplication::clipboard();
    connect( clipBoard, SIGNAL( dataChanged() ), this, SLOT( slot_clipDataChange() ) );
}

void MonitorClipBoard::slot_clipDataChange()
{
    QString URL = clipBoard->text();

    XMLOperations tmpOPera;
    if (tmpOPera.getMainConfig().clipboard == "true")
    {
        //在统一处理时判断是否是合法的URL
        DownloadDataSender::getInstance()->controlItem("dl_search","download_redownloed",URL);
    }
}
