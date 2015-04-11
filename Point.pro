TEMPLATE = subdirs
SUBDIRS = \
        PointDownload/PointDownload.pro\
        PointPopup/PointPopup.pro\
        #XwareStartUp/XwareStartUp.pro

isEmpty(PREFIX){
    PREFIX = /opt/Point
}

EXTENSIONDIR = $$PREFIX/Extensions
ICONDIR = $$PREFIX/PointDownload

ChromeExtension.files = ./PointChromeExtension/PointChromeExtension.crx
ChromeExtension.path = $$EXTENSIONDIR
FireFoxExtension.files = ./PointFirefoxExtension.xpi/PointFirefoxExtension.xpi
FileFoxExtension.path = $$EXTENSIONDIR
PointIcon.files = ./point.png
PointIcon.path = $$ICONDIR

INSTALLS += ChromeExtension FileFoxExtension PointIcon
