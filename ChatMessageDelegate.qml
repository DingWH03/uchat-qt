// ChatMessageDelegate.qml
import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2

Item {
    id: root
    width: parent ? parent.width : 300
    // Expose properties to be set by the ListView model
    property alias text: messageText.text
    property bool isMine: false
    property bool isGroup: false
    property string sender: ""

    // Use ColumnLayout for better layout management
    ColumnLayout {
        id: wrapper
        anchors {
            left: parent.left
            right: parent.right
            margins: 8
        }

        // Display sender's name if it's a group chat and the message isn't from the user
        Text {
            text: (isGroup && !isMine) ? sender : ""
            color: "#888888"
            font.pointSize: 12
            visible: isGroup && !isMine
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        // Message Bubble
        Rectangle {
            id: bubble
            radius: 6
            color: isMine ? "#87CEFA" : "#FFFFFF"  // Light blue for mine, white for others
            border.width: 1
            border.color: "#CCCCCC"
            Layout.alignment: isMine ? Qt.AlignRight : Qt.AlignLeft
            // Dynamic width based on text, capped at 70% of parent width
            width: Math.min(messageText.paintedWidth + 16, root.width * 0.7)
            // Dynamic height based on text
            height: messageText.paintedHeight + 16

            Item {
                anchors.fill: parent
                anchors.margins: 8 // Simulates padding

                Text {
                    id: messageText
                    text: root.text
                    color: isMine ? "white" : "black"
                    font.pointSize: 14
                    wrapMode: Text.Wrap
                    anchors.fill: parent
                }
            }
        }

    }
}
