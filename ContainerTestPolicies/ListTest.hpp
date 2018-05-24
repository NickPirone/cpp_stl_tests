#include <list>
#include <vector>
#include <chrono>
#include "Tester.hpp"

using namespace std;
using namespace std::chrono;


/*
		okay so here's the idea:  we can time everything--insertions, accesses, etc, but if we want these times as a function of n (number of members), then we need to do each test after each insertion.
		
		we should probably think of a POD structure to keep track of all of these.

*/


struct ListTest : Tester {

	list<int> value_list;
	
	void Test(const vector<int>& values) {
		for(int i = 0; i < values.size(); i++) {
			high_resolution_clock::time_point start = high_resolution_clock::now();
			value_list.push_back(values[i]);
			high_resolution_clock::time_point end = high_resolution_clock::now();
			nanoseconds exectime = duration_cast<nanoseconds>(end - start);
			insertion_times_nanos.push_back(exectime.count());
			TestFrontAccess();
			TestBackAccess();
			TestRandomAccess(values.size() / 2);
			//cout << "It took me " << exectime.count() << " nanoseconds." << endl;
		}
	}
	
	void TestRandomAccess(int index) {
		//because the write to register will be the same no matter N, we can still get a good comparison.
		high_resolution_clock::time_point start = high_resolution_clock::now();
		auto iter = value_list.begin();
		advance(iter, index);
		int a = *iter;
		high_resolution_clock::time_point end = high_resolution_clock::now();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		random_access_times_nanos.push_back(exectime.count());
	}
	
	void TestFrontAccess() {
		high_resolution_clock::time_point start = high_resolution_clock::now();
		int a = value_list.front();
		high_resolution_clock::time_point end = high_resolution_clock::now();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		front_access_times_nanos.push_back(exectime.count());
	}
	
	void TestBackAccess() {
		high_resolution_clock::time_point start = high_resolution_clock::now();
		int a = value_list.back();
		high_resolution_clock::time_point end = high_resolution_clock::now();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		back_access_times_nanos.push_back(exectime.count());
	}
	
	
	

};