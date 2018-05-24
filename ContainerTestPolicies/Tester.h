#include <vector>

struct Tester {

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
	vector<int> size_query_times_;
	
	//clearing
	vector<int> clear_times_;
	
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