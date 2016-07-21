/*
Jason Chalom 711985 2016
Use: g++ -fopenmp -std=c++11 AccessingMultiDimensionalArrays.cpp -o example1.out
*/

#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;

//constants
const int row = 1000;
const int col = 1000;
const double Min = 0.00;
const double Max = 100.00;
const bool PrintArray = false;

//modified from an answer posted:
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

void PrintMatrix (double **pmatrix)
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

void row_dominant(double (&mat)[row][col])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mat[i][j] = RandomDouble(Min, Max);
		}
	}
}

void col_dominant(double (&mat)[row][col])
{
	for (int j = 0; j < col; j++)
	{
		for (int i = 0; i < row; i++)
		{
			mat[i][j] = RandomDouble(Min, Max);
		}
	}
}

void row_dominant(double **mat)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mat[i][j] = RandomDouble(Min, Max);
		}
	}
}

void col_dominant(double **mat)
{
	for (int j = 0; j < col; j++)
	{
		for (int i = 0; i < row; i++)
		{
			mat[i][j] = RandomDouble(Min, Max);
		}
	}
}

//using a matrix dynamically allocated
void dynamic_array()
{
	double matrix[row][col];

	double start_row = omp_get_wtime();
	row_dominant(matrix);
	double end_row = omp_get_wtime(); 
	double diff_row = end_row - start_row;
	cout << "row_dominant execution time: " << diff_row << endl;

	double start_col = omp_get_wtime();
	col_dominant(matrix);
	double end_col = omp_get_wtime(); 
	double diff_col = end_col - start_col;
	cout << "col_dominant execution time: " << diff_col << endl;

	if(PrintArray)
	{
		PrintMatrix(matrix);
	}	
}

void pointer_array()
{
	double** matrix = new double*[row];
	for(int i = 0; i < row; i++)
	{
		matrix[i] = new double[col];
	}

	double start_row = omp_get_wtime();
	row_dominant(matrix);
	double end_row = omp_get_wtime(); 
	double diff_row = end_row - start_row;
	cout << "row_dominant execution time: " << diff_row << endl;

	double start_col = omp_get_wtime();
	col_dominant(matrix);
	double end_col = omp_get_wtime(); 
	double diff_col = end_col - start_col;
	cout << "col_dominant execution time: " << diff_col << endl;

	if(PrintArray)
	{
		PrintMatrix(matrix);
	}	
}

int main () 
{	
	double start = omp_get_wtime();
	
	cout << "Test Array: " << row << "X" << col << endl;
	cout << "dynamic_array: " << endl;
	dynamic_array();
	cout << "\npointer_array: " << endl;
	pointer_array();

	double end = omp_get_wtime(); 
	double diff = end - start;
	cout << "main execution time: " << diff << endl;
	
	return 0;
}