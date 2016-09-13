/*
Jason Chalom 711985
September 13th 2016
PC COMS 3008 test rewrite
Question 4.2

compile: g++ -fopenmp question4.2.cpp -o q4.2.out
*/

#include <stdio.h>
#include "omp.h"
#include <cmath>
#include <time.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

void lowConcurrency ()
{
	omp_set_num_threads(1000); //vastly more than the system can do at once
	double sum = 1.0;

	#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < 1000000; i++)
	{
		sum += i;
	}

	cout << "sum: " << sum << endl;
}

void goodConcurrency ()
{
	double sum1 = 1.0;
	double sum2 = 1.0;
	double sum3 = 1.0;
	double sum4 = 1.0;

	int section1Count = 1000000 / 4;
	int section2Count = 1000000 / 2;
	int section3Count = (1000000 * 3) / 4;
	int section4Count = 1000000;
	
	//will use 4 sections which will utilise all 4 of the systems processor units
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			for (int i = 0; i < section1Count; i++)
			{
				sum1 += i;
			}
		}

		#pragma omp section
		{
			for (int i = section1Count; i < section2Count; i++)
			{
				sum2 += i;
			}
		}

		#pragma omp section
		{
			for (int i = section2Count; i < section3Count; i++)
			{
				sum3 += i;
			}
		}

		#pragma omp section
		{
			for (int i = section3Count; i < section4Count; i++)
			{
				sum4 += i;
			}
		}
	}

	//here out of the parallel the 4 sums are added together
	double sum = sum1 + sum2 + sum3 + sum4;

	cout << "sum: " << sum << endl;
}

int main()
{
	//This system has 4 cores

	cout << "Looking at high and good concurreny\nThis system needs to have 4 processors\n\n" << endl;
	cout << "Low Concurrency Should be slower as it has more tasks than there are processors of the system" << endl;
	double s_start = omp_get_wtime();
	lowConcurrency();
	double s_end = omp_get_wtime();
	double s_diff = s_end - s_start;
	cout << "Low Concurrency time taken: " << s_diff << " seconds. (should be slower i.e. larger than the good concurrency)" << endl;
	cout << endl;
	
	cout << "Good Concurrency Should be faster as it uses the 4 processors of the system" << endl;
	double p_start = omp_get_wtime();
	goodConcurrency();
	double p_end = omp_get_wtime();
	double p_diff = p_end - p_start;
	cout << "Good Concurrency time taken: " << p_diff << " seconds." << endl;
	cout << endl;

	return 0;
}
