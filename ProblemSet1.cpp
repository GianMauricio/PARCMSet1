/// The objective is simple. Using the test case of 2147483647, the highest prime number that fits into an int data type
/// Create a multi-threaded algorithm that proves that it is in fact a prime number.
/// The algorithm must perform faster than a normal program
/// You must also observe an inverted-bell pattern in relation to the number of threads spawned.
///
/// If the patterns don't line up, or are to small to observe, consider switching to the "long" data type and use the insane prime number
/// 2305843009213693951

#include <iostream>
#include <vector>
#include "PrimeChecker.h"

//Using Intel Core i5 - 10600K, 6 cores
//Compounded increment of 1000ms, for the sake of letting the diagnostics window catch up
/*
 * 2 = 3.439s / 3.461s / 3.530s
 * 4 = 2.439s / 2.461s / 2.456s
 * 8 = 1.822s / 1.851s / 1.811s
 * 16 = 1.714s / 1.692s / 1.723s
 * 32 = 1.587s / 1.615s / 1.573s
 * 64 = 1.556s / 1.545s / 1.536s
 * 128 = 1.593s / 1.608s / 1.592s
 * 256 = 1.770s / 1.675s
 * 2048 = 1.237s???
 * 4096 =
 * 8192> =
 */

//Using...

//Typedef the list type
typedef  std::vector<PrimeChecker*> PrimeTracker;

//ooga booga implementation (Time taken 4-5s)
bool checkNumber(int number);

//Standard implementation based on prime number theory (Time taken 2-3s)
bool checkNumberBetter(int number);

//Threading implementation (Time taken 1-2s)
bool checkNumberWithThreads(int number, int threadcount);

int main()
{
    //Establish data boundaries.
	int prime = 2147483647;
	int testcase = 256;
	bool proof = checkNumberWithThreads(prime, testcase);

	if (proof)
	{
		std::cout << "Number is prime";
	}
	
	else
	{
		std::cout << "Number is fucking weak";
	}
}

bool checkNumber(int number)
{
	for (int i = 2; i < number - 1; i++)
	{
		if (number % i == 0)
		{
			return false;
		}
	}

	return true;
}

bool checkNumberBetter(int number)
{
	//If no number until x / 2 divides the number perfectly, no other number will
	for (int i = 2; i < number / 2; i++)
	{
		if (number % i == 0)
		{
			return false;
		}
	}
	return true;
}


bool checkNumberWithThreads(int number, int threadcount)
{
	//List of all threads present
	PrimeTracker threadList;

	int divisionSize = number / threadcount;
	for(int i = 0; i < threadcount; i++)
	{
		//This is here because lowerbound must not be 1 or 0
		if(i == 0)
		{
			PrimeChecker* checker = new PrimeChecker(i, number, (divisionSize * (i + 1)) - 1, 2);
			threadList.push_back(checker);
			checker->start();
		}
		
		else {
			PrimeChecker* checker = new PrimeChecker(i, number, (divisionSize * (i + 1)) - 1, divisionSize * i);
			threadList.push_back(checker);
			checker->start();
		}
	}

	/*
	int halfpoint = number / 2; //Data cast here yeets the decimal
	int quarterpoint = halfpoint / 2;
	
	//The first thread will handle all numbers up to the halfpoint of the halfpoint
	PrimeChecker* checker1 = new PrimeChecker(1, number, quarterpoint, 2);
	threadList.push_back(checker1);
	
	//The second thread will handle all number after the halfpoint up to the halfpoint
	PrimeChecker* checker2 = new PrimeChecker(2, number, halfpoint, quarterpoint);
	threadList.push_back(checker2);
	
	//start both threads
	checker1->start();
	checker2->start();
	*/

	
	bool checking = true;
	while(checking)
	{
		checking = false;

		
		for (PrimeChecker* primechecker : threadList)
		{
			//If any thread is still checking
			if(primechecker->getState())
			{
				//Continue the loop
				checking = true;
			}
		}
	}

	for (PrimeChecker* primechecker : threadList)
	{
		//If any thread is still checking
		if (!primechecker->Result())
		{
			return false;
		}
	}

	return true;
}
