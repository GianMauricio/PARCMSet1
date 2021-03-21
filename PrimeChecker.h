#pragma once
#include "BaseThread.h"
class PrimeChecker : public BaseThread
{
public:
	PrimeChecker(int id, int number, int upperbound, int lowerbound);
	~PrimeChecker();


	bool Result();
	bool getState();
private:
	void run() override;
	bool proof = true;
	bool isChecking = true;
	int id = 0;
	int target = 0;
	int upperBound = 0;
	int lowerBound = 0;
};

