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
#include <vector>


using namespace std;


template <typename ContainerTestPolicy, typename ValuePopulationPolicy, int ArraySize>
struct container_test {
	vector<int> value_vector;
	ContainerTestPolicy container_policy;
	
	container_test()
	{
		srand(time(0));
		populate();
	}
	
	void populate() {
		ValuePopulationPolicy::Populate(value_vector, ArraySize);
	}
	
	void test_container() {
		container_policy.Test(value_vector);
	}
	
	
};
