/*
Jason Chalom 711985 2016
Use: g++ -fopenmp AccessingMultiDimensionalArrays.cpp -o example1.out
*/

#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>     
#include <time.h>       
#include <fstream>

using namespace std;

const int row = 2000000;
const double Min = 0.00;
const double Max = 100.00;
const bool PrintArray = false;
const int experimentNumber = 10000;

void PrintMatrix (double *vector)
{
	std::cout << "Vector:" << endl;
	for (int i = 0; i < row; i++)
	{
		std::cout << vector[i] << " ";
		std::cout << std::endl;
	}
}

double* RandomVector()
{
	double *vector = new double[row];

	for(int i = 0; i < row; i++)
	{
		vector[i] = rand()*(Max-Min) + Min;
	}

	return vector;
}

double* ParallelRandomVector()
{
	double *vector = new double[row];

	#pragma omp parallel for
	for(int i = 0; i < row; i++)
	{
		vector[i] = rand()*(Max-Min) + Min;
	}

	return vector;
}

double DotProduct(double *vector1, double *vector2)
{
	if (sizeof(vector1) == sizeof(vector2)) //hack
	{
		double sum = 0.00;
		for (int i = 0; i < row; i++)
		{
			sum += vector1[i]*vector2[i];
		}

		cout << "DotProduct: " << sum << endl;
		return sum;
	}

	return 0.00;
}

double ParallelDotProduct(double *vector1, double *vector2)
{
	if (sizeof(vector1) == sizeof(vector2)) //hack
	{
		double sum = 0.00;

		#pragma omp parallel for
		for (int i = 0; i < row; i++)
		{
			sum += vector1[i]*vector2[i];
		}

		cout << "DotProduct: " << sum << endl;
		return sum;
	}

	return 0.00;
}

void seqential_dot_product()
{
	double start = omp_get_wtime();

	double *vector1 = RandomVector ();		
	double *vector2 = RandomVector ();		

/*	if(PrintArray)
	{
		PrintMatrix (vector1);
		PrintMatrix (vector2);
	}	*/	

	double dotProd = DotProduct(vector1, vector2);
	
	double end = omp_get_wtime(); 
	double diff = end - start;
	cout << diff << endl;
}

void parallel_dot_product()
{
	double start = omp_get_wtime();

	double *vector1 = RandomVector ();		
	double *vector2 = RandomVector ();		

	double dotProd = ParallelDotProduct(vector1, vector2);
	
	double end = omp_get_wtime(); 
	double diff = end - start;
	cout << diff << endl;
}

void parallel_dot_product_rnd()
{
	double start = omp_get_wtime();

	double *vector1 = ParallelRandomVector ();		
	double *vector2 = ParallelRandomVector ();			

	double dotProd = ParallelDotProduct(vector1, vector2);
	
	double end = omp_get_wtime(); 
	double diff = end - start;
	cout << diff << endl;
}

int main () {	
	{
		//seed rnd
		srand(time(NULL));
		seqential_dot_product();
		parallel_dot_product();
		parallel_dot_product_rnd();
	}
	return 0;
}