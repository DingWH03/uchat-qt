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

    return app.exec();
}


