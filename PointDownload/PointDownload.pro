#/***********************************************************************
#*PointDownload
#*Copyright (C) 2014  PointTeam
#*
#*
#* This program is free software: you can redistribute it and/or modify
#* it under the terms of the GNU General Public License as published by
#* the Free Software Foundation, either version 3 of the License, or
#* any later version.
#*
#* This program is distributed in the hope that it will be useful,
#* but WITHOUT ANY WARRANTY; without even the implied warranty of
#* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#* GNU General Public License for more details.
#*
#* You should have received a copy of the GNU General Public License
#* along with this program.  If not, see <http://www.gnu.org/licenses/>.
# ***********************************************************************/

QT += xml
QT += network
QT += widgets
QT += core
QT += quick
QT += gui
QT += multimedia
#CONFIG += static

#Add support for unity menu------------------------------------------------------------------------------------------------------
CONFIG += link_pkgconfig
PKGCONFIG += gtk+-2.0 glib-2.0 appindicator-0.1
#Add support for unity menu done--------------------------------------------------------------------------------------------------------

# Add more folders to ship with the application, here
folder_01.source = qml/PointDownload
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    Controler/middlesender.cpp \
    Controler/monitorClipBoard.cpp \
    Controler/peventfilter.cpp \
    Controler/settingcontroler.cpp \
    Controler/topcontrl.cpp \
    Controler/urlserver.cpp \
    SysData/getspeed.cpp \
    XMLHandler/xmloperations.cpp \
    SysData/dataflow.cpp \
    Controler/downloaddatasender.cpp \
    Download/unifiedinterface.cpp \
    Download/Aria2Task/a2ia2task.cpp \
    Download/PointTask/HttpTask/httpthread.cpp \
    Download/PointTask/pointtask.cpp \
    Download/YouGetTask/yougetprocess.cpp \
    Download/YouGetTask/yougettask.cpp \
    Download/PointTask/HttpTask/httptask.cpp \
    Download/PointTask/HttpTask/httpthreadmanager.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

RESOURCES += \
    resources.qrc

HEADERS += \
    Controler/middlesender.h \
    Controler/monitorClipBoard.h \
    Controler/peventfilter.h \
    Controler/settingcontroler.h \
    Controler/topcontrl.h \
    Controler/urlserver.h \
    SysData/getspeed.h \
    XMLHandler/xmloperations.h \
    SysData/dataflow.h \
    Controler/downloaddatasender.h \
    Download/unifiedinterface.h \
    Download/DataType.h \
    Download/Aria2Task/a2ia2task.h \
    Download/PointTask/pointtask.h \
    Download/YouGetTask/yougetprocess.h \
    Download/YouGetTask/yougettask.h \
    Download/PointTask/HttpTask/httpthread.h \
    Download/PointTask/HttpTask/httptask.h \
    Download/PointTask/HttpTask/httpthreadmanager.h
include(./QtSingleApplication/qtsinglecoreapplication.pri)

TRANSLATIONS = PointDownload_zh_CN.ts
