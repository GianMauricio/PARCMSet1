#pragma once
#include <iostream>
#include <thread>

class IETThread
{
public:
	IETThread();
	~IETThread();

	void start();
	static void Sleep(int ms);

protected:
	virtual void run() = 0;
};