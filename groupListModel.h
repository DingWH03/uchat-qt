// GroupListModel.h
#ifndef GROUPLISTMODEL_H
#define GROUPLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "contactItem.h"

class GroupListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum GroupRoles {
        IdRole = Qt::UserRole + 1,
        TitleRole
    };

    GroupListModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}

    void addGroup(GroupItem* groupItem) {
        beginInsertRows(QModelIndex(), m_groups.size(), m_groups.size());
        m_groups.append(groupItem);
        endInsertRows();
    }

    void clear() {
        beginResetModel();
        qDeleteAll(m_groups); // 释放所有 GroupItem 对象
        m_groups.clear();
        endResetModel();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return m_groups.count();
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid() || index.row() < 0 || index.row() >= m_groups.size())
            return QVariant();

        GroupItem* groupItem = m_groups[index.row()];
        if (role == IdRole)
            return groupItem->id();
        else if (role == TitleRole)
            return groupItem->title();
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[IdRole] = "id";
        roles[TitleRole] = "title";
        return roles;
    }

    ~GroupListModel() {
        qDeleteAll(m_groups); // 确保在模型销毁时释放所有 GroupItem 对象
    }

private:
    QList<GroupItem*> m_groups;
};

#endif // GROUPLISTMODEL_H
