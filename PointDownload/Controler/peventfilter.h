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

#ifndef PCLOSEEVENTFILTER_H
#define PCLOSEEVENTFILTER_H

#include <QObject>
#include <QDebug>
#include <QEvent>
#include <QQmlEngine>
#include <QApplication>

class PEventFilter : public QObject
{
    Q_OBJECT

    //将c++数据暴露给qml使用
    Q_PROPERTY(int globalX  READ getGlobalX WRITE setGlobalX NOTIFY globalXChange)
    Q_PROPERTY(int globalY  READ getGlobalY WRITE setGlobalY NOTIFY globalYChange)
public:
    static PEventFilter * getInstance();

    int getGlobalX();
    void setGlobalX(int value);
    int getGlobalY();
    void setGlobalY(int value);

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
private:
    explicit PEventFilter(QObject *parent = 0);

private:
    static PEventFilter * pEventFilter;
    int globalX;
    int globalY;

signals:
    void globalXChange();
    void globalYChange();

public slots:

};

//将单例对象注册到qml中使用的回调函数
static QObject * eventFilterObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return PEventFilter::getInstance();
}

#endif // PCLOSEEVENTFILTER_H
