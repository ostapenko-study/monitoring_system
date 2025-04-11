#include <QCoreApplication>
#include "AgentController.h"

#include "network/network_scanner.h"

#include <iostream>

int main(int argc, char *argv[])
{

    std::cout << "Пошук інтерфейсів\n";
    const auto interfaces = network_scanner::get_interfaces();
    std::cout << "Знайдені інтерфейси:\n";
    for (const auto& interface : interfaces) {
        std::cout << interface.toString().toStdString() << std::endl;
        if(interface.name == "lo"){
            continue;
        }
        if(interface.name.startsWith("br-")){ //linux system networks-bridge (for docker for example)
            continue;
        }

        std::cout << "Знайдені хости:\n";
        for(auto host : interface.scan()){
            std::cout << host.toString().toStdString() << std::endl;
        }
    }


    // auto controller = new AgentController;
    // controller->init();

    return 0;
}
