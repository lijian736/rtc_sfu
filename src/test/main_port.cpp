#include "common_port_manager.h"
#include <iostream>

int main()
{
	for(uint16_t start = 10000; start < 10100; start++)
	{
		bool availableTCP = PortManager::check_available(start, PortType::PORT_TYPE_TCP);
		bool availableUDP = PortManager::check_available(start, PortType::PORT_TYPE_UDP);

		std::cout << "Port " << start << " available, tcp:" << availableTCP << " udp:" << availableUDP << std::endl;
	}

	for(uint16_t start = 10000; start < 10100; start++)
	{
		bool availableTCP = PortManager::check_available(start, PortType::PORT_TYPE_TCP);
		bool availableUDP = PortManager::check_available(start, PortType::PORT_TYPE_UDP);

		std::cout << "Port " << start << " available, tcp:" << availableTCP << " udp:" << availableUDP << std::endl;
	}

	std::cin.get();

    return 0;
}
