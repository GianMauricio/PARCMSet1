#include "Thread2.h"

Thread2::Thread2()
{
	
}

Thread2::~Thread2()
{
	
}

void Thread2::run()
{
	while (true) {
		srand((unsigned)time(0));
		std::cout << "Thread ID: " << this->id << " I should happen slower" << std::endl;
		int sleepTime = 1 + (rand() % 6);

		int trueSleep = sleepTime * 1000;
		Sleep(trueSleep);
	}
}
