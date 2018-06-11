#include "ContainerTests.h"
#include "ContainerTestPolicies/ListTestPolicy.h"
#include "ContainerTestPolicies/VectorTestPolicy.h"
#include "ContainerTestPolicies/MultiSetTestPolicy.h"
#include "ContainerTestPolicies/UnorderedMultiSetTestPolicy.h"
#include "ContainerTestPolicies/DequeTestPolicy.h"
#include "ValuePopulationPolicies/RandomDistributionPolicy.h"
#include <list>
#include <iostream>
#include <chrono>
#include <thread>

/*
	style conventions:
	PascalCase							Typename
	camelCase							none
	lowercase_with_underscores			variables/function arguments
	lowercase_with_trail_				member variable.
*/
using namespace std::chrono;


int main()
{
	high_resolution_clock::time_point start_ = high_resolution_clock::now();
	const int total_count = 5000;
	ContainerTest<VectorTestPolicy, RandomDistributionPolicy<100000>, total_count> ct1;
	ContainerTest<ListTestPolicy, RandomDistributionPolicy<100000>, total_count> ct2;
	ContainerTest<MultiSetTestPolicy, RandomDistributionPolicy<100000>, total_count> ct3;
	ContainerTest<UnorderedMultiSetTestPolicy, RandomDistributionPolicy<100000>, total_count> ct4;
	ContainerTest<DequeTestPolicy, RandomDistributionPolicy<100000>, total_count> ct5;
	thread t1([&] (ContainerTest<VectorTestPolicy, RandomDistributionPolicy<100000>, total_count>* ct) { ct->TestContainer(); }, &ct1);
	thread t2([&] (ContainerTest<ListTestPolicy, RandomDistributionPolicy<100000>, total_count>* ct) { ct->TestContainer(); }, &ct2);
	thread t3([&] (ContainerTest<MultiSetTestPolicy, RandomDistributionPolicy<100000>, total_count>* ct) { ct->TestContainer(); }, &ct3);
	thread t4([&] (ContainerTest<UnorderedMultiSetTestPolicy, RandomDistributionPolicy<100000>, total_count>* ct) { ct->TestContainer(); }, &ct4);
	thread t5([&] (ContainerTest<DequeTestPolicy, RandomDistributionPolicy<100000>, total_count>* ct) { ct->TestContainer(); }, &ct5);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	high_resolution_clock::time_point end_ = high_resolution_clock::now();
	nanoseconds time = duration_cast<nanoseconds>(end_ - start_);
	std::cout << time.count() << std::endl;
  	return 0;
}

