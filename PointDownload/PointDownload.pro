TEMPLATE = app

QT += qml quick

SOURCES += main.cpp

RESOURCES += qml.qrc \
    image.qrc \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    qml/PointDownload/Widgets/ControlButtonLine.qml \
    qml/PointDownload/Widgets/FileControlButton.qml \
    qml/PointDownload/Widgets/FileListPanel.qml \
    qml/PointDownload/Widgets/HeadInfoItem.qml \
    qml/PointDownload/Widgets/ImageButton.qml \
    qml/PointDownload/Widgets/RotatingRectangle.qml \
    qml/PointDownload/ContentPanel.qml \
    qml/PointDownload/main.qml \
    qml/PointDownload/TrashPanel/TrashFileItem.qml \
    qml/PointDownload/TrashPanel/TrashMainFrame.qml \
    qml/PointDownload/TopPanel/MiddleMenu.qml \
    qml/PointDownload/TopPanel/MiddleMenuItem.qml \
    qml/PointDownload/TopPanel/RightMenu.qml \
    qml/PointDownload/TopPanel/RightMenuItem.qml \
    qml/PointDownload/TopPanel/TopBar.qml \
    qml/PointDownload/TaskPanel/TaskFileItem.qml \
    qml/PointDownload/TaskPanel/TaskMainFrame.qml \
    qml/PointDownload/SettingPanel/SettingFrame.qml \
    qml/PointDownload/DonePanel/DoneFileItem.qml \
    qml/PointDownload/DonePanel/DoneMainFrame.qml
