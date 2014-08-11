import QtQuick 2.0
import Singleton.DataControler 1.0

Rectangle{
    id: toolsRec
    color: "#f1f1f1"

    signal updateToolType(string newTType)
    //连接单例的信号
    Connections {
        target: DataControler
        onSToolsTypeChange:{
            //每次更新前都清空所有状态
            updateToolType("")
            pointCheckImg.source = "qrc:///images/uncheck"
            aria2CheckImg.source = "qrc:///images/uncheck"
            xwareCheckImg.source = "qrc:///images/uncheck"
            updateCheckState()
        }
    }

    Text{
        id:titleText
        width: parent.width
        height: 15
        text: qsTr("Download Tools:")
        font.pixelSize: 12
        color: "#008dac"
        anchors {left: parent.left}
    }

    Image{
        id:pointCheckImg
        width: 12
        height: 12
        source: DataControler.defaultTool==="Point"?"qrc:///images/checked":"qrc:///images/uncheck"
        anchors {left: parent.left;leftMargin: 2; top: titleText.bottom; topMargin: 5}

        MouseArea{
            anchors.fill: parent
            onClicked: {
                //只能通过选择其他的項使该项取消选中，确保一定有一项会被选中
                if (pointCheckImg.source == "qrc:///images/uncheck")
                {
                    pointCheckImg.source = "qrc:///images/checked"
                    //一个被选中，其他的都要标记为未选中
                    aria2CheckImg.source = "qrc:///images/uncheck"
                    xwareCheckImg.source = "qrc:///images/uncheck"

                    updateToolType("Point")
                }
            }
        }
    }
    Text{
        id:pointText
        text:qsTr("Point:")
        font.pixelSize: 12
        color: "#008dac"
        anchors {left: pointCheckImg.right;leftMargin: 2; verticalCenter: pointCheckImg.verticalCenter}
    }

    Image{
        id:aria2CheckImg
        width: 12
        height: 12
        source: DataControler.defaultTool==="Aria2"?"qrc:///images/checked":"qrc:///images/uncheck"
        enabled: DataControler.isAria2Enable?true:false
        anchors {left: pointText.right;leftMargin: 20; top: titleText.bottom; topMargin: 5}

        MouseArea{
            anchors.fill: parent
            onClicked: {
                //只能通过选择其他的項使该项取消选中，确保一定有一项会被选中
                if (aria2CheckImg.source == "qrc:///images/uncheck")
                {
                    aria2CheckImg.source = "qrc:///images/checked"
                    //一个被选中，其他的都要标记为未选中
                    pointCheckImg.source = "qrc:///images/uncheck"
                    xwareCheckImg.source = "qrc:///images/uncheck"

                    updateToolType("Aria2")
                }
            }
        }
    }
    Text{
        id:aria2Text
        text:qsTr("Aria2:")
        font.pixelSize: 12
        color: DataControler.isAria2Enable?"#008dac":"#c6c4c4"
        anchors {left: aria2CheckImg.right;leftMargin: 2; verticalCenter: aria2CheckImg.verticalCenter}
    }

    Image{
        id:xwareCheckImg
        width: 12
        height: 12
        source: DataControler.defaultTool==="Xware"?"qrc:///images/checked":"qrc:///images/uncheck"
        enabled: DataControler.isXwareEnable?true:false
        anchors {left: aria2Text.right;leftMargin: 20; top: titleText.bottom; topMargin: 5}

        MouseArea{
            anchors.fill: parent
            onClicked: {
                //只能通过选择其他的項使该项取消选中，确保一定有一项会被选中
                if (xwareCheckImg.source == "qrc:///images/uncheck")
                {
                    xwareCheckImg.source = "qrc:///images/checked"
                    //一个被选中，其他的都要标记为未选中
                    pointCheckImg.source = "qrc:///images/uncheck"
                    aria2CheckImg.source = "qrc:///images/uncheck"

                    updateToolType("Xware")
                }
            }
        }
    }
    Text{
        text:qsTr("Xware(Thunder):")
        font.pixelSize: 12
        color: DataControler.isXwareEnable?"#008dac":"#c6c4c4"
        anchors {left: xwareCheckImg.right;leftMargin: 2; verticalCenter: xwareCheckImg.verticalCenter}
    }

    function updateCheckState()
    {
        //因为只有you-get才能下载网页探测的视频，所以其他的都不可选
        if (DataControler.toolsType === "YouGet")
        {
            pointCheckImg.source = "qrc:///images/uncheck";
            pointCheckImg.enabled = false;
            aria2CheckImg.source = "qrc:///images/uncheck";
            aria2CheckImg.enabled = false;
            xwareCheckImg.source = "qrc:///images/uncheck";
            xwareCheckImg.enabled = false;

            updateToolType("YouGet")
        }
        else if (DataControler.toolsType === "Aria2")
        {
            //因为某些链接只有aria2和xware才能分析下载，比如bt
            pointCheckImg.source = "qrc:///images/uncheck";
            pointCheckImg.enabled = false;
            if (DataControler.isAria2Enable)
            {
                aria2CheckImg.source = "qrc:///images/checked";
                aria2CheckImg.enabled = true;

                updateToolType("Aria2")
            }

            if (DataControler.isXwareEnable)
            {
                xwareCheckImg.source = "qrc:///images/uncheck";
                xwareCheckImg.enabled = true;

                updateToolType("Xware")
            }
        }
        else if(DataControler.toolsType === "Xware" && DataControler.isXwareEnable)
        {
            pointCheckImg.source = "qrc:///images/uncheck";
            pointCheckImg.enabled = false;
            aria2CheckImg.source = "qrc:///images/uncheck";
            aria2CheckImg.enabled = false;
            xwareCheckImg.source = "qrc:///images/checked";
            xwareCheckImg.enabled = true;

            updateToolType("Xware")
        }
        else//Point
        {
            pointCheckImg.enabled = true;
            if (DataControler.isAria2Enable)
            {
                aria2CheckImg.source = "qrc:///images/checked";
                aria2CheckImg.enabled = true;

                updateToolType("Aria2")
            }
            else if (DataControler.isXwareEnable)
            {
                xwareCheckImg.source = "qrc:///images/checked";
                xwareCheckImg.enabled = true;

                updateToolType("Xware")
            }
            else
            {
                pointCheckImg.source = "qrc:///images/checked";
                updateToolType("Point")
            }
        }
    }
}
