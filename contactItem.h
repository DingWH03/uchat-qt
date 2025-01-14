// ContactItem.h
#ifndef CONTACTITEM_H
#define CONTACTITEM_H

#include <QObject>
#include <QString>

class FriendItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(quint32 id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit FriendItem(QObject *parent = nullptr) : QObject(parent), m_id(0) {}
    FriendItem(quint32 id, const QString &name, QObject *parent = nullptr)
        : QObject(parent), m_id(id), m_name(name) {}

    quint32 id() const { return m_id; }
    void setId(quint32 id) {
        if (m_id != id) {
            m_id = id;
            emit idChanged();
        }
    }

    QString name() const { return m_name; }
    void setName(const QString &name) {
        if (m_name != name) {
            m_name = name;
            emit nameChanged();
        }
    }

signals:
    void idChanged();
    void nameChanged();

private:
    quint32 m_id;
    QString m_name;
};

class GroupItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(quint32 id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    explicit GroupItem(QObject *parent = nullptr) : QObject(parent), m_id(0) {}
    GroupItem(quint32 id, const QString &title, QObject *parent = nullptr)
        : QObject(parent), m_id(id), m_title(title) {}

    quint32 id() const { return m_id; }
    void setId(quint32 id) {
        if (m_id != id) {
            m_id = id;
            emit idChanged();
        }
    }

    QString title() const { return m_title; }
    void setTitle(const QString &title) {
        if (m_title != title) {
            m_title = title;
            emit titleChanged();
        }
    }

signals:
    void idChanged();
    void titleChanged();

private:
    quint32 m_id;
    QString m_title;
};

#endif // CONTACTITEM_H
