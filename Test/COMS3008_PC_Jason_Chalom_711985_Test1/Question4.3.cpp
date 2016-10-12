/*
COMS 3008 PC Test 1
Jason Chalom 711985
Question 4.3
*/

#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include "stdlib.h"

using namespace std;

int main (int argc, char** argv)
{
	double sum = 0.0;

	#pragma omp parallel
	{
		//all work is done in master thread
		#pragma omp master
		{
			//fix the problem by removing master and using #pragma omp parallel for reduction(+:sum)
			for (int i = 0; i < 1000000; i++)
			{
				sum += i;
			}
		}		
	}
	
	cout << sum << endl;
	
	return 0;
}

// this creates balanced work load between the 4 threads.
//The 4 threads are explicitly stated here but for a balanced workload of threads this is unnecessary.
void fixedVersion()
{
	double sum = 0.0;
	omp_set_num_threads(4);
	#pragma omp parallel
	{
		//all work is done in master
		#pragma omp parallel for reduction(+:sum)
		for (int i = 0; i < 1000000; i++)
		{
			sum += i;
		}		
	}
	
	cout << sum << endl;
}
