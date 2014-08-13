import QtQuick 2.0
import xwareSettingControler 1.0

Rectangle{
    id:xwareSettingPage

    XwareSettingControler{
        id:xwareCotrl
        onSSignInFinish: {
            logText.text = qsTr("Sign out")
        }
        onSSignOutFinish: {
            logText.text = qsTr("Sign in")
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
            width: parent.width * 4 / 5
            height:  parent.height * 2 /  5
            anchors {top: parent.top; topMargin: 10; horizontalCenter: parent.horizontalCenter}
        }

//        Rectangle{
//            id:licenseRec
//            width: parent.width * 3 / 4
//            height: parent.height / 6
//            anchors {top: loginPage.bottom; horizontalCenter: parent.horizontalCenter}
//        }

        Rectangle{
            id:logButton
            color: "#319b8d"
            radius: height / 5
            width: parent.width * 4 / 5
            height: parent.height / 5
            anchors {bottom: parent.bottom; bottomMargin: 20; horizontalCenter: parent.horizontalCenter}

            Text{
                id:logText
                color: "#ffffff"
                text:qsTr(xwareCotrl.isSignIn?"Sign out" : "Sign in")
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
                        xwareCotrl.signInXware(loginPage.getUsername(),loginPage.getPassword())
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

}
