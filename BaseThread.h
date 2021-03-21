#pragma once
#include <iostream>
#include <thread>
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
