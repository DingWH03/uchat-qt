#ifndef COREAPI_H
#define COREAPI_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QMutex>
#include <QByteArray>

class CoreApi : public QObject
{
    Q_OBJECT
public:
    explicit CoreApi(QObject* parent = nullptr);
    ~CoreApi();

    // 对外暴露的API
    Q_INVOKABLE void connectToServer(const QString& address, quint16 port);
    Q_INVOKABLE void sendRegister(const QString& username, const QString& password);
    Q_INVOKABLE void sendLogin(quint32 userId, const QString& password);
    Q_INVOKABLE void sendMessage(quint32 group_id, quint32 receiver, const QString& message);
    Q_INVOKABLE void getOnlineUsers();
    Q_INVOKABLE void getGroups();
    Q_INVOKABLE void getFriends();
    Q_INVOKABLE void addFriend(quint32 user_id);
    Q_INVOKABLE void newGroup(QString groupName);

signals:
    void connected();
    void connectionError(const QString& error);
    void serverResponseReceived(const QJsonObject& response);

private slots:
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket* socket;
    QByteArray readBuffer;
    QMutex bufferMutex;

    void writerPacket(const QJsonObject& json);
};

#endif // COREAPI_H
