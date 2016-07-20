#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;

double *vector1 = {2.00, 4.00};
double *vector2 = {4.00, 2.00};



double DotProduct(double* vector1, double* vector2)
{
	if (sizeof(vector1) == sizeof(vector2)) //hack
	{
		double sum = 0.00;
		for (int i = 0; i < sizeof(vector1) / sizeof(double); i++)
		{
			sum += sqrt(pow(vector1[i], 2) + pow(vector2[i], 2));
		}

		cout << "DotProduct: " << sum << endl;
		return sum;
	}

	return 0.00;
}

int main () {	
	{
		double start = omp_get_wtime();

		double dotProd = DotProduct(double* vector1, double* vector2);
		
		double end = omp_get_wtime(); 
		double diff = end - start;
		cout << diff << endl;
	}
	return 0;
}