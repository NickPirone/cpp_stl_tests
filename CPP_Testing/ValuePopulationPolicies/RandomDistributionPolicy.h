#include <random>
#include <vector>
#include <string>

using namespace std;

template<int max_value>
struct RandomDistributionPolicy {

	static string get_typename() {
		return "Random0to" + to_string(max_value);
	}
	
	static void Populate(vector<int>& values, int arr_size) {
		for(int i = 0; i < arr_size; i++) {
			values.push_back( rand() % 1000 );
		}
	}
	
};
