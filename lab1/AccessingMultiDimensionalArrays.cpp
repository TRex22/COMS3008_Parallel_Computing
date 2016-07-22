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

//constants
const int row = 5000;
const int col = 5000;
const double Min = 0.00;
const double Max = 100.00;
const bool PrintArray = false;
const int experimentNumber = 10000;

//file outputs
const char* row_dynamic_file = "Example1_row_dynamic.txt";
const char* col_dynamic_file = "Example1_col_dynamic.txt";
const char* row_static_file = "Example1_row_static.txt";
const char* col_static_file = "Example1_col_static.txt";

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
			mat[i][j] = rand()*(Max-Min)+Min;
		}
	}
}

void col_dominant(double (&mat)[row][col])
{
	for (int j = 0; j < col; j++)
	{
		for (int i = 0; i < row; i++)
		{
			mat[i][j] = rand()*(Max-Min)+Min;
		}
	}
}

void row_dominant(double **mat)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mat[i][j] = rand()*(Max-Min)+Min;
		}
	}
}

void col_dominant(double **mat)
{
	for (int j = 0; j < col; j++)
	{
		for (int i = 0; i < row; i++)
		{
			mat[i][j] = rand()*(Max-Min)+Min;
		}
	}
}

void FileWriter(char* output, const char* file)
{
	ofstream myfile;
  	myfile.open (file, std::ios_base::app);
		myfile << output << "\n";
  	myfile.close();
}

//using a matrix dynamically allocated
void dynamic_array()
{
	//it is statically allocated a beginning of program and destroyed at end of program
	static double matrix[row][col];

	//row
	double start_row = omp_get_wtime();
	row_dominant(matrix);
	double end_row = omp_get_wtime(); 
	double diff_row = end_row - start_row;
	//write to file
	cout << "row_dominant execution time: " << diff_row << endl;
	char r_out[255] = "row_dominant execution time: ";
	sprintf(r_out, "%f", diff_row);
	FileWriter(r_out, row_dynamic_file);

	//col
	double start_col = omp_get_wtime();
	col_dominant(matrix);
	double end_col = omp_get_wtime(); 
	double diff_col = end_col - start_col;
	cout << "col_dominant execution time: " << diff_col << endl;
	char c_out[255] = "col_dominant execution time: ";
	sprintf(c_out, "%f", diff_col);
	FileWriter(c_out, col_dynamic_file);

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

void initFileOuts()
{
	char row_d = "row_dynamic_file";
	FileWriter(row_d, row_dynamic_file);

	char col_d = "col_dynamic_file";
	FileWriter(col_d, col_dynamic_file);
}

int main () 
{	
	//seed rnd
	srand(time(NULL));
	double start = omp_get_wtime();
	
	cout << "Test Array: " << row << " X " << col << endl;
	cout << "dynamic_array: " << endl;
	dynamic_array();
	cout << "\npointer_array: " << endl;
	pointer_array();

	double end = omp_get_wtime(); 
	double diff = end - start;
	cout << "main execution time: " << diff << endl;
	
	return 0;
}