#include "container_tests.hpp"
#include "list_test.hpp"
#include <list>
#include <iostream>

int main()
{
	const int total_count = 500;
	container_test<list_test<total_count>, total_count> ct;
	ct.populate_random_values(total_count);
	ct.test_inserts();
  	return 0;
}





/*
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

int main ()
{
  using namespace std::chrono;

  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  std::cout << "printing out 1000 stars...\n";
  for (int i=0; i<1000; ++i) std::cout << "*";
  std::cout << std::endl;

  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

  std::cout << "It took me " << time_span.count() << " seconds.";
  std::cout << std::endl;

  return 0;
}
*/