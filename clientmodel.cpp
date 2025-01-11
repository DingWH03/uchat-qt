// ClientModel.cpp
#include "clientmodel.h"
#include <QJsonObject>
#include <QJsonDocument>
ClientModel::ClientModel(QObject *parent) : QObject(parent) {
    // 连接 CoreApi 的信号到 ClientModel 的槽
    connect(&api, &CoreApi::connected, this, &ClientModel::handleConnected);
    connect(&api, &CoreApi::serverResponseReceived, this, &ClientModel::handleServerResponse);
}

void ClientModel::connectToServer(const QString &address, int port) {
    api.connectToServer(address, port);
}

void ClientModel::sendLogin(int userId, const QString &password) {
    api.sendLogin(userId, password);
}

void ClientModel::handleConnected() {
    emit connected();
    // 连接成功后自动发送登录请求（如果需要）
    // api.sendLogin(2, "123456");
}

void ClientModel::handleServerResponse(const QJsonObject& response) {
    QJsonDocument doc(response);
    QString jsonString = doc.toJson(QJsonDocument::Indented); // 将 QJsonObject 转换为格式化的 JSON 字符串
    qDebug() << "Received response:" << jsonString;
}

void ClientModel::test(){
    qDebug()<<"Hello";
}
