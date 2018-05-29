#include <list>
#include <vector>
#include <chrono>
#include "Tester.h"

using namespace std;
using namespace std::chrono;


/*
		okay so here's the idea:  we can time everything--insertions, accesses, etc, but if we want these times as a function of n (number of members), then we need to do each test after each insertion.
		
		we should probably think of a POD structure to keep track of all of these.

*/


struct ListTest : Tester {

	list<int> value_list_;
	
	void Test(const vector<int>& values) {
		for(int i = 0; i < values.size(); i++) {
			high_resolution_clock::time_point start = high_resolution_clock::now();
			value_list_.push_back(values[i]);
			high_resolution_clock::time_point end = high_resolution_clock::now();
			nanoseconds exectime = duration_cast<nanoseconds>(end - start);
			insertion_times_nanos_.push_back(exectime.count());
			TestFrontAccess();
			TestBackAccess();
			TestFrontSearch();
			TestBackSearch();
			TestFrontRemoval();
			TestBackRemoval();
			TestSizeQuery();
			TestClearing();
			//cout << "It took me " << exectime.count() << " nanoseconds." << endl;
		}
		for(int& num : clear_times_nanos_) {
			cout << num << endl;
		}
	}
	
	void TestMiddleAccess(int index) {
		//because the write to register will be the same no matter N, we can still get a good comparison.
		/*
		high_resolution_clock::time_point start = high_resolution_clock::now();
		auto iter = value_list_.begin();
		advance(iter, index);
		int a = *iter;
		high_resolution_clock::time_point end = high_resolution_clock::now();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		middle_access_times_nanos_.push_back(exectime.count());
		*/
	}
	
	void TestFrontAccess() {
		high_resolution_clock::time_point start = high_resolution_clock::now();
		int a = value_list_.front();
		high_resolution_clock::time_point end = high_resolution_clock::now();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		front_access_times_nanos_.push_back(exectime.count());
	}
	
	void TestBackAccess() {
		high_resolution_clock::time_point start = high_resolution_clock::now();
		int a = value_list_.back();
		high_resolution_clock::time_point end = high_resolution_clock::now();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		back_access_times_nanos_.push_back(exectime.count());
	}
	
	void TestMiddleSearch(int index) {
		/*
		auto iter_one = value_list_.begin();
		advance(iter_one, index);
		int a = *iter_one;
		high_resolution_clock::time_point start = high_resolution_clock::now();
		for(auto iter = value_list_.begin(); iter != value_list_.end(); iter++) {
			if(*iter == a){
				break;
			}
		}
		high_resolution_clock::time_point end = high_resolution_clock::now();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		middle_search_times_nanos_.push_back(exectime.count());
		*/
	}
	
	void TestFrontSearch() {
		int a = value_list_.front();
		high_resolution_clock::time_point start = high_resolution_clock::now();
		for(auto iter = value_list_.begin(); iter != value_list_.end(); iter++) {
			if(*iter == a){
				break;
			}
		}
		high_resolution_clock::time_point end = high_resolution_clock::now();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		front_search_times_nanos_.push_back(exectime.count());
	}
	
	void TestBackSearch() {
		int a = value_list_.back();
		high_resolution_clock::time_point start = high_resolution_clock::now();
		for(auto iter = value_list_.end(); iter != value_list_.begin(); iter--) {
			if(*iter == a){
				break;
			}
		}
		high_resolution_clock::time_point end = high_resolution_clock::now();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		back_search_times_nanos_.push_back(exectime.count());
	}
	
	//removal
	void TestMiddleRemoval(int index) {
		//no middle for list.
	}
	
	void TestFrontRemoval() {
		int a = value_list_.front();
		high_resolution_clock::time_point start = high_resolution_clock::now();
		value_list_.pop_front();
		high_resolution_clock::time_point end = high_resolution_clock::now();
		value_list_.push_front(a);
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		front_remove_times_nanos_.push_back(exectime.count());
	}
	
	void TestBackRemoval() {
		int a = value_list_.back();
		high_resolution_clock::time_point start = high_resolution_clock::now();
		value_list_.pop_back();
		high_resolution_clock::time_point end = high_resolution_clock::now();
		value_list_.push_back(a);
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		back_remove_times_nanos_.push_back(exectime.count());
	}
	
	//size_query
	void TestSizeQuery() {
		high_resolution_clock::time_point start = high_resolution_clock::now();
		int a = value_list_.size();
		high_resolution_clock::time_point end = high_resolution_clock::now();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		size_query_times_nanos_.push_back(exectime.count());
	}
	
	//clearing
	void TestClearing() {
		list<int> copy_list_(value_list_);
		high_resolution_clock::time_point start = high_resolution_clock::now();
		copy_list_.clear();
		high_resolution_clock::time_point end = high_resolution_clock::now();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		clear_times_nanos_.push_back(exectime.count());
	}
	

};