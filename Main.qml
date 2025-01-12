import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ClientModel

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("uchat")

    ClientModel {
        id: clientModel

        onConnected: {
            notifier.showMessage("服务器连接成功", 3000)
            stackView.push(loginPage)
        }

        onConnectionError: {
            notifier.showMessage("与服务器的连接断开", 3000)
            stackView.push(connectPage)
        }

        onLoginOk: function(message){
            notifier.showMessage(message, 3000)
            stackView.push(contactPage)
        }

        onLoginError: function(message){
            notifier.showMessage(message, 3000)
        }
    }

    NotificationPopup {
            id: notifier
        }

    StackView {
            id: stackView
            anchors.fill: parent
            initialItem: connectPage
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

    ListModel {
        id: friendList
                        ListElement { name: "Alice" }
                        ListElement { name: "Bob" }
                        ListElement { name: "Charlie" }
                        ListElement { name: "Diane" }
                        ListElement { name: "Eric" }
                    }

    ListModel {
        id: groupList
                        ListElement { title: "Group Chat A" }
                        ListElement { title: "Group Chat B" }
                        ListElement { title: "Group Chat C" }
                    }

}

