TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp

# Default rules for deployment.
include(deployment.pri)


isEmpty(PREFIX){
    PREFIX = /opt/Point
}

BINDIR = $$PREFIX/PointDownload

target.path = $$BINDIR
INSTALLS += target
