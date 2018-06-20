#include <deque>
#include <chrono>
#include <random>
#include <limits>
#include "DataHelper.h"

using namespace std;
using namespace std::chrono;



struct DequeTestPolicy {

	deque<int> values_;
	DataHelper data_;
	
	static string get_typename() {
		return "Deque";
	}
	
	void AddNextValue(const int& val) {
		values_.push_back(val);
	}
	
	void TestMiddleInsertion(int& value, int index) {
		data_.start_ = high_resolution_clock::now();
		auto iter = values_.begin();
		advance(iter, index);
		auto remove_iter = values_.insert(iter, value);
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.middle_insertion_times_nanos_.push_back(data_.exec_time_.count());
		values_.erase(remove_iter);
	}
	
	void TestFrontInsertion(int& value) {
		data_.start_ = high_resolution_clock::now();
		values_.push_front(value);
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.front_insertion_times_nanos_.push_back(data_.exec_time_.count());
		values_.pop_front();
	}
	
	void TestBackInsertion(int& value) {
		data_.start_ = high_resolution_clock::now();
		values_.push_back(value);
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.back_insertion_times_nanos_.push_back(data_.exec_time_.count());
		values_.pop_back();
	}
	
	void TestMiddleAccess(int index) {
		data_.start_ = high_resolution_clock::now();
		int a = values_[index];
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.middle_access_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestFrontAccess() {
		data_.start_ = high_resolution_clock::now();
		int a = values_.front();
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.front_access_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestBackAccess() {
		data_.start_ = high_resolution_clock::now();
		int a = values_.back();
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.back_access_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestMiddleSearch(int index) {
		int a = values_[index];
		data_.start_ = high_resolution_clock::now();
		for(auto iter = values_.begin(); iter != values_.end(); iter++) {
			if(*iter == a){
				break;
			}
		}
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.middle_search_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestFrontSearch() {
		int a = values_.front();
		data_.start_ = high_resolution_clock::now();
		for(auto iter = values_.begin(); iter != values_.end(); iter++) {
			if(*iter == a){
				break;
			}
		}
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.front_search_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestBackSearch() {
		int a = values_.back();
		data_.start_ = high_resolution_clock::now();
		for(auto iter = values_.begin(); iter != values_.end(); iter++) {
			if(*iter == a){
				break;
			}
		}
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.back_search_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	//removal
	void TestMiddleRemoval(int index) {
		int a = values_[index]; //get temporary value before timing.
		data_.start_ = high_resolution_clock::now();
		auto iter = values_.begin();
		advance(iter, index);
		auto replace_iter = values_.erase(iter);
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.middle_remove_times_nanos_.push_back(data_.exec_time_.count());
		values_.insert(replace_iter, a);
	}
	
	void TestFrontRemoval() {
		int a = values_.front();
		data_.start_ = high_resolution_clock::now();
		values_.pop_front();
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.front_remove_times_nanos_.push_back(data_.exec_time_.count());
		values_.push_front(a);
	}
	
	void TestBackRemoval() {
		int a = values_.back();
		data_.start_ = high_resolution_clock::now();
		values_.pop_back();
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.back_remove_times_nanos_.push_back(data_.exec_time_.count());
		values_.push_back(a);
	}
	
	//size_query
	void TestSizeQuery() {
		data_.start_ = high_resolution_clock::now();
		int a = values_.size();
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.size_query_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	//clearing
	void TestClearing() {
		deque<int> copy_list_(values_);
		data_.start_ = high_resolution_clock::now();
		copy_list_.clear();
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.clear_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestFindSmallest() {
		int smallest = numeric_limits<int>::max();
		data_.start_ = high_resolution_clock::now();
		//we will have to check every value since it is unordered.
		for(auto iter = values_.begin(); iter != values_.end(); iter++) {
			if(*iter < smallest) smallest = *iter;
		}
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.find_smallest_times_nanos_.push_back(data_.exec_time_.count());
	}

};