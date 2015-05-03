/*************************************************************
*File Name: AnalyzeButton.qml
*Author: Match
*Email: Match.YangWanQing@gmail.com
*Created Time: 2015年04月07日 星期二 20时33分24秒
*Description:
*
*************************************************************/
import QtQuick 2.1
import QtGraphicalEffects 1.0

Rectangle {
    id: analyzeButton
    width: parent.width
    height: parent.height

    state: "normal"
    color: "#7ee1aa"

    signal doAnalyze
    signal entered
    signal exited

    function changeToNormalState(){
        analyzeButton.state = "normal"
    }

    function changeToAnalyzingState(){
        analyzeButton.state = "analyzing"
    }

    function changeToDisableState(){
        analyzeButton.state = "disable"
    }

    Text {
        id: titleText
        text: qsTr("Analyze")
        color: analyzeButton.state == "disable" ? "#b4b4b4" :  "#ffffff"
        font.pixelSize: 19
        anchors.centerIn: parent
        height: contentHeight
        width: contentWidth
        verticalAlignment: Text.AlignVCenter
    }

    Glow {
        id: textGlow
        enabled: false
        anchors.fill: titleText
        radius: 1
        samples: 16
        color: "white"
        source: titleText
        opacity: 0
    }

    AnimatedImage {
        id: loadingImg
        source: "qrc:/images/loading.gif"
        playing: true
        opacity: 1
        width: parent.height / 2
        height: parent.height / 2
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            analyzeButton.state = "analyzing"
            analyzeButton.doAnalyze()
            textGlow.opacity = 0
        }
        onEntered: {
            analyzeButton.entered()
            if (analyzeButton.state == "normal")
                textGlow.opacity = 1
        }
        onExited: {
            analyzeButton.exited()
            textGlow.opacity = 0
        }
    }


    states:[
        State {
            name: "analyzing"
            PropertyChanges {target: titleText; opacity: 0}
            PropertyChanges {target: loadingImg; playing: true; opacity: 1}
        },
        State {
            name: "normal"
            PropertyChanges {target: titleText; opacity: 1}
            PropertyChanges {target: loadingImg; playing: false; opacity: 0}
        },
        State {
            name: "disable"
            PropertyChanges {target: titleText; opacity: 0}
            PropertyChanges {target: loadingImg; playing: false; opacity: 0}
        }
    ]
}

