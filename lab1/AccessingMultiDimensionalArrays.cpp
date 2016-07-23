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
int row = 100;
int col = 100;

const double Min = 0.00;
const double Max = 100.00;
const bool PrintArray = false;
const int experimentNumber = 10000;

//file outputs
const char* row_dynamic_file = "results/Example1_row_dynamic.txt";
const char* col_dynamic_file = "results/Example1_col_dynamic.txt";
const char* row_static_file = "results/Example1_row_static.txt";
const char* col_static_file = "results/Example1_col_static.txt";

template <size_t r, size_t c>
void PrintMatrix (double (&pmatrix)[r][c])
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

template <size_t r, size_t c>
void row_dominant(double (&mat)[r][c])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mat[i][j] = rand()*(Max-Min)+Min;
		}
	}
}

template <size_t r, size_t c>
void col_dominant(double (&mat)[r][c])
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
void dynamic_array(char* dimensions)
{
	/*//it is statically allocated a beginning of program and destroyed at end of program
	double matrix[row][col];

	//row
	double start_row = omp_get_wtime();
	row_dominant(matrix);
	double end_row = omp_get_wtime(); 
	double diff_row = end_row - start_row;
	//write to file
	cout << "row_dominant execution time: " << diff_row << endl;
	char r_out[255] = "row_dominant execution time: ";
	sprintf(r_out, "%s %f", r_out, diff_row);
	FileWriter(r_out, row_dynamic_file);

	//col
	double start_col = omp_get_wtime();
	col_dominant(matrix);
	double end_col = omp_get_wtime(); 
	double diff_col = end_col - start_col;
	//write to file
	cout << "col_dominant execution time: " << diff_col << endl;
	char c_out[255] = "col_dominant execution time: ";
	sprintf(c_out, "%s %f", c_out, diff_col);
	FileWriter(c_out, col_dynamic_file);

	if(PrintArray)
	{
		PrintMatrix(matrix);
	}	*/
}

void pointer_array(char* dimensions)
{
	double** matrix = new double*[row];
	for(int i = 0; i < row; i++)
	{
		matrix[i] = new double[col];
	}

	//row
	double start_row = omp_get_wtime();
	row_dominant(matrix);
	double end_row = omp_get_wtime(); 
	double diff_row = end_row - start_row;
	//write to file
	cout << "row_dominant execution time: " << diff_row << endl;
	char r_out[255] = "row_dominant execution time: ";
	sprintf(r_out, "%s %f", r_out, diff_row);
	FileWriter(r_out, row_static_file);

	//col
	double start_col = omp_get_wtime();
	col_dominant(matrix);
	double end_col = omp_get_wtime(); 
	double diff_col = end_col - start_col;
	//write to file
	cout << "col_dominant execution time: " << diff_col << endl;
	char c_out[255] = "col_dominant execution time: ";
	sprintf(c_out, "%s %f", c_out, diff_col);
	FileWriter(c_out, col_static_file);

	if(PrintArray)
	{
		PrintMatrix(matrix);
	}	
	free(matrix);
}

void initFileOuts()
{
	char row_d[255] = "row_dynamic_file";
	FileWriter(row_d, row_dynamic_file);
	char col_d[255] = "col_dynamic_file";
	FileWriter(col_d, col_dynamic_file);

	char row_s[255] = "row_static_file";
	FileWriter(row_s, row_static_file);
	char col_s[255] = "col_static_file";
	FileWriter(col_s, col_static_file);
}

int main () 
{	
	//seed rnd
	srand(time(NULL));
	initFileOuts();

	double start_main = omp_get_wtime();

	char dimensions[255] = "";	

	for (int i = 0; i < experimentNumber; i++)
	{
		sprintf(dimensions, "%d X %d: ", row, col);

		double start = omp_get_wtime();
	
		cout << "Test Array: " << row << " X " << col << endl;
		cout << "dynamic_array: " << endl;
		dynamic_array(dimensions);
		cout << "\npointer_array: " << endl;
		pointer_array(dimensions);

		double end = omp_get_wtime(); 
		double diff = end - start;

		row = 100 + (i*10);
		col = 100 + (i*10);
	}

	double end_main = omp_get_wtime(); 
	double diff_main = end_main - start_main;
	cout << "main execution time: " << diff_main << endl;
	
	return 0;
}