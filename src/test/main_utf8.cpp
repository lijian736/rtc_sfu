#include <iostream>
#include <fstream>
#include <string>
#include <new>
#include <cstring>
#include <atomic>

#include <unistd.h>
#include <signal.h>

#include "common_utf8.h"

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

	std::string name = "lijian";
	std::cout << "\"lijian\" is utf8 str: " << is_utf8_str(name) << std::endl;
	std::cout << "\"李健\" is utf8 chars: " << is_utf8_chars((const uint8_t*)name.c_str()) << std::endl;

	std::string name1 = "李健";
	std::cout << "\"李健\" is utf8 str: " << is_utf8_str(name1) << std::endl;
	std::cout << "\"李健\" is utf8 chars: " << is_utf8_chars((const uint8_t*)name1.c_str()) << std::endl;

	return 0;
}