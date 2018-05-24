#include <list>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;


struct ListTest {
	list<int> value_list;
	
	void Test(const vector<int>& values) {
		for(int i = 0; i < values.size(); i++) {
			high_resolution_clock::time_point start = high_resolution_clock::now();
			value_list.push_back(values[i]);
			high_resolution_clock::time_point end = high_resolution_clock::now();
			duration<double> exectime = duration_cast<duration<double> >(start - end);
			cout << "It took me " << exectime.count() << " seconds." << endl;
		}
	}
	
	
	

};