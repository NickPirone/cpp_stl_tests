#include <set>
#include <chrono>
#include <random>
#include <limits>
#include "DataHelper.h"

using namespace std;
using namespace std::chrono;



struct MultiSetTestPolicy {

	multiset<int> values_;
	DataHelper data_;
	
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
		data_.start_ = high_resolution_clock::now();
		values_.insert(value);
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.back_insertion_times_nanos_.push_back(data_.exec_time_.count());
		data_.front_insertion_times_nanos_.push_back(data_.exec_time_.count());
		data_.middle_insertion_times_nanos_.push_back(data_.exec_time_.count());
		values_.erase(value);
	}
	
	void TestMiddleAccess(int index) {
		data_.start_ = high_resolution_clock::now();
		auto iter = values_.begin();
		advance(iter, index);
		int a = *iter;
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.middle_access_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestFrontAccess() {
		data_.start_ = high_resolution_clock::now();
		int a = *(values_.begin());
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.front_access_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestBackAccess() {
		data_.start_ = high_resolution_clock::now();
		int a = *(values_.rbegin());
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.back_access_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestMiddleSearch(int index) {
		auto iter = values_.begin();
		advance(iter, values_.size() / 2);
		int a = *iter;
		data_.start_ = high_resolution_clock::now();
		values_.find(a);
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.middle_search_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestFrontSearch() {
		int a = *(values_.begin());
		data_.start_ = high_resolution_clock::now();
		values_.find(a);
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.front_search_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestBackSearch() {
		int a = *(values_.rbegin());
		data_.start_ = high_resolution_clock::now();
		values_.find(a);
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.back_search_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	//removal
	void TestMiddleRemoval(int index) {
		auto temp_iter = values_.begin();
		advance(temp_iter, index);
		int a = *temp_iter; //get temporary value before timing.
		data_.start_ = high_resolution_clock::now();
		values_.erase(temp_iter);
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.middle_remove_times_nanos_.push_back(data_.exec_time_.count());
		values_.insert(a);
	}
	
	void TestFrontRemoval() {
		int a = *(values_.begin());
		data_.start_ = high_resolution_clock::now();
		values_.erase(values_.begin());
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.front_remove_times_nanos_.push_back(data_.exec_time_.count());
		values_.insert(a);
	}
	
	void TestBackRemoval() {
		auto last_iter = values_.end();
		last_iter--;
		int a = *(last_iter);
		data_.start_ = high_resolution_clock::now();
		values_.erase(last_iter);
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.back_remove_times_nanos_.push_back(data_.exec_time_.count());
		values_.insert(a);
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
		multiset<int> copy_set_(values_);
		data_.start_ = high_resolution_clock::now();
		copy_set_.clear();
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.clear_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestFindSmallest() {
		data_.start_ = high_resolution_clock::now();
		int a = *(values_.begin());
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.find_smallest_times_nanos_.push_back(data_.exec_time_.count());
	}
	
};