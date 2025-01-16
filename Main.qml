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
        // onCurrentChatNameChanged: function(title){
        //     // chatPageContent.chatTitle = title
        //     console.log(title)
        // }
    }

    Connections {
            target: clientModel.friendList

            function onFriendSelected(friend) {
                console.log("Selected friend: " + friend)
                clientModel.setCurrentChat(friend.id, friend.name)
                stackView.push(chatPage)
            }
        }

    Connections {
            target: clientModel.groupList

            function onGroupSelected(group) {
                console.log("Selected friend: " + group)

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

            ChatPage {
                onBackRequested: {
                    stackView.pop()
                }
            }  // 引用 ChatPage.qml
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

