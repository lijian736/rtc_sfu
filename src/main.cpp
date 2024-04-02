#include <iostream>

#include <errno.h>
#include <string.h>

#include "common_logger.h"
#include "common_utils.h"
#include "io_utils.h"
#include "io_socket_handler_mgr.h"
#include "io_udp_carrier.h"
#include "app_forward.h"

AppLogger *g_pLogger = NULL;
int g_log_level = LOG_LEVEL_VERBOSE;

int main()
{
	UdpCarrierHandler* udpCarrier = nullptr;
	AppForward* appForward = nullptr;
	bool cycle = false;
	bool ret = false;

    if (!check_path_exists("/home/lijian/testlog"))
	{
		std::cout << "/home/lijian/testlog does not exists, create recursively" << std::endl;
		bool createRet = create_directory_recursively("/home/lijian/testlog");
		std::cout << "create /home/lijian/testlog returns:" << createRet << std::endl;
		if(!createRet)
		{
			std::cout << "mkdir returns: " << strerror(errno) << std::endl;
		}
	}

	AppLogger *pLogger = new AppLogger("logger");
	if (pLogger)
	{
		ret = pLogger->initialize("/home/lijian/testlog", false, 1024 * 5, 10);
		std::cout << "AppLogger::initialize(): " << ret << std::endl;
	}
	g_pLogger = pLogger;

	LOG_INFO("Program begins.......");

	std::cout << "epoll supported: " << is_epoll_supported() << std::endl;

	//the udp carrier lifetime is managed by IOSocketHandlerMgr
	udpCarrier = UdpCarrierHandler::create("0.0.0.0", 30002, 64, 64);
	if(!udpCarrier)
	{
		std::cout << "Create UDP Carrier failed" << std::endl;
		goto exitFlag;
	}

	appForward = new AppForward();
	if(!appForward)
	{
		std::cout << "Create AppForward failed" << std::endl;
		goto exitFlag;
	}

	udpCarrier->set_udp_protocol(appForward);
	appForward->set_udp_carrier(udpCarrier);

    ret = IOSocketHandlerMgr::init();
    if(!ret)
    {
        std::cout << "IOSocketHandlerMgr::init() error occurs. " << std::endl;
        return 0;
    }

	udpCarrier->add_destination("192.168.0.100", 32000);
	ret = udpCarrier->start();
	if(!ret)
	{
		std::cout << "udpCarrier->start() error occurs. " << std::endl;
	}

    do
    {
        cycle = IOSocketHandlerMgr::cycle();
        IOSocketHandlerMgr::delete_inactive_handlers();
        
    }while(cycle);

    IOSocketHandlerMgr::close_all_iohandlers();
    IOSocketHandlerMgr::delete_inactive_handlers();

    ret = IOSocketHandlerMgr::shutdown();

exitFlag:

    LOG_INFO("Program ends.......");

	if(appForward)
	{
		delete appForward;
	}

	if (g_pLogger)
	{
		g_pLogger->uninitialize();
		delete g_pLogger;
	}

	std::cin.get();

    return 0;
}
