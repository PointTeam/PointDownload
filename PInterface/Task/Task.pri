INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD
HEADERS+= \
    $$PWD/taskinfo.h \
    $$PWD/task.h \
    $$PWD/taskfileinfo.h
		
SOURCES+= \
    $$PWD/taskinfo.cpp \
    $$PWD/task.cpp \
    $$PWD/taskfileinfo.cpp

include(../PDataType/PDataType.pri)
