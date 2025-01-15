// ClientModel.h
#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QtQml>
#include "coreapi.h"
#include "friendListModel.h"
#include "groupListModel.h"
#include "chatmodel.h"

struct UserSimpleInfo {
    quint32 user_id;
    QString username;
};

struct UserDetailedInfo {
    quint32 user_id;
    QString username;
    // 添加其他字段如果有的话
};

struct GroupSimpleInfo {
    quint32 group_id;
    QString title;
};

struct GroupDetailedInfo {
    quint32 group_id;
    QString title;
    // 添加其他字段如果有的话
};

struct Message {
    quint32 sender_id;
    QString message;
    QDateTime timestamp;
};

class ClientModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(FriendListModel* friendList READ friendList CONSTANT)
    Q_PROPERTY(GroupListModel* groupList READ groupList CONSTANT)

    Q_PROPERTY(ChatModel* chatModel READ chatModel NOTIFY chatModelChanged)
    Q_PROPERTY(QString currentChatName READ currentChatName NOTIFY currentChatNameChanged)
    Q_PROPERTY(bool isCurrentChatGroup READ isCurrentChatGroup NOTIFY isCurrentChatGroupChanged)
    Q_PROPERTY(quint32 currentUserId READ currentUserId CONSTANT)

public:
    explicit ClientModel(QObject *parent = nullptr);

    Q_INVOKABLE void connectToServer(const QString &address, int port);
    Q_INVOKABLE void sendLogin(int userId, const QString &password);
    Q_INVOKABLE void sendRegister(const QString &userName, const QString &password);

    FriendListModel* friendList() const { return m_friendList; }
    GroupListModel* groupList() const { return m_groupList; }

    // New methods
    ChatModel* chatModel() const { return m_chatModel; }
    QString currentChatName() const { return m_currentChatName; }
    bool isCurrentChatGroup() const { return m_isCurrentChatGroup; }
    quint32 currentUserId() const { return m_currentUserId; } // Assume you have this

    QString getChatName(quint32 chatId) const;
    Q_INVOKABLE void sendMessage(const QString &text);

    Q_INVOKABLE void setCurrentChat(quint32 chatId); // Method to change current chat


private:
    CoreApi api;
    FriendListModel *m_friendList;
    GroupListModel *m_groupList;

    quint32 m_currentChatId;
    QString m_currentChatName;
    bool m_isCurrentChatGroup;
    quint32 m_currentUserId;

    ChatModel *m_chatModel;

signals:
    void connected();
    void connectionError();
    void loginOk(const QString& message);
    void loginError(const QString& message);
    void registerOk(const QString& message);
    void registerError(const QString& message);
    void genericResponseReceived(const QString& status, const QString& message);
    void messageReceived(quint32 sender, const QString& message, const QString& timestamp);
    void errorReceived(const QString& message);
    void onlineUsersReceived(const QString& flag, const QList<quint32>& userIds);

    // 更新后的信号，使用结构体列表
    void groupMembersReceived(quint32 groupId, const QList<UserSimpleInfo>& memberInfos);
    void friendListReceived(const QList<UserSimpleInfo>& friendInfos);
    void groupListReceived(const QList<GroupSimpleInfo>& groupInfos);

    void userInfoReceived(const UserDetailedInfo& userInfo);
    void groupInfoReceived(const GroupDetailedInfo& groupInfo);
    void messagesReceived(quint32 sender, const QList<Message>& messages);
    void groupMessagesReceived(quint32 groupId, const QList<Message>& messages);

    void chatModelChanged();
    void currentChatNameChanged();
    void isCurrentChatGroupChanged();

private slots:
    void handleConnected();
    void handleConnectionError();
    void handleServerResponse(const QJsonObject& response);

    void onFriendListReceived(const QList<UserSimpleInfo>& friendInfos);
    void onGroupListReceived(const QList<GroupSimpleInfo>& groupInfos);

    void handleMessagesReceived(quint32 sender_id, const QList<Message> &messages);
    void handleGroupMessagesReceived(quint32 group_id, const QList<Message> &messages);
};


#endif // CLIENTMODEL_H
