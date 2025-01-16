#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QDateTime>
#include <QFile>

struct ChatMessage {
    bool is_mine;
    QString message;
    QDateTime timestamp;
};

class ChatModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ChatRoles {
        isMine,
        MessageRole,
        TimestampRole
    };

    explicit ChatModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Role names for QML
    QHash<int, QByteArray> roleNames() const override;

    // Methods to manage messages
    void addMessage(const ChatMessage &msg);
    void clearMessages();

private:
    QVector<ChatMessage> m_messages;
};

#endif // CHATMODEL_H
