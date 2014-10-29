import QtQuick 2.0
import settingControler 1.0
import Singleton.DropzoneSettingControler 1.0
import "../../SettingWin"
import "../../SettingWin/GenericSetting"

Rectangle{
    id:dropzoneSettingPage
    color: "#3b5a6f"
    property int itemHeight:0

    SettingControler{
        id:settingContrl
    }

    InputItem{
        id:opacityItem
        width: parent.width
        height: itemHeight
        title: qsTr("Opacity:")
        buttonValue: DropzoneSettingControler.opacity
        maxValue: 10
        minValue: 5
        anchors {top: parent.top; topMargin: 8}
        onValueChanged: {
            if (DropzoneSettingControler.opacity !== value )
                DropzoneSettingControler.opacity = value
        }
    }

    InputItem{
        id:infoIntervalItem
        width: parent.width
        height: itemHeight
        title: qsTr("Infomation Interval(MS):")
        buttonValue: DropzoneSettingControler.infoInterval
        maxValue: 10000
        minValue: 500
        anchors {top: opacityItem.bottom; topMargin: 5}
        onValueChanged: {
            if (DropzoneSettingControler.infoInterval !== value && value >= 500)
                DropzoneSettingControler.infoInterval = value
        }
    }

    SwitchItem{
        id:showJobCountSwitch
        height: itemHeight
        width: parent.width
        title: qsTr("Show Job Count")
        itemState: DropzoneSettingControler.showJobCount
        anchors {top: infoIntervalItem.bottom; topMargin: 5}
        onSwitchValueChanged: {
            DropzoneSettingControler.showJobCount = switchState
        }
    }

    SwitchItem{
        id:showCPUUsageSwitch
        height: itemHeight
        width: parent.width
        title: qsTr("Show Storage Usage")
        itemState: DropzoneSettingControler.showStorageUsage
        anchors {top: showJobCountSwitch.bottom; topMargin: 5}
        onSwitchValueChanged: {
                DropzoneSettingControler.showStorageUsage = switchState
        }
    }

}
