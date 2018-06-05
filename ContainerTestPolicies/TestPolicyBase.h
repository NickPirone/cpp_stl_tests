#pragma once

#include <vector>
#include <chrono>
#include <mutex>

using namespace std;

struct TestPolicyBase {

//Data Members:

	//clocks to save garbage collection:
	chrono::high_resolution_clock::time_point start_;
	chrono::high_resolution_clock::time_point end_;
	chrono::nanoseconds exec_time_;
	mutex clock_mutex_;

	//insertion
	vector<int> back_insertion_times_nanos_;
	vector<int> front_insertion_times_nanos_;
	vector<int> middle_insertion_times_nanos_;
	
	//access
	vector<int> front_access_times_nanos_;
	vector<int> back_access_times_nanos_;
	vector<int> middle_access_times_nanos_;
	
	//search
	vector<int> front_search_times_nanos_;
	vector<int> back_search_times_nanos_;
	vector<int> middle_search_times_nanos_;
	
	//removal
	vector<int> front_remove_times_nanos_;
	vector<int> back_remove_times_nanos_;
	vector<int> middle_remove_times_nanos_;
	
	//size_querying
	vector<int> size_query_times_nanos_;
	
	//clearing
	vector<int> clear_times_nanos_;
	
	//comparison finding
	vector<int> find_smallest_times_nanos_;
	
//Virutal Methods

	//testing inserts, main driver of tests
	virtual void AddNextValue(const int& val) = 0;
	
	//testing insertion:
	virtual void TestMiddleInsertion(int& value, int index) = 0;
	virtual void TestFrontInsertion(int& value) = 0;
	virtual void TestBackInsertion(int& value) = 0;

	//testing access
	virtual void TestMiddleAccess(int index) = 0;
	virtual void TestFrontAccess() = 0;
	virtual void TestBackAccess() = 0;
	
	//search
	virtual void TestMiddleSearch(int index) = 0;
	virtual void TestFrontSearch() = 0;
	virtual void TestBackSearch() = 0;
	
	//removal
	virtual void TestMiddleRemoval(int index) = 0;
	virtual void TestFrontRemoval() = 0;
	virtual void TestBackRemoval() = 0;
	
	//size_query
	virtual void TestSizeQuery() = 0;
	
	//clearing
	virtual void TestClearing() = 0;
	
	//comparison finding
	virtual void TestFindSmallest() = 0;
	
};