#include <vector>
#include <chrono>
#include <random>
#include <limits>
#include "TestPolicyBase.h"

using namespace std;
using namespace std::chrono;



struct VectorTestPolicy : TestPolicyBase {

	vector<int> values_;
	
	static string get_typename() {
		return "Vector";
	}
	
	void AddNextValue(const int& val) {
		values_.push_back(val);
	}
	
	void TestMiddleInsertion(int& value, int index) {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.insert(values_.begin() + index, value);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		middle_insertion_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.erase(values_.begin() + index);
	}
	
	void TestFrontInsertion(int& value) {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		values_.insert(values_.begin(), value);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_insertion_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.erase(values_.begin());
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
		for(int i = 0; i < values_.size(); i++) {
			if(values_[i] == a){
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
		for(int i = 0; i < values_.size(); i++) {
			if(values_[i] == a){
				break;
			}
		}
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_search_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestBackSearch() {
		//because list does not have a search function, we should test a linear search.
		//this is obviously luck of the draw since we are sampling the last element and looking for it
		//from the 0-index, however for different distributions we will see interesting results.
		//e.g. in a tight distributions where we have many repetitions and just need the first one, it is
		//possible we may see marginal performance decrease.
		int a = values_.back();
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		for(int i = 0; i < values_.size(); i++) {
			if(values_[i] == a){
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
		auto temp_iter = values_.begin();
		advance(temp_iter, index);
		int a = *temp_iter; //get temporary value before timing.
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
		values_.erase(values_.begin());
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_remove_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		values_.insert(values_.begin(), a);
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
		vector<int> copy_vector_(values_);
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		copy_vector_.clear();
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
		for(int i = 0; i < values_.size(); i++) {
			if(values_[i] < smallest) smallest = values_[i];
		}
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		find_smallest_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
};