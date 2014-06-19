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
/*************************************************************************************
Date:   2014.5.4~2014.5.5
Description:
    事件过滤器，监控整个项目的事件，当检测到用户按下Enter键时立即通知qml界面做相应事件
（传递数据到主程序并且使自身退出）。这是一个单例类，为的是
    使监控时所使用的对象跟qml中接收事件通知的是同一个对象，这样才能保证数据是同步的
Others:

History:
*************************************************************************************/

#ifndef PCLOSEEVENTFILTER_H
#define PCLOSEEVENTFILTER_H

#include <QObject>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QQmlEngine>
#include <QApplication>

class PEventFilter : public QObject
{
    Q_OBJECT
public:

    static PEventFilter * getInstance();        //返回该类的单例对象
protected:
    bool eventFilter(QObject *obj, QEvent *ev); //过滤事件

signals:
    void sendEnterKeyChange();                  //发送一个信号到qml界面通知其已获得Enter的按下事件
    void sendEscKeyChange();

private:
    static PEventFilter * peventFilter;         //单例对象
    explicit PEventFilter(QObject *parent = 0); //构造函数


};

//将单例对象注册到qml中使用的回调函数
static QObject * pEventObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return PEventFilter::getInstance();
}


#endif // PCLOSEEVENTFILTER_H
