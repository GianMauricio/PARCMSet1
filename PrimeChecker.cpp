#include "PrimeChecker.h"

PrimeChecker::PrimeChecker(int id, int target, int upperbound, int lowerbound)
{
	this->id = id;
	this->target = target;
	this->upperBound = upperbound;
	this->lowerBound = lowerbound;
}

PrimeChecker::~PrimeChecker()
{
	
}

bool PrimeChecker::Result()
{
	if(this->target == 3)
	{
		return true;
	}

	if (this->target == 5)
	{
		return true;
	}

	if (this->target == 7)
	{
		return true;
	}
	
	return this->proof;
}

bool PrimeChecker::getState()
{
	return this->isChecking;
}

void PrimeChecker::run()
{
	if(this->target > 4)
	{
		//If no number until x / 2 divides the number perfectly, no other number will
		for (int i = lowerBound; i < upperBound; i++)
		{
			if (this->target % i == 0)
			{
				this->proof = false;
			}
		}
	}
	isChecking = false;
}
