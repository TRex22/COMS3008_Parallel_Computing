#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;

//constants
const int row = 20;
const int col = 20;
const double Min = 0.00;
const double Max = 100.00;

//http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
//taken from a library Im writing
double RandomDouble (double min, double max)
{
	random_device rd;     // only used once to initialise (seed) engine
	mt19937_64 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	uniform_real_distribution<double> uni(min, max); // guaranteed unbiased
	double random_integer = uni(rng);
	return random_integer;
}

void PrintMatrix (double pmatrix[row][col])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			std::cout << pmatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void row_dominant(double (&mat)[row][col]){
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mat[i][j] = RandomDouble(Min, Max);
		}
	}
	//return mat;
}

void col_dominant(double (&mat[row][col]){
	for (int j = 0; j < col; j++)
	{
		for (int i = 0; i < row; i++)
		{
			mat[i][j] = RandomDouble(Min, Max);
		}
	}
	//return mat;
}

int main () 
{	
	double start = omp_get_wtime();
	
	double matrix[row][col] = new double[row][col];
	row_dominant(matrix);

	matrix = new double[row][col];
	col_dominant(matrix);

	PrintMatrix(matrix);

	double end = omp_get_wtime(); 
	double diff = end - start;
	cout << diff << endl;
	
	return 0;
}