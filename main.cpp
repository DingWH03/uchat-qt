#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "coreapi.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QQmlContext>
#include "clientmodel.h"

// 打印 QJsonObject 的函数
void printResponse(const QJsonObject &response) {
    QJsonDocument doc(response);
    QString jsonString = doc.toJson(QJsonDocument::Indented); // 将 QJsonObject 转换为格式化的 JSON 字符串
    qDebug() << "Received response:" << jsonString;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<ClientModel>("ClientModel", 1, 0, "ClientModel");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("uchat-qt", "Main");

    // CoreApi api;

    // // 连接信号到自定义槽函数
    // QObject::connect(&api, &CoreApi::serverResponseReceived, printResponse);

    // // 连接 CoreApi 的 connected 信号到发送登录的槽
    // QObject::connect(&api, &CoreApi::connected, [&api]() {
    //     // 连接成功后发送登录请求
    //     api.sendLogin(2, "123456");
    // });

    // api.connectToServer("127.0.0.1", 8080);
    // // api.sendLogin(2, "123456");

    return app.exec();
}


