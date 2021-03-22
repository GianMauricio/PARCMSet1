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
 * 8192 =
 */

//Using Intel Core i7-4790 CPU
/*
 * 2 = 5.067/ 4.890 / 4.732
 * 4 = 3.308 / 3.231 / 3.385
 * 8 =  2.637 / 2.682 / 2.896
 * 16 = 2.477 / 2.627/ 2.457
 * 32 = 2.474 / 2.395 / 2.582
 * 64 = 2.254 / 2.543 / 2.36	88% at peak
 * 128 = 2.530 / 2.476 / 2.542  69% at peak
 * 256 = 2.424 / 2.563 / 2.437 //There are test cases here where its less than a second 
 * 512 = 1.065 / 2.476 / 2.520
 * 1024 = 2.508 / 1.872 / 2.542
 * 2048 =  3.600 / 3.71 / 3.35
 * 4096 =  4.142 / 3.900 / 4.669
 * 8192 =  6.642 / 7.230 / 6.538 
 */

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
	for (int i = 2; i < number / 2 ; i++)
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
