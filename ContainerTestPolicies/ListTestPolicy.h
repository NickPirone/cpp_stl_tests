#include <list>
#include <vector>
#include <chrono>
#include <random>
#include "TestPolicyBase.h"

using namespace std;
using namespace std::chrono;



struct ListTestPolicy : TestPolicyBase {

	list<int> value_list_;
	
	static string get_typename() {
		return "List";
	}
	
	void Test(const vector<int>& values) {
		for(int i = 0; i < values.size(); i++) {
			value_list_.push_back(values[i]);
			int randInt = rand() % 1000000;
			TestMiddleInsertion(randInt, value_list_.size() / 2);
			TestFrontInsertion(randInt);
			TestBackInsertion(randInt);
			TestMiddleAccess(value_list_.size() / 2);
			TestFrontAccess();
			TestBackAccess();
			TestMiddleSearch(value_list_.size() / 2);
			TestFrontSearch();
			TestBackSearch();
			TestMiddleRemoval(value_list_.size() / 2);
			TestFrontRemoval();
			TestBackRemoval();
			TestSizeQuery();
			TestClearing();
			//cout << "It took me " << exectime.count() << " nanoseconds." << endl;
		}
	}
	
	void TestMiddleInsertion(int& value, int index) {
		high_resolution_clock::time_point start = high_resolution_clock::now();
		auto iter = value_list_.begin();
		advance(iter, index);
		auto remove_iter = value_list_.insert(iter, value);
		high_resolution_clock::time_point end = high_resolution_clock::now();
		value_list_.erase(remove_iter);
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		middle_insertion_times_nanos_.push_back(exectime.count());
	}
	
	void TestFrontInsertion(int& value) {
		high_resolution_clock::time_point start = high_resolution_clock::now();
		value_list_.push_front(value);
		high_resolution_clock::time_point end = high_resolution_clock::now();
		value_list_.pop_front();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		front_insertion_times_nanos_.push_back(exectime.count());
	}
	
	void TestBackInsertion(int& value) {
		high_resolution_clock::time_point start = high_resolution_clock::now();
		value_list_.push_back(value);
		high_resolution_clock::time_point end = high_resolution_clock::now();
		value_list_.pop_back();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		back_insertion_times_nanos_.push_back(exectime.count());
	}
	
	void TestMiddleAccess(int index) {
		//because the write to register will be the same no matter N, we can still get a good comparison.
		high_resolution_clock::time_point start = high_resolution_clock::now();
		auto iter = value_list_.begin();
		advance(iter, index);
		int a = *iter;
		high_resolution_clock::time_point end = high_resolution_clock::now();
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		middle_access_times_nanos_.push_back(exectime.count());
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
	}
	
	void TestFrontSearch() {
		//because list does not have a search function, we should test a linear search
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
		//because list does not have a search function, we should test a linear search.
		//this is obviously luck of the draw since we are sampling the last element and looking for it
		//from the 0-index, however for different distributions we will see interesting results.
		//e.g. in a tight distributions where we have many repetitions and just need the first one, it is
		//possible we may see marginal performance decrease.
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
		auto temp_iter = value_list_.begin();
		advance(temp_iter, index);
		int a = *temp_iter; //get temporary value before timing.
		high_resolution_clock::time_point start = high_resolution_clock::now();
		auto iter = value_list_.begin();
		advance(iter, index);
		auto replace_iter = value_list_.erase(iter);
		high_resolution_clock::time_point end = high_resolution_clock::now();
		value_list_.insert(replace_iter, a);
		nanoseconds exectime = duration_cast<nanoseconds>(end-start);
		middle_remove_times_nanos_.push_back(exectime.count());
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