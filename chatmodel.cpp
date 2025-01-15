#include "chatmodel.h"

ChatModel::ChatModel(QObject *parent)
    : QAbstractListModel(parent), m_currentChatId(0)
{
}

int ChatModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_messages.size();
}

QVariant ChatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_messages.size())
        return QVariant();

    const ChatMessage &msg = m_messages[index.row()];
    switch (role) {
    case SenderIdRole:
        return msg.sender_id;
    case MessageRole:
        return msg.message;
    case TimestampRole:
        return msg.timestamp;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ChatModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SenderIdRole] = "sender_id";
    roles[MessageRole] = "message";
    roles[TimestampRole] = "timestamp";
    return roles;
}

void ChatModel::addMessage(const ChatMessage &msg)
{
    beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
    m_messages.append(msg);
    endInsertRows();
}

void ChatModel::loadMessages(quint32 chatId)
{
    // // Pseudo-code for loading messages
    // QFile file(QString("chat_%1.json").arg(chatId));
    // if (file.open(QIODevice::ReadOnly)) {
    //     QByteArray data = file.readAll();
    //     QJsonDocument doc = QJsonDocument::fromJson(data);
    //     if (doc.isArray()) {
    //         QJsonArray array = doc.array();
    //         beginResetModel();
    //         m_messages.clear();
    //         for (const QJsonValue &value : array) {
    //             if (value.isObject()) {
    //                 QJsonObject obj = value.toObject();
    //                 ChatMessage msg;
    //                 msg.sender_id = obj["sender_id"].toInt();
    //                 msg.message = obj["message"].toString();
    //                 msg.timestamp = QDateTime::fromString(obj["timestamp"].toString(), Qt::ISODate);
    //                 m_messages.append(msg);
    //             }
    //         }
    //         endResetModel();
    //     }
    //     file.close();
    // }
}

void ChatModel::saveMessages(quint32 chatId)
{
    // Pseudo-code for saving messages
    // QFile file(QString("chat_%1.json").arg(chatId));
    // if (file.open(QIODevice::WriteOnly)) {
    //     QJsonArray array;
    //     for (const ChatMessage &msg : m_messages) {
    //         QJsonObject obj;
    //         obj["sender_id"] = static_cast<int>(msg.sender_id);
    //         obj["message"] = msg.message;
    //         obj["timestamp"] = msg.timestamp.toString(Qt::ISODate);
    //         array.append(obj);
    //     }
    //     QJsonDocument doc(array);
    //     file.write(doc.toJson());
    //     file.close();
    // }
}


void ChatModel::clearMessages()
{
    beginResetModel();
    m_messages.clear();
    endResetModel();
}
