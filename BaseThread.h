#pragma once
#include <iostream>
#include <thread>

//This thread will serve as a basis for single use operations
class BaseThread
{
public:
	BaseThread();
	~BaseThread();

	void start();
	static void Sleep(int ms);

protected:
	virtual void run() = 0;
};
