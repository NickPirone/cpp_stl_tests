#include <list>
#include <array>
#include <chrono>

using namespace std;
using namespace std::chrono;

template<int ArraySize>
struct list_test {
	list<int> value_list;
	
	void test_insertions_impl(const array<int, ArraySize>& values) {
		for(int i = 0; i < ArraySize; i++) {
			high_resolution_clock::time_point start = high_resolution_clock::now();
			value_list.push_back(values[i]);
			high_resolution_clock::time_point end = high_resolution_clock::now();
			duration<double> exectime = duration_cast<duration<double> >(start - end);
			cout << "It took me " << exectime.count() << " seconds." << endl;
		}
	}

};