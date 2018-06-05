#include <list>
/*
#include <vector>
#include <deque>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <stack>
#include <array>
#include <forward_list>
#include <priority_queue>
*/

#include <iostream>
#include <boost/timer/timer.hpp>
#include <random>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>


using namespace std;


template <typename ContainerTestPolicy, typename ValuePopulationPolicy, int array_size>
struct ContainerTest {
	vector<int> base_value_vector_;
	ContainerTestPolicy container_policy_;
	
	ContainerTest()
	{
		srand(time(0));
		PopulateValues();
	}
	
	~ContainerTest() {
		string filePath = "../Output/" + ContainerTestPolicy::get_typename() + "_" + ValuePopulationPolicy::get_typename();
		fstream out_strm(filePath, fstream::out | ios::trunc);
		out_strm << 	"front_insertion, front_access, front_search, front_remove, back_insertion, back_access, back_search, back_remove, middle_insertion, middle_access, middle_search, middle_remove, size_query, clear, find_smallest" << endl;
		bool front_enabled = true;
		bool back_enabled = true;
		bool mid_enabled = true;
		if(container_policy_.front_access_times_nanos_.size() == 0) front_enabled = false;
		if(container_policy_.back_access_times_nanos_.size() == 0) back_enabled = false;
		if(container_policy_.middle_access_times_nanos_.size() == 0) mid_enabled = false;
		for(int i = 0; i < array_size; i++) {
			if(front_enabled) {
				out_strm << container_policy_.front_insertion_times_nanos_[i] << ",";
				out_strm << container_policy_.front_access_times_nanos_[i] << ",";
				out_strm << container_policy_.front_search_times_nanos_[i] << ",";
				out_strm << container_policy_.front_remove_times_nanos_[i] << ",";
			} else out_strm << "0,0,0,";
			if(back_enabled) {
				out_strm << container_policy_.back_insertion_times_nanos_[i] << ",";
				out_strm << container_policy_.back_access_times_nanos_[i] << ",";
				out_strm << container_policy_.back_search_times_nanos_[i] << ",";
				out_strm << container_policy_.back_remove_times_nanos_[i] << ",";
			} else out_strm << "0,0,0,";
			if(mid_enabled) {
				out_strm << container_policy_.middle_insertion_times_nanos_[i] << ",";
				out_strm << container_policy_.middle_access_times_nanos_[i] << ",";
				out_strm << container_policy_.middle_search_times_nanos_[i] << ",";
				out_strm << container_policy_.middle_remove_times_nanos_[i] << ",";
			} else out_strm << "0,0,0,";
			out_strm << container_policy_.size_query_times_nanos_[i] << ",";
			out_strm << container_policy_.clear_times_nanos_[i] << ",";
			out_strm << container_policy_.find_smallest_times_nanos_[i];
			out_strm << endl;
		}
		out_strm.close();
	}
	
	
	void PopulateValues() {
		ValuePopulationPolicy::Populate(base_value_vector_, array_size);
	}
	
	void TestContainer() {
		//container_policy_.Test(base_value_vector_);
		for(int i = 0; i < base_value_vector_.size(); i++) {
			container_policy_.AddNextValue(base_value_vector_[i]);
			int randInt = rand() % 1000000;
			container_policy_.TestMiddleInsertion(randInt, container_policy_.values_.size() / 2);
			container_policy_.TestFrontInsertion(randInt);
			container_policy_.TestBackInsertion(randInt);
			container_policy_.TestMiddleAccess(container_policy_.values_.size() / 2);
			container_policy_.TestFrontAccess();
			container_policy_.TestBackAccess();
			container_policy_.TestMiddleSearch(container_policy_.values_.size() / 2);
			container_policy_.TestFrontSearch();
			container_policy_.TestBackSearch();
			container_policy_.TestMiddleRemoval(container_policy_.values_.size() / 2);
			container_policy_.TestFrontRemoval();
			container_policy_.TestBackRemoval();
			container_policy_.TestSizeQuery();
			container_policy_.TestClearing();
			container_policy_.TestFindSmallest();
		}
	}
	
	
};
