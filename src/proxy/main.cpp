#include <QCoreApplication>
#include "ProxySocketController.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto proxy_socket_constoller = new ProxySocketController();

    auto server = createWebsocketServer();
    auto client = createWebsocketClient(WebsocketClient::Role::Proxy);

    proxy_socket_constoller->setServer(server);
    proxy_socket_constoller->setClient(client);

    proxy_socket_constoller->init();

    return a.exec();
}
