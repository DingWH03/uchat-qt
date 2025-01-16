#include "chatmodel.h"

ChatModel::ChatModel(QObject *parent)
    : QAbstractListModel(parent)
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
    case isMine:
        return msg.is_mine;
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
    roles[isMine] = "is_mine";
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


void ChatModel::clearMessages()
{
    beginResetModel();
    m_messages.clear();
    endResetModel();
}
