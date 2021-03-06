# cpp_stl_tests
testing performance of STL containers scientifically.

This program (in its most basic sense) will:  
a.  generate a bunch of numbers to be inserted into our container.  
b.  insert the numbers one by one, each time taking a sample timing of:
<pre>
	1.  insertion  
	2.  access  
	3.  search  
	4.  removal  
	5.  size querying  
	6.  clearing  
</pre>
c.  write the obtained output to the Output directory. 


To download and run this project on your local machine, please clone the git repository and run the script "compile_and_run.sh".  If you get an access denied error, change the permission on the script file:  using a shell (or terminal), navigate to the folder containing the script and type:

		chmod u+x compile_and_run.sh  
		
this will tell the OS that the script is executable.




Where does this code start?  The entrypoint for this is main.cpp.  This is (as of now) the driving function, however you will see a peculiar data type called something like:

		ContainerTest<ListTestPolicy, RandomDistributionPolicy<100000>, total_count> ct;
		
This project uses a "Policy-Based Design" pattern in order to make it expandable to different use cases.  Here there are 3 policies we control:

		ContainerTestPolicy:  the main testing portion of code.  different one for each stl container.
		ValuePopulationPolicy:  how the numbers we plan on inserting are generated.  e.g. uniform?  random?
		array_size:  max number of elements.

When defining your ContainerTest<> template parameters, you get to choose the policies you want to test, e.g:

		ContainerTest<ListTestPolicy, RandomDistributionPolicy<100000>, 1000> ct1; //default
		ContainerTest<ListTestPolicy, RandomDistributionPolicy<10>, 1000> ct; //only a 0-9 distribution.
		ContainerTest<VectorTestPolicy, RandomDistributionPolicy<100000>, 1000> ct;//vector instead of list.
		ContainerTest<ListTestPolicy, RandomDistributionPolicy<100000>, 500> ct;//only testing up to n=500.
		
		
		
		
As the project grows and generates more contributors who want to test different policies, we will be able to pick and choose which policy to implement in our main.cpp instead of writing all the code out ourselves!

Examples:

		ContainerTestPolicies/ListTestPolicy.h
		ValuePopulationPolicies/RandomDistributionPolicy.h



