import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: notificationPopup
    property string message: ""
    property int duration: 2000 // 显示时间，默认2秒

    x: parent ? parent.width / 2 - width / 2 : 0
    y: parent ? parent.height / 3 - height / 2 : 0
    width: Math.max(message.length * 10 + 20, 200)
    height: 50
    modal: false
    focus: false

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.8
        radius: 10
        border.color: "gray"

        Text {
            anchors.centerIn: parent
            text: notificationPopup.message
            color: "white"
            font.pixelSize: 16
        }
    }

    Timer {
        id: autoCloseTimer
        interval: notificationPopup.duration
        running: false
        repeat: false
        onTriggered: notificationPopup.close()
    }

    function showMessage(newMessage, newDuration = 2000) {
        message = newMessage
        duration = newDuration
        open()
        autoCloseTimer.restart()
    }
}
