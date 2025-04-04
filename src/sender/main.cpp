#include <QCoreApplication>
#include "WebsocketClient.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    if(argc == 1){
        qWarning("need one argument");
        return EXIT_FAILURE;
    }else if(argc != 2){
        qWarning("need only one argument");
        return EXIT_FAILURE;
    }

    auto client = createWebsocketClient(WebsocketClient::Role::Sender);
    client->sendMessage(QString::fromStdString(std::string(argv[1])));

    return EXIT_SUCCESS;
}
