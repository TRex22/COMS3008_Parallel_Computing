/*
Jason Chalom 711985
September 13th 2016
PC COMS 3008 test rewrite
Question 1.4

compile: g++ -fopenmp Question1.4.cpp -o q1.4.out
*/

#include <stdio.h>
#include "omp.h"
#include <cmath>
#include <time.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	int sum = 0;
	// this illustrates a race condition where there is no reduction for sum
	// The answers will be inconsistent

	// to fix this add a reduction on the sum variable
  	#pragma omp parallel for //reduction(+:sum)
	for(int i = 0; i < 1000; i++)	
	{
		sum += sum + i;
	}

	cout << sum << endl;

	return 0;
}
