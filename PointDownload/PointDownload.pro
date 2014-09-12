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
QT += webkitwidgets
#CONFIG += static


#Get distributions type
DISTRIBUTION_NAME = $$system(cat /etc/os-release)
contains(DISTRIBUTION_NAME,suse){DEFINES+=LINUX_LIKE_SUSE}
contains(DISTRIBUTION_NAME,debian){DEFINES+=LINUX_LIKE_DEBIAN}
 exists(/etc/arch-release ) {DEFINES+=LINUX_LIKE_ARCH}
 exists(/etc/redhat-release ) {DEFINES+=LINUX_LIKE_REDHAT}
 exists(/etc/gentoo-release ) {DEFINES+=LINUX_LIKE_GENTOO}


#Get Desktop Environment
DESKTOP_ENVIRONMENT = $$system(echo $DESKTOP_SESSION)
contains(DESKTOP_ENVIRONMENT,[Uu]buntu){DEFINES+=DESKTOP_ENV_UBUNTU}

#Add support for unity menu------------------------------------------------------------------------------------------
contains(DESKTOP_ENVIRONMENT,[Uu]buntu){CONFIG += link_pkgconfig}
contains(DESKTOP_ENVIRONMENT,[Uu]buntu){PKGCONFIG += gtk+-2.0 glib-2.0 appindicator-0.1}
#Add support for unity menu done---------------------------------------------------------------------------------------

#is gksudo or kdesu  exist
GKSUDO_EXIST = $$system(command -v gksudo)
contains(GKSUDO_EXIST,gksudo){DEFINES+=GKSUDO_EXIST}
KDESU_EXIST = $$system(command -v kdesu)
contains(KDESU_EXIST,kdesu){DEFINES+=KDESU_EXIST}

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
    Controler/topcontrl.cpp \
    Controler/urlserver.cpp \
    SysData/getspeed.cpp \
    SysData/dataflow.cpp \
    Download/unifiedinterface.cpp \
    Download/Aria2Task/a2ia2task.cpp \
    Download/PointTask/HttpTask/httpthread.cpp \
    Download/PointTask/pointtask.cpp \
    Download/YouGetTask/yougetprocess.cpp \
    Download/YouGetTask/yougettask.cpp \
    Download/PointTask/HttpTask/httptask.cpp \
    Download/PointTask/HttpTask/httpthreadmanager.cpp \
    XMLHandler/downloadxmlhandler.cpp \
    XMLHandler/settingxmlhandler.cpp \
    Controler/SettingWin/settingcontroler.cpp \
    Controler/SettingWin/yougetsettingcontroler.cpp \
    Controler/SettingWin/dropzonesettingcontroler.cpp \
    Controler/SettingWin/xwaresettingcontroler.cpp \
    Download/XwareTask/xwarecontroller.cpp \
    Download/XwareTask/xwarepopulateobject.cpp \
    Download/XwareTask/xwaretask.cpp \
    Download/XwareTask/xwarewebcontroller.cpp \
    Download/XwareTask/mynetworkaccessmanager.cpp \
    Download/XwareTask/mywebview.cpp \
    Download/XwareTask/xwaretaskentity.cpp \
    Controler/dldataconverter.cpp \
    Download/XwareTask/webctrlviewtest.cpp \
    Controler/Message/normalnotice.cpp \
    Download/XwareTask/completedlistwebview.cpp \
    Download/XwareTask/xwaresetting.cpp

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
    Controler/topcontrl.h \
    Controler/urlserver.h \
    SysData/getspeed.h \
    SysData/dataflow.h \
    Download/unifiedinterface.h \
    Download/DataType.h \
    Download/Aria2Task/a2ia2task.h \
    Download/PointTask/pointtask.h \
    Download/YouGetTask/yougetprocess.h \
    Download/YouGetTask/yougettask.h \
    Download/PointTask/HttpTask/httpthread.h \
    Download/PointTask/HttpTask/httptask.h \
    Download/PointTask/HttpTask/httpthreadmanager.h \
    XMLHandler/downloadxmlhandler.h \
    XMLHandler/settingxmlhandler.h \
    Controler/SettingWin/settingcontroler.h \
    Controler/SettingWin/yougetsettingcontroler.h \
    Controler/SettingWin/dropzonesettingcontroler.h \
    Controler/SettingWin/xwaresettingcontroler.h \
    Download/XwareTask/XwareConstants.h \
    Download/XwareTask/xwarecontroller.h \
    Download/XwareTask/XwareDataType.h \
    Download/XwareTask/xwarepopulateobject.h \
    Download/XwareTask/xwaretask.h \
    Download/XwareTask/xwarewebcontroller.h \
    Download/XwareTask/mynetworkaccessmanager.h \
    Download/XwareTask/mywebview.h \
    Download/XwareTask/xwaretaskentity.h \
    Controler/dldataconverter.h \
    Download/XwareTask/webctrlviewtest.h \
    Controler/Message/normalnotice.h \
    Download/XwareTask/completedlistwebview.h \
    Download/XwareTask/xwaresetting.h
include(./QtSingleApplication/qtsinglecoreapplication.pri)

TRANSLATIONS += PointDownload_zh_CN.ts
TRANSLATIONS += PointDownload_ja_JP.ts
