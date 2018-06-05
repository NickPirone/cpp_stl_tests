#include <deque>
#include <chrono>
#include <random>
#include <limits>
#include "TestPolicyBase.h"

using namespace std;
using namespace std::chrono;



struct DequeTestPolicy : TestPolicyBase {

	deque<int> values_;
	
	static string get_typename() {
		return "Deque";
	}
	
	void AddNextValue(const int& val) {
		values_.push_back(val);
	}
	
	void TestMiddleInsertion(int& value, int index) {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		auto iter = values_.begin();
		advance(iter, index);
		auto remove_iter = values_.insert(iter, value);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		middle_insertion_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.erase(remove_iter);
	}
	
	void TestFrontInsertion(int& value) {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.push_front(value);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_insertion_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.pop_front();
	}
	
	void TestBackInsertion(int& value) {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.push_back(value);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		back_insertion_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.pop_back();
	}
	
	void TestMiddleAccess(int index) {
		//because the write to register will be the same no matter N, we can still get a good comparison.
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		int a = values_[index];
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		middle_access_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestFrontAccess() {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		int a = values_.front();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_access_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestBackAccess() {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		int a = values_.back();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		back_access_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestMiddleSearch(int index) {
		int a = values_[index];
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		for(auto iter = values_.begin(); iter != values_.end(); iter++) {
			if(*iter == a){
				break;
			}
		}
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		middle_search_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestFrontSearch() {
		//because list does not have a search function, we should test a linear search
		int a = values_.front();
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		for(auto iter = values_.begin(); iter != values_.end(); iter++) {
			if(*iter == a){
				break;
			}
		}
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_search_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestBackSearch() {
		int a = values_.back();
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		for(auto iter = values_.begin(); iter != values_.end(); iter++) {
			if(*iter == a){
				break;
			}
		}
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		back_search_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	//removal
	void TestMiddleRemoval(int index) {
		int a = values_[index]; //get temporary value before timing.
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		auto iter = values_.begin();
		advance(iter, index);
		auto replace_iter = values_.erase(iter);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		middle_remove_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.insert(replace_iter, a);
	}
	
	void TestFrontRemoval() {
		int a = values_.front();
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.pop_front();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_remove_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.push_front(a);
	}
	
	void TestBackRemoval() {
		int a = values_.back();
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.pop_back();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		back_remove_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.push_back(a);
	}
	
	//size_query
	void TestSizeQuery() {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		int a = values_.size();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		size_query_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	//clearing
	void TestClearing() {
		deque<int> copy_list_(values_);
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		copy_list_.clear();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		clear_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestFindSmallest() {
		int smallest = numeric_limits<int>::max();
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		//we will have to check every value since it is unordered.
		for(auto iter = values_.begin(); iter != values_.end(); iter++) {
			if(*iter < smallest) smallest = *iter;
		}
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		find_smallest_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}

};