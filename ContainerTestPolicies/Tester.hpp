#include <vector>

struct Tester {

	//insertion
	vector<int> insertion_times_nanos;
	
	//access
	vector<int> front_access_times_nanos;
	vector<int> back_access_times_nanos;
	vector<int> random_access_times_nanos;

	virtual TestRandomAccess(int index) = 0;
	virtual TestFrontAccess(int index) = 0;
	virtual TestBackAccess(int index) = 0;
};