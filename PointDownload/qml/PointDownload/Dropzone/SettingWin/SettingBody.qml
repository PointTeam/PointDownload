import QtQuick 2.0
import youGetSettingControler 1.0
import "GenericSetting"
import "DropzoneSetting"
import "Help"

Rectangle {
    id:settingBodyRec
    width: 100
    height: 62

    ListView {
        id: settingItemView
        anchors.fill: parent
        model: itemModel
        clip: true
    }

    VisualItemModel
    {
        id: itemModel

        Rectangle{
            id:extensionRec

            width: settingBodyRec.width
            height: 40

            SettingMainItem{
                id:extensionItem
                width: parent.width
                height: 40
                itemTitle: "Browser plugin"
                anchors {top: extensionRec.top}
            }
        }

        //youget----------------------------------------------------------------------
        Rectangle{
            id:yougetRec

            width: settingBodyRec.width
            height: 40

            YouGetSettingControler{
                id:ygControler
                onInstallingStep: {
                    ygSettingPage.stepNum = step
                    ygSettingPage.stepInfo = descririytion
                }
                onGotError: {
                    ygSettingPage.middleInfo = errString
                    ygSettingPage.stepInfo = qsTr("Error! Please Retry")
                    yougetItem.enableButtonIcon = "qrc:/images/dropzone/disable"
                }
            }

            SettingMainItem{
                id:yougetItem
                width: parent.width
                height: 40
                itemTitle: "You-Get"
                enableButtonIcon: ygControler.isYouGetEnable?"qrc:/images/dropzone/enable":"qrc:/images/dropzone/disable"
                anchors {top: yougetRec.top}

                //折叠事件
                MouseArea{
                    anchors.fill: parent
                    anchors.rightMargin: 40
                    onClicked: {
                        if (yougetRec.height == 140)
                            yougetRec.height = 40
                        else
                            yougetRec.height = 140
                    }
                }
                MouseArea{
                    anchors.right: parent.right
                    width: 40
                    height: parent.height
                    onClicked: {
                        if (yougetItem.enableButtonIcon == "qrc:/images/dropzone/disable")
                        {
                            yougetItem.enableButtonIcon = "qrc:/images/dropzone/enable"
                            ygControler.enableYouGet()
                            yougetRec.height = 140
                        }
                        else
                        {
                            yougetItem.enableButtonIcon = "qrc:/images/dropzone/disable"
                            ygControler.disableYouGet()
                            yougetRec.height = 40
                        }
                    }
                }
            }

            YouGetSettingPage{
                id:ygSettingPage
                width: parent.width
                height: 100
                anchors.top:yougetItem.bottom
            }

            Behavior on height {
                NumberAnimation{duration: 300;easing.type: Easing.OutCubic}
            }
        }

        SettingMainItem{
            id:xwareItem
            width: settingBodyRec.width
            height: 40
            itemTitle: "Xware(Thunder)"
            enableButtonIcon: "qrc:/images/dropzone/disable"
            anchors {top: yougetRec.bottom}
        }

        SettingMainItem{
            id:aria2Item
            width: settingBodyRec.width
            height: 40
            itemTitle: "Aria2"
            enableButtonIcon: "qrc:/images/dropzone/disable"
            anchors {top: xwareItem.bottom}
        }

        Rectangle{
            id:dropzoneRec

            width: settingBodyRec.width
            height: 40

            SettingMainItem{
                id:dropzonItem
                width: settingBodyRec.width
                height: 40
                itemTitle: qsTr("Dropzone")
                anchors {top: dropzoneRec.top}

                //折叠事件
                MouseArea{
                    anchors.fill: parent
                    anchors.rightMargin: 40
                    onClicked: {
                        if (dropzoneRec.height == 190)
                        {
                            dropzoneRec.height = 40
                            dzSettingPage.itemHeight = 0
                            dzSettingPage.height = 0
                        }
                        else
                        {
                            dropzoneRec.height = 190
                            dzSettingPage.itemHeight = 30
                            dzSettingPage.height = 150
                        }
                    }
                }
            }

            DropzoneSettingPage{
                id:dzSettingPage
                width: parent.width
                anchors.top:dropzonItem.bottom
            }

            Behavior on height {
                NumberAnimation{duration: 300;easing.type: Easing.OutCubic}
            }
        }

        //generic-------------------------------------------------
        Rectangle {
            id:genericRec

            width: settingBodyRec.width
            height: 40


            SettingMainItem{
                id:genericsettingsItem
                width: settingBodyRec.width
                height: 40
                itemTitle: qsTr("Generic settings")
                anchors {top: genericRec.top}

                //折叠事件
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if (genericRec.height == 300)
                        {
                            genericRec.height = 40
                            geSettingPage.itemHeight = 0
                            geSettingPage.height = 0
                        }
                        else
                        {
                            genericRec.height = 300
                            geSettingPage.itemHeight = 30
                            geSettingPage.height = 260
                        }
                    }
                }
            }

            GenericSettingPage{
                id:geSettingPage
                width: parent.width
                anchors.top:genericsettingsItem.bottom
            }

            Behavior on height {
                NumberAnimation{duration: 300;easing.type: Easing.OutCubic}
            }

        }

        Rectangle {
            id:helpRec

            width: settingBodyRec.width
            height: 40

            SettingMainItem{
                id:helpItem
                width: settingBodyRec.width
                height: 40
                itemTitle: qsTr("Help")
                anchors.top:helpRec.top

                //折叠事件
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if (helpRec.height == 120)
                        {
                            helpRec.height = 40
                            helpPage.height = 0
                        }
                        else
                        {
                            helpRec.height = 120
                            helpPage.height = 80
                        }
                    }
                }
            }

            HelpPage{
                id:helpPage
                width: parent.width
                anchors.top:helpItem.bottom
            }

            Behavior on height {
                NumberAnimation{duration: 300;easing.type: Easing.OutCubic}
            }
        }
    }


    states: [
        State {
            name: "YouGetPageShow"
            PropertyChanges { target: showMainSector; opacity: 1 }
        },
        State {
            name: "YouGetPageHide"
            PropertyChanges { target: showMainSector; opacity: 0 }
        }

    ]

    transitions: [
        Transition {
            from: "hideAllMenu"
            to: "showAllMenu"
            PropertyAnimation { target: showMainSector; property: "rotation"; duration: animationDuration;easing.type: Easing.InOutBack}
        }
    ]

}
