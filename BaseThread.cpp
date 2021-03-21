#include "BaseThread.h"

//Never instantiate this, if you do you will die
BaseThread::BaseThread()
{

}

BaseThread::~BaseThread()
{

}

void BaseThread::start()
{
	std::thread(&BaseThread::run, this).detach(); //detach thread
}

void BaseThread::Sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
