TEMPLATE = app

QT += qml quick widgets gui xml

SOURCES += main.cpp

RESOURCES += qml.qrc \
#    image.qrc \
    images.qrc

# QMAKE FLAGS
QMAKE_CXXFLAGS += -std=c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
#include(deployment.pri)

include(../PInterface/XmlHandler/XmlHandler.pri)
include(../PInterface/Message/Message.pri)
include(../PInterface/Task/Task.pri)
include(../PInterface/PDataType/PDataType.pri)
include(../PInterface/PEventFilter/PEventFilter.pri)

HEADERS += 

DISTFILES += \
    qml/PointPopup/main.qml \
    qml/PointPopup/SearchBar/SearchBar.qml \
    qml/PointPopup/SearchBar/SearchBar.qml.autosave \
    qml/PointPopup/SearchBar/SearchInput.qml \
    qml/PointPopup/SearchBar/ToolsComboBox.qml \
    qml/PointPopup/SearchBar/AnalyzeButton.qml \
    qml/PointPopup/FilePanel/FileListPage.qml \
    qml/PointPopup/FilePanel/FileInfoItem.qml \
    qml/PointPopup/FilePanel/CheckButton.qml \
    qml/PointPopup/ContentPanel.qml \
    qml/PointPopup/ControlPanel/ControlPage.qml \
    qml/PointPopup/ControlPanel/ValueInput.qml
