#include <iostream>
#include <thread>
#include <vector>
#include "Thread1.h"
#include "Thread2.h"

void testFunc()
{
	std::cout << "Hello World but threads" << std::endl;
}

void testID(int i)
{
	std::cout << "Hello World but thread ID is: " << i << std::endl;
}

int main()
{
	typedef std::vector<Thread1*> Spool1;
	Spool1 threadList1;
	typedef std::vector<Thread2*> Spool2;
	Spool2 threadList2;
	//C++ is a bitchy language and hates when you don't do things properly
    //std::thread myThread(testFunc);

	//This is the result of such brattiness
	//myThread.join();

	//You can also do this to "force run" a thread but note that this causes RNG to be a factor
	//myThread.detach();

	//Spawn the first thread
	Thread1* thread1 = new Thread1();
	thread1->start();
	threadList1.push_back(thread1);

	//Spawn the second thread
	Thread2* thread2 = new Thread2();
	thread2->start();
	threadList2.push_back(thread2);

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	thread1->scheduleStop();

	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
}