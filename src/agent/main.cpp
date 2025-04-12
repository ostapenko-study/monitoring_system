#include <QCoreApplication>
#include "AgentController.h"
#include "network/network_scanner.h"
#include "qjsonarray.h"

int main(int argc, char *argv[])
{
    const auto full_interfaces = network_scanner::get_full_interfaces();
    qDebug() << full_interfaces.toJson();

    return 0;
}
