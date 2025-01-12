// ClientModel.h
#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QtQml>
#include "coreapi.h"

class ClientModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit ClientModel(QObject *parent = nullptr);

    Q_INVOKABLE void connectToServer(const QString &address, int port);
    Q_INVOKABLE void sendLogin(int userId, const QString &password);
    Q_INVOKABLE void sendRegister(const QString &userName, const QString &password);

private:
    CoreApi api;

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
    void userNameReceived(quint32 userId, const QString& username);
    void groupMembersReceived(quint32 groupId, const QList<quint32>& memberIds);
    void friendListReceived(const QList<quint32>& friendIds);
    void groupListReceived(const QList<quint32>& groupIds);

private slots:
    void handleConnected();
    void handleConnectionError();
    void handleServerResponse(const QJsonObject& response);
};


#endif // CLIENTMODEL_H
