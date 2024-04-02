#include <iostream>
#include <fstream>
#include <string>
#include <new>
#include <cstring>
#include <atomic>

#include <unistd.h>
#include <signal.h>

#include "common_random_device.h"
#include "common_random.h"

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

	Random random;
	RandomDevice randomDevice;

	std::cout << "Random 8:" << std::endl;
	for(int i = 0; i < 10; i++)
	{
		std::cout << i << " : " << (int)random.get_random8() << std::endl;
	}

	std::cout << "Random 16:" << std::endl;
	for(int i = 0; i < 10; i++)
	{
		std::cout << i << " : " << random.get_random16() << std::endl;
	}

	std::cout << "Random 32:" << std::endl;
	for(int i = 0; i < 10; i++)
	{
		std::cout << i << " : " << random.get_random32() << std::endl;
	}

	std::cout << "Random double:" << std::endl;
	for(int i = 0; i < 10; i++)
	{
		std::cout << i << " : " << random.get_random_double() << std::endl;
	}


	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	std::cout << "RandomDevice 8:" << std::endl;
	for(int i = 0; i < 10; i++)
	{
		std::cout << i << " : " << (int)randomDevice.get_random8() << std::endl;
	}

	std::cout << "RandomDevice 16:" << std::endl;
	for(int i = 0; i < 10; i++)
	{
		std::cout << i << " : " << randomDevice.get_random16() << std::endl;
	}

	std::cout << "RandomDevice 32:" << std::endl;
	for(int i = 0; i < 10; i++)
	{
		std::cout << i << " : " << randomDevice.get_random32() << std::endl;
	}

	std::cout << "RandomDevice double:" << std::endl;
	for(int i = 0; i < 10; i++)
	{
		std::cout << i << " : " << randomDevice.get_random_double() << std::endl;
	}


	return 0;
}