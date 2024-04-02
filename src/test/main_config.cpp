#include "app_config.h"
#include <iostream>

int main()
{
	AppConfig* config = AppConfig::get_instance();
	if (config->initialize("config.cfg", "=", "#"))
	{
		bool ret = config->is_config_file_exists();
		std::cout << "The config file [config.cfg] exists:" << ret << std::endl;

		ret = config->read_and_parse();
		std::cout << "The config file [config.cfg] read and parse:" << ret << std::endl;

		std::string serverIP = AppConfig::get_instance()->get_by_key("server_ip", "127.0.0.1");
		std::string serverPort = AppConfig::get_instance()->get_by_key("server_port", "8080");
		std::cout << "server ip: " << serverIP << " port: " << serverPort << std::endl;

		std::string name = AppConfig::get_instance()->get_by_key("name", "invalid_name");
		std::string uuid = AppConfig::get_instance()->get_by_key("uuid", "invalid_uuid");
		std::cout << "name: " << name << " uuid: " << uuid << std::endl;

		std::cout << "the configs list: \n" << *config << std::endl;
	}

	std::cin.get();

    return 0;
}
