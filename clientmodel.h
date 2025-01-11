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
    Q_INVOKABLE void test();

private:
    CoreApi api;

signals:
    void connected();

private slots:
    void handleConnected();
    void handleServerResponse(const QJsonObject& response);
};


#endif // CLIENTMODEL_H
