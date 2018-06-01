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
			//cout << "It took me " << exec_time_.count() << " nanoseconds." << endl;
		}
	}
	
	void TestMiddleInsertion(int& value, int index) {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		auto iter = value_list_.begin();
		advance(iter, index);
		auto remove_iter = value_list_.insert(iter, value);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		middle_insertion_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		value_list_.erase(remove_iter);
	}
	
	void TestFrontInsertion(int& value) {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		value_list_.push_front(value);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_insertion_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		value_list_.pop_front();
	}
	
	void TestBackInsertion(int& value) {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		value_list_.push_back(value);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		back_insertion_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		value_list_.pop_back();
	}
	
	void TestMiddleAccess(int index) {
		//because the write to register will be the same no matter N, we can still get a good comparison.
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		auto iter = value_list_.begin();
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
		int a = value_list_.front();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_access_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestBackAccess() {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		int a = value_list_.back();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		back_access_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	void TestMiddleSearch(int index) {
		auto iter_one = value_list_.begin();
		advance(iter_one, index);
		int a = *iter_one;
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		for(auto iter = value_list_.begin(); iter != value_list_.end(); iter++) {
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
		int a = value_list_.front();
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		for(auto iter = value_list_.begin(); iter != value_list_.end(); iter++) {
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
		//because list does not have a search function, we should test a linear search.
		//this is obviously luck of the draw since we are sampling the last element and looking for it
		//from the 0-index, however for different distributions we will see interesting results.
		//e.g. in a tight distributions where we have many repetitions and just need the first one, it is
		//possible we may see marginal performance decrease.
		int a = value_list_.back();
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		for(auto iter = value_list_.end(); iter != value_list_.begin(); iter--) {
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
		auto temp_iter = value_list_.begin();
		advance(temp_iter, index);
		int a = *temp_iter; //get temporary value before timing.
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		auto iter = value_list_.begin();
		advance(iter, index);
		auto replace_iter = value_list_.erase(iter);
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		middle_remove_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		value_list_.insert(replace_iter, a);
	}
	
	void TestFrontRemoval() {
		int a = value_list_.front();
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		value_list_.pop_front();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		front_remove_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		value_list_.push_front(a);
	}
	
	void TestBackRemoval() {
		int a = value_list_.back();
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		value_list_.pop_back();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		back_remove_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
		value_list_.push_back(a);
	}
	
	//size_query
	void TestSizeQuery() {
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		int a = value_list_.size();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		size_query_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	
	//clearing
	void TestClearing() {
		list<int> copy_list_(value_list_);
		clock_mutex_.lock();
		start_ = high_resolution_clock::now();
		copy_list_.clear();
		end_ = high_resolution_clock::now();
		exec_time_ = duration_cast<nanoseconds>(end_-start_);
		clear_times_nanos_.push_back(exec_time_.count());
		clock_mutex_.unlock();
	}
	

};