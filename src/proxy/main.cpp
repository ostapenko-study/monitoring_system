#include <QCoreApplication>
#include "WebsocketClient.h"
#include "WebsocketServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto server = createWebsocketServer();

    auto client = createWebsocketClient(WebsocketClient::Role::Proxy);

    return a.exec();
}
