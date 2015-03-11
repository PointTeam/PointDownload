/*************************************************************
*File Name: main.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年03月10日 星期二 21时19分35秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import QtQuick.Window 2.1
import "./TopPanel"

Window {
	id:mainWindow
	width: 800
	height: 500
	x: 300
	y: 100
	color: "#00000000"
	flags: Qt.FramelessWindowHint

	property var backbroundImagePath: "./backimg.jpg"
	property alias backgroundImageOpacity: backgroundImage.opacity
	property var backbroundRecColor: "#116666"
	property alias backbroundRecOpacity: backgroundRec.opacity

        MouseArea {
		        anchors.fill: parent
		        property int startX
				property int startY
		        property bool holdFlag
		        onPressed: {
				startX = mouse.x;
				startY = mouse.y;
				holdFlag = true;
		     }
		     onReleased: holdFlag = false;
			 onPositionChanged: {
		     if (holdFlag) {
	            mainWindow.setX(mainWindow.x + mouse.x - startX)
				mainWindow.setY(mainWindow.y + mouse.y - startY)
			}
		}
	}

	TopBar {
		width: parent.width
		height: 40
		z: 1
	}

	Item {
		anchors.fill: parent
		width: parent.width
		height: parent.height

		Image {
			id: backgroundImage
			anchors.fill: parent
			opacity: 0.9
			source: backbroundImagePath
		}
	}

	Rectangle {
		id: backgroundRec
		anchors.centerIn: parent
		width: parent.width
		height: parent.height
		color: backbroundRecColor
		opacity: 0
		radius: 6
	}
}
