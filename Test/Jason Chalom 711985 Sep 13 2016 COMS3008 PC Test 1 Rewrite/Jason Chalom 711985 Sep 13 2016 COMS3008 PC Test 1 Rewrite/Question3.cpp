/*
Jason Chalom 711985
September 13th 2016
PC COMS 3008 test rewrite
Question 3

compile: g++ -fopenmp Question3.cpp -o q3.out
*/

#include <stdio.h>
#include "omp.h"
#include <cmath>
#include <time.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

//constants
const double analytical_result = exp(50) - exp(5);
const double a = 5.00;
const double b = 50.00;
const double error_limit = 0.001;
const int number_partitions = 10000000;

const double h = (double)(b - a) / (double)number_partitions;

double functionx (double x)
{
	return exp(x);
}

void calc_error (double integral)
{
	// this is because the div determines how many percent accurate it is rather than how much is wrong with the approximation
	double error = 1 - (abs(integral) / abs(analytical_result));  
	cout << "error is: " << error << endl;
	
	if (error < error_limit)
	{
		cout << "error is below the error limit of: " << error_limit << endl;
	}
	else if (error > error_limit)
	{
		cout << "error is above the error limit of: " << error_limit << endl;
	}
	else
	{
		cout << "error is at the error limit of: " << error_limit << endl;
	}
	
}

//question 3.1
void serial_riemann_sum()
{
	double integral = 0.00;
	for (int i = 0; i < number_partitions; i++)
	{
		integral += functionx((double)(a + ((double)i * h)));
	}
	
	integral = h * integral;
	
	cout << "serial complete. Integral is: " << integral << endl;
	calc_error(integral);
}

//question 3.2
void parallel_riemann_sum()
{
	double integral = 0.00;
	#pragma omp parallel for reduction(+:integral)
	for (int i = 0; i < number_partitions; i++)
	{
		integral += functionx((double)(a + ((double)i * h)));
	}
	
	integral = h * integral;
	
	cout << "serial complete. Integral is: " << integral << endl;
	calc_error(integral);
}

int main()
{
	cout << "Riemann Sum Serial and Parallel" << endl;
	double s_start = omp_get_wtime();
	serial_riemann_sum();
	double s_end = omp_get_wtime();
	double s_diff = s_end - s_start;
	cout << "Total serial time taken: " << s_diff << " seconds." << endl;
	cout << endl;

	double p_start = omp_get_wtime();
	parallel_riemann_sum();
	double p_end = omp_get_wtime();
	double p_diff = p_end - p_start;
	cout << "Total parallel time taken: " << p_diff << " seconds." << endl;
	cout << endl;


	return 0;
}
