// ClientModel.cpp
#include "clientmodel.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QHash>
#include <functional>
ClientModel::ClientModel(QObject *parent) : QObject(parent) {
    // 连接 CoreApi 的信号到 ClientModel 的槽
    connect(&api, &CoreApi::connected, this, &ClientModel::handleConnected);
    connect(&api, &CoreApi::connectionError, this, &ClientModel::handleConnectionError);
    connect(&api, &CoreApi::serverResponseReceived, this, &ClientModel::handleServerResponse);
}

void ClientModel::connectToServer(const QString &address, int port) {
    api.connectToServer(address, port);
}

void ClientModel::sendLogin(int userId, const QString &password) {
    api.sendLogin(userId, password);
}

void ClientModel::sendRegister(const QString &userName, const QString &password) {
    api.sendRegister(userName, password);
}

void ClientModel::handleConnected() {
    emit connected();
}

void ClientModel::handleConnectionError() {
    emit connectionError();
}

void ClientModel::handleServerResponse(const QJsonObject& response) {
    // 将 QJsonObject 转换为格式化 JSON 字符串并输出
    QJsonDocument doc(response);
    QString jsonString = doc.toJson(QJsonDocument::Indented);
    qDebug() << "Received response:" << jsonString;

    QString action = response.value("action").toString();

    // 定义一个查找表
    static const QHash<QString, std::function<void()>> handlers = {
        {"generic_response", [&]() {
             QString status = response.value("status").toString();
             QString message = response.value("message").toString();
             emit genericResponseReceived(status, message);
         }},
        {"receive_message", [&]() {
             quint32 sender = response.value("sender").toInt();
             QString message = response.value("message").toString();
             QString timestamp = response.value("timestamp").toString();
             emit messageReceived(sender, message, timestamp);
         }},
        {"error", [&]() {
             QString message = response.value("message").toString();
             emit errorReceived(message);
         }},
        {"online_users", [&]() {
             QString flag = response.value("flag").toString();
             QJsonArray userIdsArray = response.value("user_ids").toArray();
             QList<quint32> userIds;
             for (const QJsonValue& value : userIdsArray) {
                 userIds.append(value.toInt());
             }
             emit onlineUsersReceived(flag, userIds);
         }},
        {"username", [&]() {
             quint32 userId = response.value("user_id").toInt();
             QString username = response.value("username").toString();
             emit userNameReceived(userId, username);
         }},
        {"group_members", [&]() {
             quint32 groupId = response.value("group_id").toInt();
             QJsonArray memberIdsArray = response.value("member_ids").toArray();
             QList<quint32> memberIds;
             for (const QJsonValue& value : memberIdsArray) {
                 memberIds.append(value.toInt());
             }
             emit groupMembersReceived(groupId, memberIds);
         }},
        {"friend_list", [&]() {
             QJsonArray friendIdsArray = response.value("friend_ids").toArray();
             QList<quint32> friendIds;
             for (const QJsonValue& value : friendIdsArray) {
                 friendIds.append(value.toInt());
             }
             emit friendListReceived(friendIds);
         }},
        {"group_list", [&]() {
             QJsonArray groupIdsArray = response.value("group_ids").toArray();
             QList<quint32> groupIds;
             for (const QJsonValue& value : groupIdsArray) {
                 groupIds.append(value.toInt());
             }
             emit groupListReceived(groupIds);
         }},
        {"register_response", [&]() {
             QString message = response.value("message").toString();
             if (response.value("status").toBool()) {
                 emit registerOk(message);
             } else {
                 emit registerError(message);
             }
         }},
        {"login_response", [&]() {
             QString message = response.value("message").toString();
             if (response.value("status").toBool()) {
                 emit loginOk(message);
             } else {
                 emit loginError(message);
             }
         }}
    };

    // 查找并执行对应的处理函数
    if (handlers.contains(action)) {
        handlers[action]();
    } else {
        qWarning() << "Unknown response action:" << action;
    }
}

