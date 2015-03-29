INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD
HEADERS+= \
    $$PWD/taskinfo.h \
    $$PWD/taskfileitem.h \
    $$PWD/task.h
		
SOURCES+= \
    $$PWD/taskinfo.cpp \
    $$PWD/taskfileitem.cpp \
    $$PWD/task.cpp

include(../PDataType/PDataType.pri)
