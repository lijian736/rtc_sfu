#include <iostream>
#include <errno.h>
#include <string.h>

#include "common_logger.h"
#include "common_utils.h"


AppLogger *g_pLogger = NULL;
int g_log_level = LOG_LEVEL_VERBOSE;

int main()
{
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
		bool ret = pLogger->initialize("/home/lijian/testlog", false, 1024 * 5, 10);
		std::cout << "AppLogger::initialize(): " << ret << std::endl;
	}
	g_pLogger = pLogger;

	LOG_INFO("Program begins.......");

	for (int i = 0; i < 100000; i++)
	{
		LOG_INFO("%d", i);
	}

	LOG_INFO("Program ends.......");

	std::this_thread::sleep_for(std::chrono::seconds(10));
	if (g_pLogger)
	{
		g_pLogger->uninitialize();
		delete g_pLogger;
	}

	return 0;
}
