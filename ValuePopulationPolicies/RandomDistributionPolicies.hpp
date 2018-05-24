#include <random>
#include <vector>


struct RandomWideDistribution {

	static void Populate(vector<int>& values, int arr_size){
		for(int i = 0; i < arr_size; i ++) {
			values.push_back( rand() % 1000000 ); //chooses a number between one and a million.
		}
	}

};


struct RandomTightDistribution {

	static void Populate(vector<int>& values, int arr_size) {
		for(int i = 0; i < arr_size; i++) {
			values.push_back( rand() % 10 );
		}
	}
	
};


struct RandomDistribution {
	
	static void Populate(vector<int>& values, int arr_size) {
		for(int i = 0; i < arr_size; i++) {
			values.push_back( rand() % 1000 );
		}
	}
	
};
