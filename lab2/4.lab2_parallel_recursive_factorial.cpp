/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 4.lab2_parallel_recursive_factorial.cpp -o example4.out
*/

#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>     
#include <time.h>       
#include <fstream>

using namespace std;

//variables
int noThreads = 1;
int overideNFactorial = 100000;
const double Min = 1;
const double Max = 100;
int experimentNumber = 1000; //number of iterations
int averageNumber = 50; //number of times to repeat a dimension
char newline[1] = "";

//file outputs
const char* file = "results/Example4.csv";
const char* execution_times_file = "results/ExecutionTimes.txt";

void FileWriter(char* output, const char* file)
{
	ofstream myfile;
  	myfile.open (file, std::ios_base::app);
		myfile << output << "\n";
  	myfile.close();
}

void initFileOuts()
{
	char header1[50] = "Parallel Recursive Factorial, Time";
	FileWriter(header1, file);
}

int calcRecursiveFactorial (int n)
{
	if (n <= 1)
	{
		return 1;
	}

	return n * calcRecursiveFactorial(n-1);
}

int calcUpperRecursiveFactorial (int n, int half)
{
	if (n <= half)
	{
		return 1;
	}

	return n * calcUpperRecursiveFactorial(n-1, half);
}

int calcParallelRecursiveFactorial (int n)
{
	int factorial = 1;
	//#pragma omp main
	{
		int p,q = 1;
		#pragma omp sections
		{
			#pragma omp section
			{
				int half = ceil(n/2);
				p = calcUpperRecursiveFactorial(n, half);				
			}

			#pragma omp section
			{
				//bottom end
				q = floor(n/2);
				q = calcRecursiveFactorial(q);				
			}			
		}

		#pragma omp reduction
		{
			factorial = p * q;
		}
	}
}

int main (int argc, char* argv[])
{
	//check if args
	if (argc != 3)
	{
		std::cout << "Error: Must have two arguments.";
		throw std::length_error("Must have two arguments.");
	}
	
	overideNFactorial = atoi(argv[1]);
	averageNumber = atoi(argv[2]);

	//seed rnd
	srand(time(NULL));

	cout << "Running Parallel Recursive Factorial ..." << endl;
	initFileOuts();

	int n = 0;
	if (overideNFactorial > 0)
	{
		n = overideNFactorial;
	}
	else
	{
		int n = rand()*(Max-Min) + Min; // between 500 and 100
	}

	double start_main = omp_get_wtime();

	int factorial = calcParallelRecursiveFactorial(n);

	double end_main = omp_get_wtime(); 
	double diff_main = end_main - start_main;
	
	cout << "Parallel Recursive Factorial of n: " << n << " is: " << factorial << endl;
	cout << "main execution time: " << diff_main << endl;

	char answer[500] = "";
	sprintf(answer, "%d,%f", factorial, diff_main);
	FileWriter(answer, file);

	char lineout[255] = "";
	sprintf (lineout, "Example 4 Main Execution Time: %f", diff_main);
	FileWriter(lineout, execution_times_file);

}