import QtQuick 2.0
import xwareSettingControler 1.0

Rectangle{
    id:xwareSettingPage

    XwareSettingControler{
        id:xwareCotrl
        onSIsSignInChange: {
            if (isSignIn)
            {
                loginPage.visible = false
                logoutPage.visible = true
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
    }

    signal xwareEnableChange(bool changeFlag)

    property bool xwareEnable: xwareCotrl.xwareEnable

    Image{
        id:backImg
        width: parent.width
        height: parent.height
        anchors.fill: parent
        source: "qrc:/images/dropzone/login-back"

        LoginPage{
            id:loginPage
            visible: xwareCotrl.isSignIn?false:true
            width: parent.width * 4 / 5
            height:  parent.height * 2 /  5
            anchors {top: parent.top; topMargin: 10; horizontalCenter: parent.horizontalCenter}
        }

        LogoutPage{
            id:logoutPage
            visible: xwareCotrl.isSignIn?true:false
            width: parent.width * 4 / 5
            height:  parent.height * 2 /  5
            anchors {top: parent.top; topMargin: 5; horizontalCenter: parent.horizontalCenter}
        }

        Image{
            id:remeberInfoCheckImg
            source: xwareCotrl.automaticLogin?"qrc:/images/navigation/Breduncheck":"qrc:/images/navigation/Brednone"
            width: 10
            height: parent.height / 18
            anchors {left: loginPage.left; top: loginPage.bottom; topMargin: 20}

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if (remeberInfoCheckImg.source == "qrc:/images/navigation/Breduncheck")
                    {
                        remeberInfoCheckImg.source = "qrc:/images/navigation/Brednone"
                        xwareCotrl.automaticLogin = false
                    }
                    else
                    {
                        remeberInfoCheckImg.source = "qrc:/images/navigation/Breduncheck"
                        xwareCotrl.automaticLogin = true
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
                text:xwareCotrl.isSignIn?qsTr("Sign out") : qsTr("Sign in")
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
                    if (xwareCotrl.isSignIn)
                        xwareCotrl.signOutXware()
                    else
                    {
                        xwareCotrl.userName = loginPage.getUsername();
                        xwareCotrl.userPasswd = loginPage.getPassword();
                        xwareCotrl.signInXware(loginPage.getUsername(),loginPage.getPassword())
                    }
                }
            }
        }
    }

    function enableXware()
    {
        xwareCotrl.enableXware()
    }

    function disableXware()
    {
        xwareCotrl.disableXware()
    }

    function isXwareEnable()
    {
        return xwareCotrl.xwareEnable
    }

    function getDefaultUserName()
    {
        return xwareCotrl.userName
    }

    function getDefaultUserPasswd()
    {
        return xwareCotrl.userPasswd
    }
}
