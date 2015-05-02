/*************************************************************
*File Name: ArrowTipButton.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年05月02日 星期六 13时20分56秒
*Description:
*
*************************************************************/
import QtQuick 2.1

Canvas {
    id: tipButton

    property color backColor: "#e82500"
    property color titleColor: "#c4c3c3"
    property color titleHoverColor: "#ffffff"
    property alias fontSize: tipText.font.pixelSize
    property alias buttonTitle: tipText.text
    property int arrowWidth: 10
    property int arrowHeight: 6

    property point arrowPoint: Qt.point(tipButton.width / 2, 0)
    property point leftTopPoint: Qt.point(0, arrowHeight)
    property point leftBottomPoint: Qt.point(0, tipButton.height)
    property point rightTopPoint: Qt.point(tipButton.width, arrowHeight)
    property point rightBottomPoint: Qt.point(tipButton.width, tipButton.height)

    width: parent.width
    height: parent.height

    signal clicked

    onPaint:{
       var ctx = tipButton.getContext('2d');
        ctx.clearRect(0,0,tipButton.width,tipButton.height);
        ctx.fillStyle = backColor;
        ctx.lineWidth = 10;
        ctx.beginPath();
        ctx.moveTo(arrowPoint.x, arrowPoint.y);//start point
        ctx.lineTo(arrowPoint.x + arrowWidth / 2, arrowHeight)
        ctx.lineTo(rightTopPoint.x, rightTopPoint.y)
        ctx.lineTo(rightBottomPoint.x, rightBottomPoint.y)
        ctx.lineTo(leftBottomPoint.x, leftBottomPoint.y)
        ctx.lineTo(leftTopPoint.x, leftTopPoint.y)
        ctx.lineTo(arrowPoint.x - arrowWidth / 2, arrowHeight)
        ctx.lineTo(arrowPoint.x, arrowPoint.y)
        ctx.closePath()
        ctx.fill()
    }

    Text {
        id: tipText
        height: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: tipButton.height / 2 - arrowHeight
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: titleColor
        text: "Button"
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: tipText.color = titleHoverColor
        onExited: tipText.color = titleColor
        onClicked: {
            tipButton.clicked()
        }
    }
}
