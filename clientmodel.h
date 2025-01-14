// ClientModel.h
#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QtQml>
#include "coreapi.h"
#include "friendListModel.h"
#include "groupListModel.h"

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

public:
    explicit ClientModel(QObject *parent = nullptr);

    Q_INVOKABLE void connectToServer(const QString &address, int port);
    Q_INVOKABLE void sendLogin(int userId, const QString &password);
    Q_INVOKABLE void sendRegister(const QString &userName, const QString &password);

    FriendListModel* friendList() const { return m_friendList; }
    GroupListModel* groupList() const { return m_groupList; }


private:
    CoreApi api;
    FriendListModel *m_friendList;
    GroupListModel *m_groupList;

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

private slots:
    void handleConnected();
    void handleConnectionError();
    void handleServerResponse(const QJsonObject& response);

    void onFriendListReceived(const QList<UserSimpleInfo>& friendInfos);
    void onGroupListReceived(const QList<GroupSimpleInfo>& groupInfos);
};


#endif // CLIENTMODEL_H
