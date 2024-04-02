#include "common_address_ipv4.h"
#include <iostream>

int main()
{
	IPAddrV4 a("192.168.0.1", 8008);
	IPAddrV4 b("192.168.0.1", 8008);

	std::cout << "a ip: " << a.get_ipaddr() << " port:" << a.get_port() << std::endl;
	std::cout << "a is equal b: " << (a == b) << std::endl;

	std::cin.get();

    return 0;
}
