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
const int number_intervals = 1000000;
const int a_ = 5;
const int b_ = 50;

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

//question 3.1 serial
double calcRiemannSum(int m)
{
	//work out the iterval width
	double h = (double)((double)(b_-a_) / m);
	
	double sum = 0.0;
	double x0 = a_;
	double x1 = a_ + h;
	
	for (int i = 0; i < number_intervals; i++)
	{
		sum += (double)(h*(functionx((double)(a_) + h*(i+1)) + functionx((double)(a_) + h*(i))));	
	}
	
	double integral = sum;
	return integral;
}

//question 3.2 parallel - is faster than serial.
double calcParallelRiemannSum(int m)
{
	//work out the iterval width
	double h = (double)((double)(b_-a_) / m);
	
	double sum = 0.0;
	double x0 = a_;
	double x1 = a_ + h;
	
	#pragma omp parallel for reduction(+: sum)
	for (int i = 0; i < number_intervals; i++)
	{
		sum += (double)(functionx((double)(a_) + h*(i+1)) + functionx((double)(a_) + h*(i)));/*(double)(h*(functionx((double)(a_) + h*(i+1)) + functionx((double)(a_) + h*(i))));	*/
	}
	
	double integral = h*sum;
	return integral;
}

int main (int argc, char** argv)
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
