import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("uchat")

    StackView {
            id: stackView
            anchors.fill: parent
            initialItem: chatPage
        }

    Component {
            id: loginPage
            LoginPage { }  // 引用 loginPage.qml
        }
    Component {
            id: chatPage
            ChatPage { }  // 引用 ChatPage.qml
        }
    Component {
            id: contactPage
            ContactPage { }  // 引用 ContactPage.qml
        }
    Component {
            id: connectPage
            ConnectPage { }  // 引用 ConnectPage.qml
        }
}

