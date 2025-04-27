#include "ServerController.h"
#include "websockets_common.h"
#include "CommandHandler.h"


const QMap<QString, ServerController::HandlerFunc> ServerController::m_command_to_implement = {
    {"get_top_by_ssh", &ServerController::getTopBySshRequest},
    {"get_scan", &ServerController::getScanRequest},
    {"setup_device_by_ssh", &ServerController::setupDeviceBySshRequest},
    };

ServerController::ServerController(QObject *parent)
    : QObject{parent}
{

}

void ServerController::init()
{
    connect(m_server_view, &WebsocketServer::received,
            this, &ServerController::onServerViewReceived);
    connect(m_server_system, &WebsocketServer::received,
            this, &ServerController::onServerSystemReceived);
}

namespace{
#include <QJsonObject>
#include <QJsonArray>

// Функція для обробки PID і пам'яті
QJsonArray processPids(const QJsonArray& pidsArray) {
    QJsonArray resultPidsArray;

    for (const QJsonValue& pidVal : pidsArray) {
        QJsonObject pidObj = pidVal.toObject();

        QJsonObject pidInfo;
        pidInfo["pid"] = pidObj["pid"];
        pidInfo["ppid"] = pidObj["ppid"];
        pidInfo["state"] = pidObj["state"];
        pidInfo["cpu"] = pidObj["cpu"];

        QJsonObject memObj = pidObj["mem"].toObject();
        QJsonObject memoryInfo;
        if (memObj.contains("VmPeak")) memoryInfo["peak"] = memObj["VmPeak"];
        if (memObj.contains("VmSize")) memoryInfo["size"] = memObj["VmSize"];
        if (memObj.contains("VmSwap")) memoryInfo["swap"] = memObj["VmSwap"];
        if (memObj.contains("VmData")) memoryInfo["data"] = memObj["VmData"];
        if (memObj.contains("VmStk"))  memoryInfo["stk"] = memObj["VmStk"];
        if (memObj.contains("VmExe"))  memoryInfo["exe"] = memObj["VmExe"];

        pidInfo["memory"] = memoryInfo;
        resultPidsArray.append(pidInfo);
    }

    return resultPidsArray;
}

// Головна функція перетворення
QJsonObject convert(const QJsonObject& obj) {
    QJsonObject system = obj["system"].toObject();
    QJsonObject mem = system["mem"].toObject();

    QJsonObject pkg;
    pkg["id"] = obj["id"];

    QJsonObject systemObj;
    systemObj["cpu"] = system["cpu"];

    QJsonObject memoryMain;
    memoryMain["buffers"] = mem["Buffers"];
    memoryMain["cached"] = mem["Cached"];
    memoryMain["free"] = mem["MemFree"];
    memoryMain["available"] = mem["MemAvailable"];
    memoryMain["total"] = mem["MemTotal"];

    QJsonObject memorySwap;
    memorySwap["cached"] = mem["SwapCached"];
    memorySwap["free"] = mem["SwapFree"];
    memorySwap["total"] = mem["SwapTotal"];

    QJsonObject memory;
    memory["main"] = memoryMain;
    memory["swap"] = memorySwap;

    systemObj["memory"] = memory;
    pkg["system"] = systemObj;

    // Обробка процесів
    QJsonArray processesArray;
    for (const QJsonValue& processVal : obj["processes"].toArray()) {
        QJsonObject processObj = processVal.toObject();
        QJsonObject proc;
        proc["name"] = processObj["process"];

        // Використовуємо функцію для обробки PIDs
        proc["pids"] = processPids(processObj["pids"].toArray());
        processesArray.append(proc);
    }

    pkg["processes"] = processesArray;

    // Додаємо config і index, як було раніше
    pkg["config"] = obj["config"];
    pkg["index"] = obj["index"];

    // Обробка користувачів
    QJsonArray usersArray;
    for (const QJsonValue& userVal : obj["users"].toArray()) {
        QJsonObject userObj = userVal.toObject();
        QJsonObject user;

        user["user"] = userObj["user"];

        // Використовуємо функцію для обробки PIDs
        user["pids"] = processPids(userObj["pids"].toArray());
        usersArray.append(user);
    }

    pkg["users"] = usersArray;

    return pkg;
}

}

void ServerController::onServerSystemReceived(QJsonObject data)
{
    const auto obj = json::parseStr(data.value("data").toString());
    if(obj.value("index").toString("") == "monitoring_package_by_timer"){
        data["data"] = convert(obj);
    }else{
        data["data"] = obj;
    }
    data["index"] = obj.value("index");
    m_server_view->sendMessageToAll(json::toString(data));
}

void ServerController::onServerViewReceived(QJsonObject obj)
{
    const auto data = obj.value("data").toObject();
    if(obj.contains("to")){ //as proxy
        m_server_system->sendMessage(
            json::toString(data),
            obj.value("to").toString()
        );
    }else{
        auto answer = processMessage(obj);


        answer["command"] = obj.value("command");
        answer["key"] = obj.value("key");
        answer["role"] = obj.value("role");
        answer["index"] = obj.value("index");

        m_server_view->sendMessageToAll(json::toString(answer));
    }
}

QJsonObject ServerController::processMessage(QJsonObject data)
{
    const auto command = data.value("command").toString();

    if(!m_command_to_implement.contains(command))
    {
        return json::generateError("command not find");
    }

    auto func = m_command_to_implement[command];
    return (this->*func)(data.value("data").toObject());
}


QJsonObject ServerController::getTopBySshRequest(const QJsonObject & data)
{
    return command_handler::getTopRequestBySsh(data);
}

QJsonObject ServerController::getScanRequest(const QJsonObject & data)
{
    return command_handler::getScanNetworkRequest(data);
}

QJsonObject ServerController::setupDeviceBySshRequest(const QJsonObject & data)
{
    return command_handler::setupDeviceBySsh(data, m_server_system->port());
}
