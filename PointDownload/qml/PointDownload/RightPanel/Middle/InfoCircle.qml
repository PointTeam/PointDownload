/***********************************************************************
*PointDownload
*Copyright (C) 2014~2015  PointTeam
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
/*******************************************************************
Date:   2014.3.20~
Description:
    使用率圆，以一个圆标示资源使用率，被MiddlePanel使用
Others:
Function list:

History:
**********************************************************************/

import QtQuick 2.0

Canvas {
  id:canvas1

  property string baseColor: "#d9e4eb"          //圆圈的底色
  property string percentageColor: "#47bac1"    //使用率的颜色
  property string mainTitle: ""
  property string subTitle: ""
  property real percentage: 0

  width: 100
  height: 100

  //anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}

  onPaint:{
     var ctx = canvas1.getContext('2d');
     //...
      ctx.strokeStyle = "#d9e4eb";
      ctx.lineWidth = 7;
      ctx.beginPath();
      ctx.arc(50,50, 45, 0, Math.PI * 2);
      ctx.stroke();
  }


  Canvas {
      id: cpuCanvas
      width: parent.width
      height: parent.height

      anchors.fill: parent

      onPaint:{
          //percentage = percentage + 1;

         var ctx = cpuCanvas.getContext('2d');
          ctx.clearRect(0,0,100,100);
          ctx.strokeStyle = percentageColor;
          ctx.lineWidth = 7;
          ctx.beginPath();
          // 根据percentage的值画出不同长度的圆弧
          //注意圆的方向是顺时针，所以90度角在下方
          ctx.arc(50,50, 45, Math.PI / 2, 2 * Math.PI * percentage / 100 + Math.PI / 2, false);
          ctx.stroke();
      }

//      MouseArea {
//          id: cpuMouse
//          anchors.fill: parent
//          onClicked: {
//              //单击时根据新的值重换圆
//              cpuCanvas.requestPaint();
//          }
//      }
  }

  Text {
      id: mainText
      anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
      text: mainTitle
      color: "#596679"
      font.family: "URW Bookman L Bold, Bold,Georgia,Times New Roman"
      font.pixelSize: 23
  }



  Text {
      id: subText
      anchors {top: mainText.bottom; horizontalCenter: parent.horizontalCenter}
      text: subTitle
      color: "#8a95a5"
      font.bold: true
      font.pixelSize: 10
  }

  function updatePercentage()
  {
      cpuCanvas.requestPaint();
  }
}


