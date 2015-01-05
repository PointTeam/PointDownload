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

#include "peventfilter.h"
#include <QtQml>

/**************************************************************************************************
Function: PEventFilter()
Description:
    构造函数，必须在构造函数中注册该单例对象，否则qml中无法使用该类的对象，在qml中存在该类的一个单独的
对象，所以是不需要再在qml中构造该对象的组建的
Calls:
    1.qmlRegisterSingletonType
Input:
Output:
Return:
Others:
**************************************************************************************************/
PEventFilter::PEventFilter(QObject *parent) :
    QObject(parent)
{
    //import时使用Singleton.PEventFilter，在获取内容或调用函数时使用PEventFilter
    qmlRegisterSingletonType<PEventFilter>("Singleton.PEventFilter", 1, 0, "PEventFilter", pEventObj);
}

//构建单例对象
PEventFilter * PEventFilter::peventFilter = new PEventFilter();


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

/**************************************************************************************************
Function: eventFilter()
Description:
    事件过滤器，当用户按下Enter键时立即发送信号到qml界面中进行处理
Calls:
Input:
Output:
Return:
Others:
    1)按下enter键会触发两次事件，原因未知，所以要加一个pressed变量控制
**************************************************************************************************/
bool pressed = false;
bool PEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        //Key_Enter通常位于小键盘上
        if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
        {
            if (!pressed)
            {
                pressed = true;
                emit sendEnterKeyChange();
            }
        }
        else if (keyEvent->key() == Qt::Key_Escape)
        {
            emit sendEscKeyChange();
        }
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

    return false;
}


PEventFilter * PEventFilter::getInstance()
{
    return peventFilter;
}

QObject *PEventFilter::pEventObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return PEventFilter::getInstance();
}
