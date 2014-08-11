import QtQuick 2.0


Canvas {
    id: sectorCanvas

    property string percentageColor: "#1b9ad6"    //颜色
    property string iconPath: ""
    property real iconX: width / 2 - 12
    property real iconY: 10
    property real radius: parent.width * 3 / 8 - 3;
    property real startAngle:Math.PI / 2 + Math.PI - Math.PI / 6
    property real endAngle: Math.PI / 2 + Math.PI + Math.PI / 6


    width: parent.width
    height: parent.height


    onPaint:{
        var ctx = sectorCanvas.getContext('2d');
        ctx.clearRect(0,0,sectorCanvas.width,sectorCanvas.height);
        ctx.strokeStyle = percentageColor;
        ctx.lineWidth = 25;
        ctx.beginPath();
        //注意圆的方向是顺时针，所以90度角在下方
        ctx.arc(sectorCanvas.width / 2,sectorCanvas.width / 2, radius/*sectorCanvas.width * 3 / 8 - 3*/,
                startAngle + Math.PI / 180, endAngle - Math.PI / 180, false);
//        ctx.drawImage(iconPath,iconX,iconY)
        ctx.stroke();
    }

    Image{
        id:iconImg
        width: 24
        height: 24
        anchors {left:parent.left;leftMargin: iconX; top:parent.top;topMargin: iconY}
        source: iconPath
    }


    function updatePosition()
    {
        sectorCanvas.requestPaint();
    }
}
