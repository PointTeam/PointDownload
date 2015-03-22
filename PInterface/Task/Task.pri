INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD
HEADERS+= \
    $$PWD/taskinfo.h \
    $$PWD/taskfileitem.h \
    $$PWD/task.h \
    $$PWD/YouGetTask/yougettask_.h
		
SOURCES+= \
    $$PWD/taskinfo.cpp \
    $$PWD/taskfileitem.cpp \
    $$PWD/task.cpp \
    $$PWD/YouGetTask/yougettask_.cpp

include(../PDataType/PDataType.pri)
