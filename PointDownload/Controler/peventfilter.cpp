/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
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

#include "peventfilter.h"
#include <QtQml>

PEventFilter::PEventFilter(QObject *parent) :
    QObject(parent)
{
    //import时使用Singleton.DataControler，在获取内容或调用函数时使用PEventFilter
    qmlRegisterSingletonType<PEventFilter>("Singleton.PEventFilter", 1, 0, "PEventFilter", eventFilterObj);
}

PEventFilter * PEventFilter::pEventFilter = NULL;
PEventFilter * PEventFilter::getInstance()
{
    if (pEventFilter == NULL)
    {
        pEventFilter  = new PEventFilter();
    }
    return pEventFilter;
}

int PEventFilter::getGlobalX()
{
    return globalX;
}

void PEventFilter::setGlobalX(int value)
{
    globalX = value;
}

int PEventFilter::getGlobalY()
{
    return globalY;
}

void PEventFilter::setGlobalY(int value)
{
    globalY = value;
}

bool PEventFilter::eventFilter(QObject *obj, QEvent *event)
{
//    if (event->type() == QEvent::Close)
//    {
//        qDebug() << "close";
//        return true;
//    }
    if (event->type() == QEvent::KeyPress)
    {
        return QObject::eventFilter(obj, event);
    }
    else if (event->type() == QEvent::MouseMove)
    {
        globalX = QCursor::pos().x();
        globalY = QCursor::pos().y();
        return QObject::eventFilter(obj, event);
    }
    else
    {
        return QObject::eventFilter(obj, event);
    }
}
