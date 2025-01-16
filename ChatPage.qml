// ChatPage.qml
import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2
import QtQml 6.2

Page {
    id: chatPageContent
    title: qsTr("聊天")

    signal backRequested()

    ColumnLayout {
        anchors.fill: parent

        // 头部区域
        Rectangle {
            id: header
            Layout.fillWidth: true
            height: 60
            color: "#FFFFFF"
            border.color: "#CCCCCC"
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 10

                Button {
                    id: backButton
                    text: "< 返回"
                    width: 80
                    height: 40
                    onClicked: {
                        chatPageContent.backRequested()
                    }
                }

                Text {
                    id: usernameLabel
                    text: clientModel.currentChatName
                    font.pixelSize: 20
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                }
            }
        }

        // 聊天消息列表
        ListView {
            id: chatList
            Layout.fillWidth: true
            Layout.fillHeight: true

            // 建议把 spacing 调小，比如 10
            spacing: 60
            // clip: true  // 防止越界绘制

            model: clientModel.chatModel

            delegate: ChatMessageDelegate {
                text: model.message
                isMine: model.is_mine
                timestamp: model.timestamp
                width: parent.width
            }

            // 新消息时自动滚动到底部
            onCountChanged: {
                chatList.positionViewAtEnd()
            }
        }

        // 输入区域
        Rectangle {
            id: inputArea
            Layout.fillWidth: true
            height: 50
            color: "#F0F0F0"
            border.color: "#CCCCCC"
            border.width: 6

            RowLayout {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 8

                TextField {
                    id: messageInput
                    Layout.fillWidth: true
                    placeholderText: qsTr("输入消息...")
                    onAccepted: sendButton.clicked()
                }

                Button {
                    id: sendButton
                    text: qsTr("发送")
                    enabled: messageInput.text.trim() !== ""
                    onClicked: {
                        messageInput.text = "";
                    }
                }
            }
        }
    }
}
