#include "CommandHandler.h"
#include "ClientConfig.h"
#include "WebsocketClient.h"
#include "WebsocketServer.h"
#include "network/network_scanner.h"
#include "websockets_common.h"
#include "stat/MainStat.h"
#include "inspector_common.h"

namespace command_handler
{

QJsonObject& appendIndex(QJsonObject &output, const QJsonObject &request)
{
    output["index"] = request.value("index");
    return output;
}

namespace {

template<typename Func>
QJsonObject wrapWithErrorHandling(Func func, const QJsonObject& data)
{
    try {
        return json::generateResult(func(data));
    } catch (const std::exception& ex) {
        QJsonObject error = json::generateError(QString::fromStdString(ex.what()));
        return appendIndex(error, data);
    } catch (...) {
        QJsonObject error = json::generateError("Unknown error");
        return appendIndex(error, data);
    }
}


QString generateSshBackgroundCommand(QString app_name){
    return "sh -c \'nohup " + app_name + " > /dev/null 2>&1 < /dev/null &\'";
}



QJsonObject __getTopRequest(const QJsonObject& data)
{
    const auto stats = getProcessTopInfos();
    QJsonObject answer;
    answer["top"] = json::containerToJson(stats.begin(), stats.end());
    return json::generateResult(appendIndex(answer, data));
}

QJsonObject __getScanNetworkRequest(const QJsonObject& data)
{
    QJsonObject answer;
    answer["interfaces"] = network_scanner::get_full_interfaces().toJson();
    return json::generateResult(appendIndex(answer, data));
}

QJsonObject __getTopRequestBySsh(const QJsonObject & data)
{
    const auto stats = getProcessTopInfosBySsh(SshCredentials::fromJson(data));
    QJsonObject answer;
    answer["top"] = json::containerToJson(stats.begin(), stats.end());
    return json::generateResult(appendIndex(answer, data));
}

}

#define WRAPPER_FUNC(func_name) QJsonObject func_name(const QJsonObject & data) {return wrapWithErrorHandling(__##func_name, data); }
WRAPPER_FUNC(getTopRequest)
WRAPPER_FUNC(getScanNetworkRequest)
WRAPPER_FUNC(getTopRequestBySsh)
#undef WRAPPER_FUNC

QJsonObject setupDeviceBySsh(const QJsonObject& data, int port)
{
    static const auto apps = {"agent", "proxy"};

    auto ssh_credentials = SshCredentials::fromJson(data);
    const auto interface = network_scanner::find_interface_by_ip(ssh_credentials.ip);

    if(!interface.has_value())
    {
        return json::generateError("don't find network interface");
    }

    static const QString tmp_dir = "~/.monitoring_system_tmp/";
    static const QString remote_dir = "~/.monitoring_system/";

    if(!ensureDirectoryExists(tmp_dir))
    {
        return json::generateError("don't find tmp folder");
    }

    for(const auto& app : apps){
        run_local_bash_command(QString("cp ./") + app + tmp_dir);
    }

    {
        ClientConfig config;
        config.server_ip = interface->ip.toString();
        config.server_port = port;
        config.client_key = data.value("name_id").toString();

        for(auto role : {
                 WebsocketClient::Role::Agent,
                 WebsocketClient::Role::Proxy,
                 WebsocketClient::Role::Sender,
             }){
            file::write(tmp_dir + getClientWebsocketConfigFileNameByRole(role), json::toString(config.toJson()));
        }
    }

    {
        ServerConfig config;
        config.server_name = data.value("name_id").toString();
        config.port = 18000;
        for(auto role : {
                 WebsocketServer::Role::Proxy,
             }){
            file::write(tmp_dir + getServerWebsocketConfigFileNameByRole(role), json::toString(config.toJson()));
        }
    }

    auto responce = run_sсp_from_local_to_remote(ssh_credentials, "-r " + tmp_dir.toStdString(), remote_dir.toStdString());

    //check responce

    for(const auto& app : apps){
        if(data.value(app).toBool()){
            run_ssh(ssh_credentials, generateSshBackgroundCommand(remote_dir + app));
        }
    }

    return json::generateResult({});
}

}
