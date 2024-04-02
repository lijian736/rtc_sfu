#include "common_simple_timer.h"
#include <iostream>

#include <unistd.h>
#include <signal.h>

SimpleTimer timer;
void sigint_handler(int sig)
{
    timer.cancel_timer();
}

int g_count = 0;

int main()
{
	timer.run_once_async(1000, [&](int param){
		std::cout << "run_once_async, param: " << param << std::endl;
	}, 32);

	timer.run_once_sync(2000, [&](int param){
		std::cout << "run_once_sync, param: " << param << std::endl;
	}, 64);

	timer.run_repeatedly(5000, [](){
		g_count++;
		std::cout << "The current count is: " << g_count << std::endl;
	});

	std::cin.get();

    return 0;
}
