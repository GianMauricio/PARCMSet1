// ProblemSet1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/// The objective is simple. Using the test case of 2147483647, the highest prime number that fits into an int data type
/// Create a multi-threaded algorithm that proves that it is in fact a prime number.
/// The algorithm must perform faster than a normal program
/// You must also observe an inverted-bell pattern in relation to the number of threads spawned.
///
/// If the patterns don't line up, or are to small to observe, consider switching to the "long" data type and use the insane prime number
/// 2305843009213693951

#include <iostream>
#include "PrimeChecker.h"

//ooga booga implementation (Time taken 4-5s)
bool checkNumber(int number);

//Standard implementation based on prime number theory (Time taken 2-3s)
bool checkNumberBetter(int number);

//Threading implementation (Time taken 1-2s)
bool checkNumberWithThreads(int number);

int main()
{
    //Establish data boundaries.
	int prime = 2147483647;

	bool proof = checkNumberWithThreads(prime);

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

bool checkNumberWithThreads(int number)
{
	int halfpoint = number / 2; //Data cast here yeets the decimal
	int quarterpoint = halfpoint / 2;

	//The first thread will handle all numbers up to the halfpoint of the halfpoint
	PrimeChecker* checker1 = new PrimeChecker(1, number, quarterpoint, 2);

	//The second thread will handle all number after the halfpoint up to the halfpoint
	PrimeChecker* checker2 = new PrimeChecker(2, number, halfpoint, quarterpoint);

	//start both threads
	checker1->start();
	checker2->start();
	
	bool checking = true;
	while(checking)
	{
		//Once both threads are finished...
		if(checker1->getState() == false && checker2->getState() == false)
		{
			//Cease the loop
			checking = false;
		}
	}

	//determine what to send back
	if(checker1->Result() && checker2->Result())
	{
		return true;
	}

	return false;
}