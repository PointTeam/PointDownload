/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Match <2696627729@qq.com>
* Maintainer: Match <2696627729@qq.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

import QtQuick 2.0

Rectangle {
    id: shortcutButton

    property string iconSource: ""
    property string buttonText: ""

    width: parent.width
    color: "#08334b"

    Image {
        id: buttonIcon
        source: iconSource
        width: 12
        height: 12
        anchors {/*verticalCenter: parent.verticalCenter;*/ left: parent.left; leftMargin: 14}
    }

    Text {
        id: bText
        text: buttonText
        font.pixelSize: 12
        font.family: "URW Bookman L"
        color: "#ffffff"
        anchors {verticalCenter: buttonIcon.verticalCenter; left:buttonIcon.right; leftMargin: 4}
    }
}
