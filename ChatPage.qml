// ChatPage.qml
import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2
import QtQml 6.2

Page {
    id: page
    title: qsTr("聊天")

    // Overall layout with vertical arrangement
    ColumnLayout {
        anchors.fill: parent

        // ListView to display chat messages
        ListView {
            id: chatList
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 60
            model: chatModel

            // Reference the ChatMessageDelegate
            delegate: ChatMessageDelegate {
                sender: model.sender
                text: model.text
                isMine: model.isMine
                isGroup: model.isGroup
                width: parent.width  // Ensure delegate takes full width for proper alignment
            }

            // Automatically scroll to the bottom when new messages are added
            onCountChanged: {
                chatList.positionViewAtEnd();
            }
        }

        // Input area for sending new messages
        Rectangle {
            id: inputArea
            Layout.fillWidth: true
            height: 50
            color: "#F0F0F0"
            border.color: "#CCCCCC"
            border.width: 1

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
                        // Add new message to the model
                        chatModel.append({
                            sender: "Me",
                            text: messageInput.text,
                            isMine: true,
                            isGroup: false  // Set to true if it's a group chat
                        });
                        messageInput.text = "";
                    }
                }
            }
        }
    }

    // Define the chat model
    ListModel {
        id: chatModel
        // Initial sample messages
        ListElement {
            sender: "Alice"
            text: "你好，最近怎么样？"
            isMine: false
            isGroup: false
        }
        ListElement {
            sender: "Me"
            text: "我挺好的，谢谢！你呢？"
            isMine: true
            isGroup: false
        }
        ListElement {
            sender: "Tom"
            text: "大家好，我是Tom"
            isMine: false
            isGroup: true
        }
        ListElement {
            sender: "Me"
            text: "欢迎加入群聊！"
            isMine: true
            isGroup: true
        }
        ListElement {
            sender: "Alice"
            text: "周末有活动吗？"
            isMine: false
            isGroup: false
        }
        ListElement {
            sender: "Me"
            text: "打算周日出去爬山，你来吗？"
            isMine: true
            isGroup: false
        }
    }
}
