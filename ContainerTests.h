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


template <typename ContainerTestPolicy, typename ValuePopulationPolicy, int array_size>
struct ContainerTest {
	vector<int> value_vector_;
	ContainerTestPolicy container_policy_;
	
	ContainerTest()
	{
		srand(time(0));
		PopulateValues();
	}
	
	void PopulateValues() {
		ValuePopulationPolicy::Populate(value_vector_, array_size);
	}
	
	void TestContainer() {
		container_policy_.Test(value_vector_);
	}
	
	
};
