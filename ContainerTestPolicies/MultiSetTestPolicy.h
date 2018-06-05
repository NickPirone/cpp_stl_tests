#include <set>
#include <chrono>
#include <random>
#include <limits>
#include "TestPolicyBase.h"

using namespace std;
using namespace std::chrono;



struct MultiSetTestPolicy : TestPolicyBase {

	multiset<int> values_;
	
	static string get_typename() {
		return "MultiSet";
	}
	
	void AddNextValue(const int& val) {
		values_.insert(val);
	}
	
	void TestMiddleInsertion(int& value, int index) {
		// not applicable:  sets are stored as trees, you cannot specify where to insert.
	}
	
	void TestFrontInsertion(int& value) {
		// not applicable.  same as above
	}
	
	void TestBackInsertion(int& value) {
		//this will be our default test for insertions.
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.insert(value);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		back_insertion_times_nanos_.push_back(exec_time_.count());
		front_insertion_times_nanos_.push_back(exec_time_.count());
		middle_insertion_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.erase(value);
	}
	
	void TestMiddleAccess(int index) {
		//because the write to register will be the same no matter N, we can still get a good comparison.
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		auto iter = values_.begin();
		advance(iter, index);
		int a = *iter;
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		middle_access_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestFrontAccess() {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		int a = *(values_.begin());
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_access_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestBackAccess() {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		int a = *(values_.rbegin());
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		back_access_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestMiddleSearch(int index) {
		auto iter = values_.begin();
		advance(iter, values_.size() / 2);
		int a = *iter;
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.find(a);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		middle_search_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestFrontSearch() {
		int a = *(values_.begin());
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.find(a);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_search_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestBackSearch() {
		int a = *(values_.rbegin());
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.find(a);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		back_search_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	//removal
	void TestMiddleRemoval(int index) {
		auto temp_iter = values_.begin();
		advance(temp_iter, index);
		int a = *temp_iter; //get temporary value before timing.
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.erase(temp_iter);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		middle_remove_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.insert(a);
	}
	
	void TestFrontRemoval() {
		int a = *(values_.begin());
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.erase(values_.begin());
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_remove_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.insert(a);
	}
	
	void TestBackRemoval() {
		auto last_iter = values_.end();
		last_iter--;
		int a = *(last_iter);
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.erase(last_iter);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		back_remove_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.insert(a);
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
		multiset<int> copy_set_(values_);
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		copy_set_.clear();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		clear_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestFindSmallest() {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		int a = *(values_.begin());
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		find_smallest_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
};