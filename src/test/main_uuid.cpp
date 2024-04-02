#include <iostream>
#include <fstream>
#include <string>
#include <new>
#include <cstring>
#include <atomic>

#include <unistd.h>
#include <signal.h>

#include "common_uuid.h"
#include "common_utils.h"

static std::atomic<bool> g_interrupted(false);

void sigint_handler(int sig)
{
    g_interrupted = true;
}

int main(int argc, char *argv[])
{
	signal( SIGINT, sigint_handler );
    signal( SIGTERM, sigint_handler );
	signal( SIGTSTP, sigint_handler );

	std::cout << "is little endian:" << is_little_endian() << std::endl;
	for(int i = 0; i < 10; i++)
	{
		std::cout << get_uuid() << std::endl;
	}

	return 0;
}