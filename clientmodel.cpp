// ClientModel.cpp
#include "clientmodel.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QHash>
#include <functional>
ClientModel::ClientModel(QObject *parent)
    : QObject(parent),
    m_friendList(new FriendListModel(this)),
    m_groupList(new GroupListModel(this))
{
    // 连接 CoreApi 的信号到 ClientModel 的槽
    connect(&api, &CoreApi::connected, this, &ClientModel::handleConnected);
    connect(&api, &CoreApi::connectionError, this, &ClientModel::handleConnectionError);
    connect(&api, &CoreApi::serverResponseReceived, this, &ClientModel::handleServerResponse);
    connect(this, &ClientModel::friendListReceived, this, &ClientModel::onFriendListReceived);
    connect(this, &ClientModel::groupListReceived, this, &ClientModel::onGroupListReceived);

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
    // FriendItem *test = new FriendItem;
    // test->setId(1);
    // test->setName("dwh");
    // m_friendList->addFriend(test);
    // GroupItem *test2 = new GroupItem;
    // test2->setId(1);
    // test2->setTitle("group2");
    // m_groupList->addGroup(test2);

    // QList<FriendItem> friends = api.getFriends();
    // for (const FriendItem &friendItem : friends) {
    //     m_friendList->addFriend(friendItem);
    // }

    // QList<GroupItem> groups = api.getGroups();
    // for (const GroupItem &groupItem : groups) {
    //     m_groupList->addGroup(groupItem);
    // }
}

void ClientModel::handleConnectionError() {
    emit connectionError();
}

void ClientModel::onFriendListReceived(const QList<UserSimpleInfo>& friendInfos) {
    // 清空当前好友列表
    m_friendList->clear();

    // 遍历接收到的好友信息并添加到 FriendListModel
    for (const UserSimpleInfo& info : friendInfos) {
        FriendItem *friendItem = new FriendItem;
        friendItem->setId(info.user_id);
        friendItem->setName(info.username);
        m_friendList->addFriend(friendItem);
    }

    qDebug() << "Friend list updated with" << friendInfos.size() << "friends.";
}

void ClientModel::onGroupListReceived(const QList<GroupSimpleInfo>& groupInfos) {
    // 清空当前群组列表
    m_groupList->clear();

    // 遍历接收到的群组信息并添加到 GroupListModel
    for (const GroupSimpleInfo& info : groupInfos) {
        GroupItem *groupItem = new GroupItem;
        groupItem->setId(info.group_id);
        groupItem->setTitle(info.title);
        m_groupList->addGroup(groupItem);
    }

    qDebug() << "Group list updated with" << groupInfos.size() << "groups.";
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
             QString timestampStr = response.value("timestamp").toString();
             // 解析时间戳
             QDateTime timestamp = QDateTime::fromString(timestampStr, Qt::ISODate);
             emit messageReceived(sender, message, timestampStr);
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
        // 更新后的 "group_members" 处理逻辑
        {"group_members", [&]() {
             quint32 groupId = response.value("group_id").toInt();
             QJsonArray memberInfosArray = response.value("member_ids").toArray();
             QList<UserSimpleInfo> memberInfos;
             for (const QJsonValue& value : memberInfosArray) {
                 QJsonObject memberObj = value.toObject();
                 UserSimpleInfo member;
                 member.user_id = memberObj.value("user_id").toInt();
                 member.username = memberObj.value("username").toString();
                 // 如果有更多字段，继续解析
                 memberInfos.append(member);
             }
             emit groupMembersReceived(groupId, memberInfos);
         }},
        // 更新后的 "friend_list" 处理逻辑
        {"friend_list", [&]() {
             QJsonArray friendInfosArray = response.value("friends").toArray();
             QList<UserSimpleInfo> friendInfos;
             for (const QJsonValue& value : friendInfosArray) {
                 QJsonObject friendObj = value.toObject();
                 UserSimpleInfo friendInfo;
                 friendInfo.user_id = friendObj.value("user_id").toInt();
                 friendInfo.username = friendObj.value("username").toString();
                 // 如果有更多字段，继续解析
                 friendInfos.append(friendInfo);
             }
             emit friendListReceived(friendInfos);
         }},
        // 更新后的 "group_list" 处理逻辑
        {"group_list", [&]() {
             QJsonArray groupInfosArray = response.value("groups").toArray();
             QList<GroupSimpleInfo> groupInfos;
             for (const QJsonValue& value : groupInfosArray) {
                 QJsonObject groupObj = value.toObject();
                 GroupSimpleInfo groupInfo;
                 groupInfo.group_id = groupObj.value("group_id").toInt();
                 groupInfo.title = groupObj.value("title").toString();
                 // 如果有更多字段，继续解析
                 groupInfos.append(groupInfo);
             }
             emit groupListReceived(groupInfos);
         }},
        {"userinfo", [&]() {
             quint32 userId = response.value("user_id").toInt();
             QJsonObject userinfoObj = response.value("userinfo").toObject();
             UserDetailedInfo userInfo;
             userInfo.user_id = userinfoObj.value("user_id").toInt();
             userInfo.username = userinfoObj.value("username").toString();
             // 解析其他字段如果有的话
             emit userInfoReceived(userInfo);
         }},
        {"groupinfo", [&]() {
             quint32 groupId = response.value("group_id").toInt();
             QJsonObject groupinfoObj = response.value("groupinfo").toObject();
             GroupDetailedInfo groupInfo;
             groupInfo.group_id = groupinfoObj.value("group_id").toInt();
             groupInfo.title = groupinfoObj.value("title").toString();
             // 解析其他字段如果有的话
             emit groupInfoReceived(groupInfo);
         }},
        {"messages", [&]() {
             quint32 sender = response.value("sender").toInt();
             QJsonArray messagesArray = response.value("messages").toArray();
             QList<Message> messages;
             for (const QJsonValue& value : messagesArray) {
                 QJsonObject msgObj = value.toObject();
                 Message msg;
                 msg.sender_id = msgObj.value("sender_id").toInt();
                 msg.message = msgObj.value("message").toString();
                 QString timestampStr = msgObj.value("timestamp").toString();
                 msg.timestamp = QDateTime::fromString(timestampStr, Qt::ISODate);
                 messages.append(msg);
             }
             emit messagesReceived(sender, messages);
         }},
        {"groupmessages", [&]() {
             quint32 groupId = response.value("group_id").toInt();
             QJsonArray messagesArray = response.value("messages").toArray();
             QList<Message> messages;
             for (const QJsonValue& value : messagesArray) {
                 QJsonObject msgObj = value.toObject();
                 Message msg;
                 msg.sender_id = msgObj.value("sender_id").toInt();
                 msg.message = msgObj.value("message").toString();
                 QString timestampStr = msgObj.value("timestamp").toString();
                 msg.timestamp = QDateTime::fromString(timestampStr, Qt::ISODate);
                 messages.append(msg);
             }
             emit groupMessagesReceived(groupId, messages);
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
                 // api.addFriend(3);
                 // api.newGroup("test");
                 api.getGroups();
                 api.getFriends();
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
