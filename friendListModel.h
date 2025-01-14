// FriendListModel.h
#ifndef FRIENDLISTMODEL_H
#define FRIENDLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "contactItem.h"

class FriendListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum FriendRoles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };

    FriendListModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}

    void addFriend(FriendItem* friendItem) {
        beginInsertRows(QModelIndex(), m_friends.size(), m_friends.size());
        m_friends.append(friendItem);
        endInsertRows();
    }

    void clear() {
        beginResetModel();
        qDeleteAll(m_friends); // 释放所有 FriendItem 对象
        m_friends.clear();
        endResetModel();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return m_friends.count();
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid() || index.row() < 0 || index.row() >= m_friends.size())
            return QVariant();

        FriendItem* friendItem = m_friends[index.row()];
        if (role == IdRole)
            return friendItem->id();
        else if (role == NameRole)
            return friendItem->name();
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[IdRole] = "id";
        roles[NameRole] = "name";
        return roles;
    }

    ~FriendListModel() {
        qDeleteAll(m_friends); // 确保在模型销毁时释放所有 FriendItem 对象
    }

private:
    QList<FriendItem*> m_friends;
};

#endif // FRIENDLISTMODEL_H
