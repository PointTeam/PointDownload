import QtQuick 2.0
import settingControler 1.0
import "../../SettingWin"

Rectangle{
    id:genericSettingPage
    color: "#3b5a6f"
    property int itemHeight:0

    SettingControler{
        id:settingContrl
    }

    InputItem{
        id:maxjobItem
        width: parent.width
        height: itemHeight
        title: qsTr("Max Job Count:")
        buttonValue: settingContrl.maxJobCount
        maxValue: 10
        minValue: 1
        anchors {top: parent.top; topMargin: 8}
        onValueChanged: {
            if (settingContrl.maxJobCount !== value)
                settingContrl.maxJobCount = value
        }
    }

    InputItem{
        id:threadItem
        width: parent.width
        height: itemHeight
        title: qsTr("Thread Count:")
        buttonValue: settingContrl.defaultThreadCount
        maxValue: 10
        minValue: 1
        anchors {top: maxjobItem.bottom; topMargin: 5}
        onValueChanged: {
            if (settingContrl.defaultThreadCount !== value)
                settingContrl.defaultThreadCount = value
        }
    }

    InputItem{
        id:maxDLSpeedItem
        width: parent.width
        height: itemHeight
        title: qsTr("MaxDL Speed:")
        buttonValue: settingContrl.maxDownloadSpeed
        maxValue: 99999
        minValue: 0
        anchors {top: threadItem.bottom; topMargin: 5}
        onValueChanged: {
            if (settingContrl.maxDownloadSpeed !== value)
                settingContrl.maxDownloadSpeed = value
        }
    }

    InputItem{
        id:maxULSpeedItem
        width: parent.width
        height: itemHeight
        title: qsTr("MaxUL Speed:")
        buttonValue: settingContrl.maxUploadSpeed
        maxValue: 99999
        minValue: 0
        anchors {top: maxDLSpeedItem.bottom; topMargin: 5}
        onValueChanged: {
            if (settingContrl.maxUploadSpeed !== value)
                settingContrl.maxUploadSpeed = value
        }
    }

    SwitchItem{
        id:enableULSwitch
        height: itemHeight
        width: parent.width
        title: qsTr("Enable Upload")
        itemState: settingContrl.enableUpload == "True"?true:false
        anchors {top: maxULSpeedItem.bottom; topMargin: 5}
        onSwitchValueChanged: {
            if (switchState)
                settingContrl.enableUpload = "True"
            else
                settingContrl.enableUpload = "False"
        }
    }

    SavePathItem{
        id:savePathItem
        width: parent.width
        height: itemHeight
        anchors {top: enableULSwitch.bottom; topMargin: 5}
    }

    PriorityToolItem{
        id:priorityToolItem
        width: parent.width
        height: itemHeight
        anchors {top: savePathItem.bottom;topMargin: 5 }
    }

}
