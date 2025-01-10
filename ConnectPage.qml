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
                text: qsTr("服务器")
                horizontalAlignment: Text.AlignRight
                Layout.alignment: Qt.AlignRight
            }
            TextField {
                Layout.preferredWidth: 200
                placeholderText: qsTr("请输入URL")
            }
        }

        Row {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter  // 让按钮居中
            Button {
                text: qsTr("连接")
            }
        }
    }
}