#include <QCoreApplication>
#include "AgentController.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto controller = new AgentController;

    controller->init();

    return a.exec();
}
