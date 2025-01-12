#include "coreapi.h"
#include <QJsonDocument>
#include <QDataStream>
#include <QDebug>

CoreApi::CoreApi(QObject* parent)
    : QObject(parent),
    socket(new QTcpSocket(this))
{
    // 连接信号与槽
    connect(socket, &QTcpSocket::connected, this, &CoreApi::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &CoreApi::onReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, &CoreApi::onErrorOccurred);
}

CoreApi::~CoreApi()
{
    if (socket->isOpen()) {
        socket->close();
    }
}

void CoreApi::connectToServer(const QString& address, quint16 port)
{
    if (socket->state() != QAbstractSocket::UnconnectedState) {
        qWarning() << "Socket is already connected or connecting.";
        return;
    }
    socket->connectToHost(address, port);
}

void CoreApi::onConnected()
{
    qDebug() << "已连接到服务器。";
    emit connected();
}

void CoreApi::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    QString errorString = socket->errorString();
    qDebug() << "连接错误:" << errorString;
    emit connectionError(errorString);
}

void CoreApi::sendRegister(const QString& username, const QString& password)
{
    QJsonObject request;
    request["action"] = "register";
    request["username"] = username;
    request["password"] = password;

    writerPacket(request);
}

void CoreApi::sendLogin(quint32 userId, const QString& password)
{
    QJsonObject request;
    request["action"] = "login";
    request["user_id"] = static_cast<int>(userId);
    request["password"] = password;

    writerPacket(request);
}

void CoreApi::sendMessage(quint32 receiver, const QString& message)
{
    QJsonObject request;
    request["action"] = "send_message";
    request["receiver"] = static_cast<int>(receiver);
    request["message"] = message;

    writerPacket(request);
}

void CoreApi::getOnlineUsers()
{
    QJsonObject request;
    request["action"] = "request";
    request["request"] = "online_users";

    writerPacket(request);
}

/// 向服务器发送请求函数
void CoreApi::writerPacket(const QJsonObject& json)
{
    if (socket->state() != QAbstractSocket::ConnectedState) {
        qWarning() << "Socket is not connected.";
        return;
    }

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    quint32 length = jsonData.size();
    QByteArray packet;

    // 使用 QDataStream 以大端序写入长度
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    stream << length;
    stream.writeRawData(jsonData.constData(), jsonData.size());

    qint64 bytesWritten = socket->write(packet);
    if (bytesWritten == -1) {
        qWarning() << "写入数据失败:" << socket->errorString();
    } else {
        qDebug() << "发送数据字节数:" << bytesWritten;
    }
}

/// 监听服务器响应
void CoreApi::onReadyRead()
{
    QMutexLocker locker(&bufferMutex);
    readBuffer.append(socket->readAll());

    while (readBuffer.size() >= 4) { // 至少4字节用于长度
        // 解析长度字段
        QByteArray lengthBytes = readBuffer.left(4);
        quint32 length = 0;

        QDataStream lengthStream(lengthBytes);
        lengthStream.setByteOrder(QDataStream::BigEndian);
        lengthStream >> length;

        if (readBuffer.size() < 4 + length)
            break; // 数据不足，等待更多数据

        QByteArray jsonData = readBuffer.mid(4, length);
        readBuffer.remove(0, 4 + length);

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qWarning() << "解析 JSON 失败:" << parseError.errorString();
            continue;
        }

        if (!doc.isObject()) {
            qWarning() << "接收到的 JSON 不是对象。";
            continue;
        }

        QJsonObject response = doc.object();
        qDebug() << "接收到服务器响应:" << response;

        emit serverResponseReceived(response);
    }
}
