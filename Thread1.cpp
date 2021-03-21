#include "Thread1.h"

Thread1::Thread1()
{
	
}

Thread1::~Thread1()
{
	
}

void Thread1::scheduleStop()
{
	this->running = false;

	std::cout << "Received Stop command" << this->id << std::endl;
}

void Thread1::run()
{
	while (this->running) {
		
		srand((unsigned)time(0));
		std::cout << "Thread ID: " << this->id << std::endl;
		int sleepTime = 1 + (rand() % 6);

		int trueSleep = sleepTime * 1000;
		Sleep(trueSleep);
	}
}
