/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 4.lab2_parallel_recursive_factorial.cpp -o example4.out

usage: ./example4.out n averageNumber incrementSize noIncrements writeFile? noThreads

./compile.sh to compile everything
./kickoff to run all, save to file and then determine averages using dataProcessor.out
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
int n = 100000;
const double Min = 1;
const double Max = 100;
int experimentNumber = 1000; //number of iterations
int averageNumber = 50; //number of times to repeat a dimension
char newline[1] = "";
bool writeFile = 1;

//file outputs
const char* file = "results/Example4.csv";
const char* execution_times_file = "results/ExecutionTimes.txt";

void FileWriter(char* output, const char* file)
{
	if (writeFile)
	{
		ofstream myfile;
	  	myfile.open (file, std::ios_base::app);
			myfile << output << "\n";
	  	myfile.close();
	}
}

void initFileOuts()
{
	char header1[50] = "n, Time, Factorial";
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
	int p,q = 1; 
	//public variables in the scope of sections because the sections do not every use each others variable
	//also the recution operation is implicit when the parallel block of code is complete, p and q are multiplied into factorial
	
	#pragma omp parallel
	{		
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
	}
	factorial = p * q;
}

int main (int argc, char* argv[])
{
	//check if args
	if (argc != 7)
	{
		std::cout << "Error: Must have six arguments.";
		throw std::length_error("Must have six arguments.");
	}

	n = atoi(argv[1]);
	averageNumber = atoi(argv[2]);
	int increment = atoi(argv[3]);
	experimentNumber = atoi(argv[4]);

	writeFile = atoi(argv[5]);
	noThreads = atoi(argv[6]);
	omp_set_num_threads(noThreads);

	cout << "Running Parallel Recursive Factorial ..." << endl;
	initFileOuts();

	double start_main = omp_get_wtime();
	
	for (int i = 0; i < experimentNumber; i++)
	{
		for (int j = 0; j < averageNumber; j++)
		{
			double start = omp_get_wtime();

			unsigned int factorial = calcParallelRecursiveFactorial(n);

			double end = omp_get_wtime(); 
			double diff = end - start;
			
			if (!writeFile)
			{
				cout << "Parallel Recursive Factorial of n: " << n << " is: " << factorial << endl;
				cout << "main execution time: " << diff << endl;
			}

			char answer[500] = "";
			sprintf(answer, "%d,%f,%d", n, diff, factorial);
			FileWriter(answer, file);					
		}
		FileWriter(newline, file);	
		n = n + increment;
	}


	double end_main = omp_get_wtime(); 
	double diff_main = end_main - start_main;
	
	char lineout[255] = "";
	sprintf (lineout, "Example 4 Main Execution Time: %f", diff_main);
	cout << "main execution time: " << diff_main << endl;
	FileWriter(lineout, execution_times_file);

}