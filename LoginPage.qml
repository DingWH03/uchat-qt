import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    Column {
        anchors.centerIn: parent
        spacing: 20

        GridLayout {
            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            Text {
                text: qsTr("用户名")
                horizontalAlignment: Text.AlignRight
                Layout.alignment: Qt.AlignRight
            }
            TextField {
                id: loginUserName
                Layout.preferredWidth: 200
                placeholderText: qsTr("请输入用户名")
            }

            Text {
                text: qsTr("密码")
                horizontalAlignment: Text.AlignRight
                Layout.alignment: Qt.AlignRight
            }
            TextField {
                id: loginPassword
                Layout.preferredWidth: 200
                placeholderText: qsTr("请输入密码")
            }
        }

        Row {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter  // 让按钮居中
            Button {
                text: qsTr("注册")
                onClicked: clientModel.sendRegister(loginUserName.text, loginPassword.text)
            }
            Button {
                text: qsTr("登陆")
                onClicked: clientModel.sendLogin(parseInt(loginUserName.text), loginPassword.text)
            }
        }
    }
}
