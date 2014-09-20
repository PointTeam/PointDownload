import QtQuick 2.0
import Singleton.XwareSettingControler 1.0

Rectangle{
    id:xwareSettingPage

    property bool xwareEnable: XwareSettingControler.xwareEnable
    property string vertifyCodeLink: ""

    Connections{
        target: XwareSettingControler

        onSSignInFlagChange:{
            if (flag)
            {
                loginPage.visible = false
                logoutPage.visible = true
                verifyCodeRec.height = 0
                logText.text = qsTr("Sign out")
            }
            else
            {
                loginPage.visible = true
                logoutPage.visible = false
                logText.text = qsTr("Sign in")
            }
        }

        onSXwareEnableChange: xwareSettingPage.xwareEnableChange(xwareEnable)

        onSVertifyCodeLinkChange:{
            loadingImg.source ="file:/" + codeLink
        }
    }

    signal xwareEnableChange(bool changeFlag)


    Image{
        id:backImg
        width: parent.width
        height: parent.height
        anchors.fill: parent
        source: "qrc:/images/dropzone/login-back"

        LoginPage{
            id:loginPage
            visible: XwareSettingControler.isSignIn?false:true
            width: parent.width * 4 / 5
            height:  parent.height * 2 /  5
            anchors {top: parent.top; topMargin: 10; horizontalCenter: parent.horizontalCenter}
        }

        LogoutPage{
            id:logoutPage
            visible: XwareSettingControler.isSignIn?true:false
            width: parent.width * 4 / 5
            height:  parent.height * 2 /  5
            anchors {top: parent.top; topMargin: 5; horizontalCenter: parent.horizontalCenter}
        }

        Rectangle {
            id:verifyCodeRec
            width: loginPage.width
            height: loadingImg.source == ""?0:20
            color: "#141414"
            radius: 4
            clip: true
            anchors {left: loginPage.left; top: loginPage.bottom}
            TextInput{
                id:vertifyCodeBox
                width: parent.width * 1/ 2
                height: parent.height
                font.pixelSize: 14
                selectByMouse: true
                color: "#ffffff"
                selectionColor: "#488bc5"
                verticalAlignment: TextInput.AlignVCenter
                horizontalAlignment: TextInput.AlignHCenter
                anchors {left: parent.left;}

            }
            Image {
                id: loadingImg
                opacity: 1
                width: parent.width / 3
                height: parent.height - 4
                anchors {right: parent.right;rightMargin: 2; verticalCenter: parent.verticalCenter}
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        XwareSettingControler.refreshVertifyCode()
                    }
                }
            }
        }

        Image{
            id:remeberInfoCheckImg
            source: XwareSettingControler.automaticLogin?"qrc:/images/navigation/Breduncheck":"qrc:/images/navigation/Brednone"
            width: 10
            height: parent.height / 18
            anchors {left: verifyCodeRec.left; top: verifyCodeRec.bottom; topMargin: 10}

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if (remeberInfoCheckImg.source == "qrc:/images/navigation/Breduncheck")
                    {
                        remeberInfoCheckImg.source = "qrc:/images/navigation/Brednone"
                        XwareSettingControler.automaticLogin = false
                    }
                    else
                    {
                        remeberInfoCheckImg.source = "qrc:/images/navigation/Breduncheck"
                        XwareSettingControler.automaticLogin = true
                    }
                }
            }
        }
        Text{
            text:qsTr("Automatic Login")
            color: "gray"
            font.pixelSize: 10
            verticalAlignment: Text.AlignVCenter
            height: remeberInfoCheckImg.height
            visible: height == 0?false:true
            anchors {left: remeberInfoCheckImg.right;leftMargin: 5; top: remeberInfoCheckImg.top}
        }
        Text{
            text:qsTr("Thunder License?")
            color: "gray"
            font.pixelSize: 10
            verticalAlignment: Text.AlignVCenter
            height: remeberInfoCheckImg.height
            visible: height == 0?false:true
            anchors {right: loginPage.right; top: remeberInfoCheckImg.top}

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: parent.color = "#ffffff"
                onExited: parent.color = "gray"
                onClicked: {
                    console.log("Show Thunder License...")
                }
            }
        }

        Rectangle{
            id:logButton
            color: "#319b8d"
            radius: height / 5
            width: parent.width * 4 / 5
            height: parent.height / 5
            anchors {top: remeberInfoCheckImg.bottom; topMargin: 20; horizontalCenter: parent.horizontalCenter}

            Text{
                id:logText
                color: "#ffffff"
                text:XwareSettingControler.isSignIn?qsTr("Sign out") : qsTr("Sign in")
                visible: parent.height == 0?false:true
                width: parent.width / 2
                height: parent.height
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors {horizontalCenter: parent.horizontalCenter}
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if (XwareSettingControler.isSignIn)
                        XwareSettingControler.signOutXware()
                    else
                    {
                        XwareSettingControler.userName = loginPage.getUsername();
                        XwareSettingControler.userPasswd = loginPage.getPassword();
                        XwareSettingControler.signInXware(loginPage.getUsername(),loginPage.getPassword(), vertifyCodeBox.text)
                        logText.text = qsTr("Signing...")
                    }
                }
            }
        }
    }

    function enableXware()
    {
        XwareSettingControler.enableXware()
    }

    function disableXware()
    {
        XwareSettingControler.disableXware()
    }

    function isXwareEnable()
    {
        return XwareSettingControler.xwareEnable
    }

    function getDefaultUserName()
    {
        return XwareSettingControler.userName
    }

    function getDefaultUserPasswd()
    {
        return XwareSettingControler.userPasswd
    }
}
