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

const int experimentNumber = 1000; //number of times to increment a dimension
const int averageNumber = 50; //number of times to repeat a dimension
const int incrementNumber = 100; //increment size of a dimension
const int maxDimension = 5000; //max square dimension to interate towards.

char newline[1] = "";

//file outputs
const char* row_static_file = "results/Example1_row.txt";
const char* col_static_file = "results/Example1_col.txt";

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
	//cout << "row_dominant execution time: " << diff_row << endl;
	char r_out[255] = "";
	sprintf(r_out, "%s %f", dimensions, diff_row);
	FileWriter(r_out, row_static_file);

	//col
	double start_col = omp_get_wtime();
	col_dominant(matrix);
	double end_col = omp_get_wtime(); 
	double diff_col = end_col - start_col;
	//write to file
	//cout << "col_dominant execution time: " << diff_col << endl;
	char c_out[255] = "";
	sprintf(c_out, "%s %f", dimensions, diff_col);
	FileWriter(c_out, col_static_file);

	if(PrintArray)
	{
		PrintMatrix(matrix);
	}


	for (int i = 0; i < row; i++)
	{
	    delete [] matrix[i];
	}
	delete [] matrix;
}

void initFileOuts()
{
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
	
	cout << "Running Experiment 1 ..." << endl;
	for (int i = 0; row <= maxDimension; i++)
	{
		sprintf(dimensions, "%d: t:", row);

		//cout << "Test Array: " << row << " X " << col << endl;
		//cout << "\npointer_array: " << endl;

		for (int j = 0; j < averageNumber; j++)
		{
			double start = omp_get_wtime();
	
			pointer_array(dimensions);

			double end = omp_get_wtime(); 
			double diff = end - start;
		}
		
		if (i == experimentNumber) //hack incase condition is never met
		{
			break;
		}
		
		FileWriter(newline, row_static_file);
		FileWriter(newline, col_static_file);

		row = 100 + incrementNumber + (i*incrementNumber);
		col = 100 + incrementNumber + (i*incrementNumber);
	}

	double end_main = omp_get_wtime(); 
	double diff_main = end_main - start_main;
	cout << "main execution time: " << diff_main << endl;

	FileWriter(newline, row_static_file);
	FileWriter(newline, col_static_file);
	FileWriter(newline, row_static_file);
	FileWriter(newline, col_static_file);

	char lineout[255] = "";
	sprintf (lineout, "main execution time: %f", diff_main);
	FileWriter(lineout, row_static_file);
	FileWriter(lineout, col_static_file);
	
	return 0;
}
