/*
COMS 3008 PC Test 1
Jason Chalom 711985
Question 3.1 and 3.2
*/

#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include "stdlib.h"

using namespace std;

//parameter values chosen as consts here to make code more explicit
const double analytical_ans = exp(50) - exp(5);
const double target_error = 0.001;
const int number_intervals = 10000000;
const int a = 5;
const int b = 50;
const double deltax = ((double)b - (double) a)/(number_intervals);

double functionx (double x)
{
	return exp(x);
}

double calcError (double ans)
{
	double difference = analytical_ans - ans;
	double percent = (abs(difference) / analytical_ans) * 100;
	return percent;
}

void checkError (double ans)
{
	double err = calcError(ans);
	if (err < target_error)
	{
		cout << "Error is below target error of 0.001. Error = " << err << endl;
	}
	else
	{
		cout << "Error is above target error of 0.001. Error = " << err << endl;
	}
}

double calcRiemannSum(int n)
{
	double integral = 0.0;
	double sum = 0.0;

	for (int i = 0; i < n; i++)
	{
		sum += functionx(a + (i*deltax));
	}

	integral = (double)(deltax * sum);
	return integral;
}

double calcParallelRiemannSum(int n)
{
	double integral = 0.0;
	double sum = 0.0;

	#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		sum += functionx(a + (i*deltax));
	}

	integral = (double)(deltax * sum);
	return integral;
}

int main() 
{
	cout << "Serial Version:" << endl;
	double start_serial = omp_get_wtime();
	double integration = calcRiemannSum(number_intervals);
	double end_serial = omp_get_wtime();
	cout << "The integration of the function from 5 to 50 is: " << integration << endl;
	checkError(integration);
	double diff_serial = end_serial - start_serial;
	cout<< "Serial Time: " << diff_serial << " seconds." << endl;
	
	cout << "\nParallel Version:" << endl;
	double start_p = omp_get_wtime();
	double integration_parallel = calcParallelRiemannSum(number_intervals);
	double end_p = omp_get_wtime();
	cout << "The integration of the function from 5 to 50 is: " << integration_parallel << endl;
	checkError(integration_parallel);
	double diff_p = end_p - start_p;
	cout<< "Parallel Time: " << diff_p << " seconds." << endl;
		
	return 0;
}