#include <QCoreApplication>
#include "AgentController.h"

int main(int argc, char *argv[])
{
    auto controller = new AgentController;

    controller->init();

    return 0;
}
