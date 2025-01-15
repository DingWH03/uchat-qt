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
                id: groupListView
                clip: true
                width: parent.width
                height: contentHeight
                interactive: false

                model: clientModel.groupList

                delegate: Rectangle {
                    property int rowIndex: index
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

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            // 调用模型的点击处理函数
                            clientModel.groupList.onGroupClicked(rowIndex);
                        }
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
                id: frientListView
                clip: true
                width: parent.width
                height: contentHeight
                interactive: false

                model: clientModel.friendList

                delegate: Rectangle {
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

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            // 调用模型的点击处理函数
                            clientModel.friendList.onFriendClicked(rowIndex);
                        }
                    }
                }
            }
        }
    }
}
