import QtQuick 2.0
import Singleton.PEventFilter 1.0
import Singleton.TopContrl 1.0
import Singleton.DLDataConverter 1.0
import Singleton.MonitorClipBoard 1.0
import "../SettingWin/SettingWin.js" as SettingScript

Image{
    id:outerImg
    source: "qrc:/images/dropzone/tback"

    property bool menuShowed:false
    property real animationDuration: 700

    state: "hideAllMenu"

    signal menuButtonHover(string buttonTips)

    Timer{
        id:destroyTimer
        interval: animationDuration
        repeat: false
        onTriggered: destroyAll()
    }

    SectorWidget{
        id:showMainSector
        startAngle: Math.PI / 2 + Math.PI - Math.PI / 6
        endAngle: Math.PI / 2 + Math.PI + Math.PI / 6
        iconPath: "qrc:/images/dropzone/maxsize"
        MouseArea{
            width: parent.width / 3
            height: 30
            hoverEnabled: true
            anchors {horizontalCenter: parent.horizontalCenter}
            onClicked: {
                TopContrl.showMainWindow()
                TopContrl.updateShowState(true)
            }
            onEntered: outerImg.menuButtonHover(qsTr("Main"))
            onExited:outerImg.menuButtonHover("")
        }
    }

    SectorWidget{
        id:jobControlSector
        startAngle: showMainSector.startAngle
        endAngle: showMainSector.endAngle
        iconPath: /*DownloadDataSender.isAllSuspend?"qrc:/images/dropzone/startall":*/"qrc:/images/dropzone/stopall"
        MouseArea{
            width: parent.width / 3
            height: 30
            hoverEnabled: true
            anchors {horizontalCenter: parent.horizontalCenter}
            onClicked: {
                if (jobControlSector.iconPath == "qrc:/images/dropzone/startall")
                {
                    DLDataConverter.resumeAllDownloading()
                    jobControlSector.iconPath = "qrc:/images/dropzone/stopall"
                }
                else
                {
                    DLDataConverter.suspendAllDownloading()
                    jobControlSector.iconPath = "qrc:/images/dropzone/startall"
                }
                updateMenuState()
            }
            onEntered: {
                if (jobControlSector.iconPath == "qrc:/images/dropzone/startall")
                    outerImg.menuButtonHover(qsTr("Resume All"))
                else
                    onEntered: outerImg.menuButtonHover(qsTr("SuspendAll"))
            }
            onExited:outerImg.menuButtonHover("")
        }
    }

    SectorWidget{
        id:newJobSector
        startAngle: showMainSector.startAngle
        endAngle: showMainSector.endAngle
        iconPath: "qrc:/images/dropzone/newjob"
        MouseArea{
            width: parent.width / 3
            height: 30
            hoverEnabled: true
            anchors {horizontalCenter: parent.horizontalCenter}
            onClicked: {
                updateMenuState()
                DLDataConverter.controlItem("dl_search","download_redownloed",MonitorClipBoard.tmpURL)
            }
            onEntered: outerImg.menuButtonHover(qsTr("NewTask"))
            onExited:outerImg.menuButtonHover("")
        }
    }

    SectorWidget{
        id:quitSector
        startAngle: showMainSector.startAngle
        endAngle: showMainSector.endAngle
        iconPath: "qrc:/images/dropzone/quit"
        MouseArea{
            width: parent.width / 3
            height: 30
            hoverEnabled: true
            anchors {horizontalCenter: parent.horizontalCenter}
            onClicked: {
                updateMenuState()
                destroyTimer.start()
            }
            onEntered: outerImg.menuButtonHover(qsTr("Quit"))
            onExited:outerImg.menuButtonHover("")
        }
    }

    SectorWidget{
        id:storageSector
        startAngle: showMainSector.startAngle
        endAngle: showMainSector.endAngle
        iconPath: "qrc:/images/dropzone/storage"
        MouseArea{
            width: parent.width / 3
            height: 30
            hoverEnabled: true
            anchors {horizontalCenter: parent.horizontalCenter}
            onClicked: {
                TopContrl.showSaveFolder()
                updateMenuState()
            }

            onEntered: outerImg.menuButtonHover(qsTr("Storage"))
            onExited:outerImg.menuButtonHover("")
        }

    }

    SectorWidget{
        id:settingSector
        startAngle: showMainSector.startAngle
        endAngle: showMainSector.endAngle
        iconPath: "qrc:/images/dropzone/setting"
        MouseArea{
            width: parent.width / 3
            height: 30
            hoverEnabled: true
            anchors {horizontalCenter: parent.horizontalCenter}
            onClicked: {
                SettingScript.showSettingWin(outerImg
                                             ,PEventFilter.globalX>270?PEventFilter.globalX-270:PEventFilter.globalX + outerImg.width - 20
                                             ,PEventFilter.globalY)
                updateMenuState()
            }
            onEntered: outerImg.menuButtonHover(qsTr("Setting"))
            onExited:outerImg.menuButtonHover("")
        }
    }

    states: [
        State {
            name: "showAllMenu"
            PropertyChanges { target: showMainSector; opacity: 1 }
            PropertyChanges { target: jobControlSector; opacity: 1; rotation:60 * 1 }
            PropertyChanges { target: newJobSector; opacity: 1 ; rotation: 60 * 2}
            PropertyChanges { target: quitSector; opacity: 1 ; rotation: 60 * 3}
            PropertyChanges { target: storageSector; opacity: 1 ; rotation: 60 * 4}
            PropertyChanges { target: settingSector; opacity: 1 ; rotation: 60 * 5}
        },
        State {
            name: "hideAllMenu"
            PropertyChanges { target: showMainSector; opacity: 0 }
            PropertyChanges { target: jobControlSector; opacity: 0; rotation:0 }
            PropertyChanges { target: newJobSector; opacity: 0 ; rotation: 0}
            PropertyChanges { target: quitSector; opacity: 0 ; rotation: 0}
            PropertyChanges { target: storageSector; opacity: 0 ; rotation: 0}
            PropertyChanges { target: settingSector; opacity: 0 ; rotation: 0}
        }

    ]

    transitions: [
        Transition {
            from: "hideAllMenu"
            to: "showAllMenu"
            PropertyAnimation { target: showMainSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
            PropertyAnimation { target: jobControlSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
            PropertyAnimation { target: newJobSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
            PropertyAnimation { target: quitSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
            PropertyAnimation { target: storageSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
            PropertyAnimation { target: settingSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
        },

        Transition {
            from: "showAllMenu"
            to: "hideAllMenu"
            PropertyAnimation { target: showMainSector; property: "opacity";from:1; to: 0.8; duration: animationDuration;}
            PropertyAnimation { target: showMainSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
            PropertyAnimation { target: jobControlSector; property: "opacity";from:1; to: 0.8; duration: animationDuration;}
            PropertyAnimation { target: jobControlSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
            PropertyAnimation { target: newJobSector; property: "opacity";from:1; to: 0.8; duration: animationDuration;}
            PropertyAnimation { target: newJobSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
            PropertyAnimation { target: quitSector; property: "opacity";from:1; to: 0.8; duration: animationDuration ;}
            PropertyAnimation { target: quitSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
            PropertyAnimation { target: storageSector; property: "opacity";from:1; to: 0.8; duration: animationDuration;}
            PropertyAnimation { target: storageSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
            PropertyAnimation { target: settingSector; property: "opacity";from:1; to: 0.8; duration: animationDuration;}
            PropertyAnimation { target: settingSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
        }
    ]

    function updateMenuState()
    {
        if (menuShowed)
        {
            outerImg.state = "hideAllMenu"
            menuShowed = false
        }
        else
        {
            outerImg.state = "showAllMenu"
            menuShowed = true
        }
    }

    //用于延时
    function destroyAll()
    {
        Qt.quit()
    }
}















