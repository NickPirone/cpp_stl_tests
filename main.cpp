#include "ContainerTests.h"
#include "ContainerTestPolicies/ListTestPolicy.h"
#include "ContainerTestPolicies/VectorTestPolicy.h"
#include "ContainerTestPolicies/SetTestPolicy.h"
#include "ValuePopulationPolicies/RandomDistributionPolicy.h"
#include <list>
#include <iostream>

/*
	style conventions:
	PascalCase							Typename
	camelCase							none
	lowercase_with_underscores			variables/function arguments
	lowercase_with_trail_				member variable.
*/



int main()
{
	const int total_count = 500;
	ContainerTest<VectorTestPolicy, RandomDistributionPolicy<100000>, total_count> ct1;
	ContainerTest<ListTestPolicy, RandomDistributionPolicy<100000>, total_count> ct2;
	ContainerTest<SetTestPolicy, RandomDistributionPolicy<100000>, total_count> ct3;
	ct1.TestContainer();
	ct2.TestContainer();
	ct3.TestContainer();
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