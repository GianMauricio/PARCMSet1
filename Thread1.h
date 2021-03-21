#pragma once
#include "BaseThread.h"
//For randomness
#include <stdlib.h>
#include <ctime>

class Thread1 : public BaseThread
{
public:
	Thread1();
	~Thread1();

	void scheduleStop();

protected:
	void run() override;
	int id = 1;
	bool running = true;
};

