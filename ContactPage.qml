import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml
Page {
    id: contactPage
    title: qsTr("联系人")

    ScrollView {
        anchors.fill: parent
        contentWidth: parent.width

        Column {
            id: contentColumn
            width: parent.width
            spacing: 16
            padding: 16

            // ------------------ 群聊部分 ------------------
            Text {
                text: qsTr("群聊")
                font.pointSize: 20
                font.bold: true
            }

            ListView {
                id: groupChatList
                clip: true
                width: parent.width
                // 让 ListView 高度根据内容自适应，从而能在外层 ScrollView 中看到所有项
                // contentHeight 表示所有列表项所需的总高度
                height: contentHeight
                interactive: false

                // 模拟数据，可替换为实际的 model
                model: ListModel {
                    ListElement { title: "Group Chat A" }
                    ListElement { title: "Group Chat B" }
                    ListElement { title: "Group Chat C" }
                }

                delegate: Rectangle {
                    // 声明一个属性接收系统注入的 index，避免 “Unqualified access” 警告
                    property int rowIndex: index
                    // 同理，使用 model.title，而不是直接用 title
                    property string chatTitle: model.title

                    width: parent.width
                    height: 50
                    color: rowIndex % 2 === 0 ? "#EFEFEF" : "#FFFFFF"

                    Text {
                        text: chatTitle
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 12
                        font.pointSize: 16
                    }
                }
            }

            // ------------------ 联系人部分 ------------------
            Text {
                text: qsTr("联系人")
                font.pointSize: 20
                font.bold: true
            }

            ListView {
                id: contactList
                clip: true
                width: parent.width
                // 同样让联系人列表自适应高度
                height: contentHeight
                interactive: false

                // 模拟数据，可替换为实际的 model
                model: ListModel {
                    ListElement { name: "Alice" }
                    ListElement { name: "Bob" }
                    ListElement { name: "Charlie" }
                    ListElement { name: "Diane" }
                    ListElement { name: "Eric" }
                }

                delegate: Rectangle {
                    // 声明属性接收 index
                    property int rowIndex: index
                    property string contactName: model.name

                    width: parent.width
                    height: 50
                    color: rowIndex % 2 === 0 ? "#EFEFEF" : "#FFFFFF"

                    Text {
                        text: contactName
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 12
                        font.pointSize: 16
                    }
                }
            }
        }
    }
}
