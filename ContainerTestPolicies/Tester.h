#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename TestType>
struct Tester {

//Destructor:  writes all data to CSV format.
	~Tester() {
		string filePath = "Output/" + TestType::get_typename();
		fstream out_strm(filePath, fstream::out | ios::trunc);
		out_strm << 	"insertion, front_access, front_search, front_remove, back_access, back_search, back_remove, middle_access, middle_search, middle_remove, size_query, clear" << endl;
		bool front_enabled = true;
		bool back_enabled = true;
		bool mid_enabled = true;
		if(front_access_times_nanos_.size() == 0) front_enabled = false;
		if(back_access_times_nanos_.size() == 0) back_enabled = false;
		if(middle_access_times_nanos_.size() == 0) mid_enabled = false;
		for(int i = 0; i < insertion_times_nanos_.size(); i++) {
			out_strm << insertion_times_nanos_[i] << ',';
			if(front_enabled) {
				out_strm << front_access_times_nanos_[i] << ",";
				out_strm << front_search_times_nanos_[i] << ",";
				out_strm << front_remove_times_nanos_[i] << ",";
			} else out_strm << "0,0,0,";
			if(back_enabled) {
				out_strm << back_access_times_nanos_[i] << ',';
				out_strm << back_search_times_nanos_[i] << ',';
				out_strm << back_remove_times_nanos_[i] << ',';
			} else out_strm << "0,0,0,";
			if(mid_enabled) {
				out_strm << middle_access_times_nanos_[i] << ',';
				out_strm << middle_search_times_nanos_[i] << ',';
				out_strm << middle_remove_times_nanos_[i] << ',';
			} else out_strm << "0,0,0,";
			out_strm << size_query_times_nanos_[i];
			out_strm << clear_times_nanos_[i];
			out_strm << endl;
		}
		out_strm.close();
	}

//Data Members:
	//insertion
	vector<int> insertion_times_nanos_;
	
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
	
//Virutal Methods

	//testing inserts, main driver of tests
	virtual void Test(const vector<int>& values) = 0;

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
	
};