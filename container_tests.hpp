#include <list>
/*
#include <vector>
#include <deque>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <stack>
#include <array>
#include <forward_list>
#include <priority_queue>
*/

#include <iostream>
#include <boost/timer/timer.hpp>
#include <random>
#include <ctime>
#include <array>
//okay, so what i want to do is run a list through a set of operations and see how fast they are for 1000 vs 10000 inserts.
//i need a timer
using namespace std;


template <typename ContainerTestPolicy, int ArraySize>
struct container_test {
	array<int,ArraySize> value_array;
	ContainerTestPolicy container_policy;
	
	container_test()
	{
		srand(time(0));
	}
	
	void populate_random_values(int highest_value) {
		for(int i = 0; i < ArraySize; i ++) {
			value_array[i] = rand() % highest_value;
		}
	}
	
	void test_inserts() {
		container_policy.test_insertions_impl(value_array);
	}
	
	
};
