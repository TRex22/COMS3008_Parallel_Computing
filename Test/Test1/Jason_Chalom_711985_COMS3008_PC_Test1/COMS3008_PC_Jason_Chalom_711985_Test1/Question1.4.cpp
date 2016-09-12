/*
COMS 3008 PC Test 1
Jason Chalom 711985
Question 1.4
*/

#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include "stdlib.h"

using namespace std;
//example of a race condition
void makeRaceCondition()
{
	//for loop which adds all numbers from 100 to 1
	int sum = 0;
	//The fix for the race condition would be to add a reduction directive on sum, commented out here
	#pragma omp parallel for //reduction(+:sum)
	for (int i = 0; i < 100; i++)
	{
		//this is where the race condition occurs
		sum += 100-i;
	}
	
	cout << "Sum is equal to: "<< sum << endl;
}

int main (int argc, char** argv)
{
	makeRaceCondition();	
	return 0;
}
