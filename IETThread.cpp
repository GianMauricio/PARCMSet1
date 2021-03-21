#include "IETThread.h"

/// <summary>
/// Weird C# / Java implementation
/// </summary>

IETThread::IETThread()
{
	
}

IETThread::~IETThread()
{
	
}

void IETThread::start()
{
	std::thread(&IETThread::run, this).detach(); //detach thread
}

void IETThread::Sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
