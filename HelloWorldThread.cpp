#include "HelloWorldThread.h"

HelloWorldThread::HelloWorldThread(int id)
{
	this->id = id;
}

HelloWorldThread::~HelloWorldThread()
{
	
}

void HelloWorldThread::run()
{
	std::cout << "Hello World but thread ID is: " << this->id << std::endl;
}
