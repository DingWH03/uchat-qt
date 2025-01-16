import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2

Item {
    id: root
    width: parent.width

    // 暴露给外部使用的属性
    property string text: ""   // 消息内容
    property bool isMine: false             // 标识是否是自己发送的消息
    property string timestamp: ""           // 消息的时间戳文本
    property bool showTime: false           // 标识当前显示的是时间还是消息内容

    // 布局容器
    ColumnLayout {
        id: wrapper
        anchors {
            left: parent.left
            right: parent.right
            margins: 8
        }

        // 聊天气泡
        Rectangle {
            id: bubble
            radius: 6
            // 自己的消息用浅蓝色，其它人的消息用白色
            color: root.isMine ? "#87CEFA" : "#FFFFFF"
            border.width: 1
            border.color: "#CCCCCC"
            Layout.alignment: root.isMine ? Qt.AlignRight : Qt.AlignLeft

            // 动态宽度：文本宽度 + padding，且不超过总宽度的 70%
            width: Math.min(messageText.paintedWidth + 16, root.width * 0.7)
            // 动态高度：文本高度 + padding
            height: messageText.paintedHeight + 16

            // 鼠标点击区域，用于切换显示内容（消息 / 时间）
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.showTime = !root.showTime
                }
            }

            Item {
                anchors.fill: parent
                anchors.margins: 8 // 内边距

                Text {
                    id: messageText
                    // 显示不同的内容：消息 or 时间
                    text: root.showTime ? root.timestamp : root.text
                    color: root.isMine ? "white" : "black"
                    font.pointSize: 14
                    wrapMode: Text.Wrap
                    anchors.fill: parent
                }
            }
        }
    }
}
