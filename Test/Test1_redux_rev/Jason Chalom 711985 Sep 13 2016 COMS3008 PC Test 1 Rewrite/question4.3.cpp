/*
Jason Chalom 711985
September 13th 2016
PC COMS 3008 test rewrite

compile: g++ -fopenmp question4.3.cpp -o q4.3.out
*/

#include <stdio.h>
#include "omp.h"
#include <cmath>
#include <time.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

void workloadImBalanced() 
{
	double sum = 0;

	#pragma omp parallel 
	{
		#pragma omp master
		{
			for (int i = 0; i < 1000000; i++)
			{				
				sum += i;			
			}
		}
	}

	cout << "sum: " << sum << endl;
}


void workloadBalanced() 
{
	double sum = 0;
	omp_set_num_threads(4);
	#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < 1000000; i++)
	{				
		sum += i;			
	}

	cout << "sum: " << sum << endl;
}

int main()
{
	//This system has 4 cores

	cout << "Looking at work load imbalance. \nThis system needs to have 4 processors\n\n" << endl;
	cout << "An imbalanced workload" << endl;
	double s_start = omp_get_wtime();
	workloadImBalanced();
	double s_end = omp_get_wtime();
	double s_diff = s_end - s_start;
	cout << "Imbalanced workload time taken: " << s_diff << " seconds. (should be slower)" << endl;
	cout << endl;
	
	cout << "A balanced workload" << endl;
	double p_start = omp_get_wtime();
	workloadBalanced();
	double p_end = omp_get_wtime();
	double p_diff = p_end - p_start;
	cout << "Balanced workload time taken: " << p_diff << " seconds." << endl;
	cout << endl;
	

	return 0;
}
