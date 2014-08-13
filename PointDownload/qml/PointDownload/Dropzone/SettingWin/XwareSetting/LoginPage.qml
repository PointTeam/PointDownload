import QtQuick 2.0

Rectangle {
    id:loginPage

    signal finishInputInfo()
    Image{
        id:userAndPasswdImg
        width: parent.width
        height: parent.height
        source: "qrc:/images/dropzone/user&passwd"
        anchors.fill: parent

        ValueInputBox{
            id:usernameBox
            defaultText: qsTr("Thunder User Name")
            width: parent.width * 3 / 4
            height: parent.height / 3
            anchors {right: parent.right; top:parent.top; topMargin: 10}
            onFinishInput: passwdBox.forceActiveFocus()
        }

        ValueInputBox{
            id:passwdBox
            defaultText: qsTr("Password")
            width: parent.width * 3 / 4
            height: parent.height / 3
            anchors {right: parent.right; bottom: parent.bottom; bottomMargin: 5}
            onFinishInput: loginPage.finishInputInfo()
        }
    }

    function getUsername()
    {
        return usernameBox.getInputText()
    }

    function getPassword()
    {
        return passwdBox.getInputText()
    }
}
