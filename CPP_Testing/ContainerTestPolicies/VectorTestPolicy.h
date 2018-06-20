#include <vector>
#include <chrono>
#include <random>
#include <limits>
#include "DataHelper.h"

using namespace std;
using namespace std::chrono;



struct VectorTestPolicy {

	vector<int> values_;
	DataHelper data_;
	
	static string get_typename() {
		return "Vector";
	}
	
	void AddNextValue(const int& val) {
		values_.push_back(val);
	}
	
	void TestMiddleInsertion(int& value, int index) {
		data_.start_ = high_resolution_clock::now();
		values_.insert(values_.begin() + index, value);
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.middle_insertion_times_nanos_.push_back(data_.exec_time_.count());
		values_.erase(values_.begin() + index);
	}
	
	void TestFrontInsertion(int& value) {
		data_.start_ = high_resolution_clock::now();
		values_.insert(values_.begin(), value);
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.front_insertion_times_nanos_.push_back(data_.exec_time_.count());
		values_.erase(values_.begin());
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
		for(int i = 0; i < values_.size(); i++) {
			if(values_[i] == a){
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
		for(int i = 0; i < values_.size(); i++) {
			if(values_[i] == a){
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
		for(int i = 0; i < values_.size(); i++) {
			if(values_[i] == a){
				break;
			}
		}
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
		values_.erase(values_.begin());
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.front_remove_times_nanos_.push_back(data_.exec_time_.count());
		values_.insert(values_.begin(), a);
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
		vector<int> copy_vector_(values_);
		data_.start_ = high_resolution_clock::now();
		copy_vector_.clear();
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.clear_times_nanos_.push_back(data_.exec_time_.count());
	}
	
	void TestFindSmallest() {
		int smallest = numeric_limits<int>::max();
		data_.start_ = high_resolution_clock::now();
		//we will have to check every value since it is unordered.
		for(int i = 0; i < values_.size(); i++) {
			if(values_[i] < smallest) smallest = values_[i];
		}
		data_.end_ = high_resolution_clock::now();
		data_.exec_time_ = duration_cast<nanoseconds>(data_.end_-data_.start_);
		data_.find_smallest_times_nanos_.push_back(data_.exec_time_.count());
	}
	
};