/*************************************************************
*File Name: ToolsComboBox.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年04月07日 星期二 20时27分35秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
//    color: "#f5f5f5"

    property var labels: ["Point","You-Get","Aria2","Xware"]

    ComboBox {
        id: mainBox
        anchors.fill: parent
        model: labels

        style: ComboBoxStyle {
            background: Rectangle {
                id: rectCategory
                width: mainBox.width
                height: mainBox.height
                color: "#f5f5f5"

                Image {
                    width: 12
                    height: 12
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:///images/arrow-down.png"
                }
            }
            textColor: "#b4b4b4"

            // drop-down customization here
            property Component __dropDownStyle: MenuStyle {
                __maxPopupHeight: 600
                __menuItemType: "comboboxitem"
                __scrollerStyle: ScrollViewStyle { }

                // background
                frame: Rectangle {
                    color: "#f5f5f5"
                    border.width: 1
                    border.color: "#b4b4b4"
                }

                // an item text
                itemDelegate.label: Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 10
                    color: styleData.selected ? "#ffffff" : "#b4b4b4"
                    text: styleData.text
                }

                // selection of an item
                itemDelegate.background: Rectangle {
                    color: styleData.selected ? "#6abae4" : "transparent"
                }

            }

//            property Component __popupStyle: MenuStyle {
//                property int __maxPopupHeight: 400
//                property int submenuOverlap: 0

//                property Component frame: Rectangle {
//                    width: (parent ? parent.contentWidth : 0)
//                    height: (parent ? parent.contentHeight : 0) + 2
//                    border.color: "black"
//                    property real maxHeight: 500
//                    property int margin: 1
//                }

//                property Component menuItemPanel: Text {
//                    text: "NOT IMPLEMENTED"
//                    color: "red"
//                    font {
//                        pixelSize: 14
//                        bold: true
//                    }
//                }

//                property Component __scrollerStyle: null
//            }
        }
    }
}
