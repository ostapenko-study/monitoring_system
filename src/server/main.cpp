#include <QCoreApplication>
#include "ServerController.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto server_system = createWebsocketServer(WebsocketServer::Role::ServerSystem);
    auto server_view = createWebsocketServer(WebsocketServer::Role::ServerView);

    auto controller = new ServerController;

    controller->setServerSystem(server_system);
    controller->setServerView(server_view);

    return a.exec();
}
