#pragma once
#include "BaseThread.h"
//For randomness
#include <stdlib.h>
#include <ctime>

class Thread2 : public BaseThread
{
public:
	Thread2();
	~Thread2();

protected:
	void run() override;
	int id = 2;
};

