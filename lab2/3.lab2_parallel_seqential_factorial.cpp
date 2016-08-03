/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 3.lab2_parallel_seqential_factorial.cpp -o example3.out
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
const char* file = "results/Example3.csv";
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

int calcSeqentialFactorial (int n)
{
	int factorial = n;

	#pragma omp parallel
	{
		#pragma omp for
		for (int i = 1; i < n - 1; i++)
		{
			factorial = factorial * (n - i);
		}
	}
	
	return factorial;
}

int main (int argc, char* argv[])
{
	//check if args
	if (argc != 6)
	{
		std::cout << "Error: Must have five arguments.";
		throw std::length_error("Must have five arguments.");
	}

	n = atoi(argv[1]);
	averageNumber = atoi(argv[2]);
	int increment = atoi(argv[3]);
	experimentNumber = atoi(argv[4]);

	writeFile = atoi(argv[5]);

	cout << "Running Parallel Sequential Factorial ..." << endl;
	initFileOuts();

	for (int i = 0; i < experimentNumber; i++)
	{
		n = n + increment;
		for (int j = 0; j < averageNumber; j++)
		{
			double start_main = omp_get_wtime();

			int factorial = calcSeqentialFactorial(n);

			double end_main = omp_get_wtime(); 
			double diff_main = end_main - start_main;
			
			/*cout << "Parallel Sequential Factorial of n: " << n << " is: " << factorial << endl;
			cout << "main execution time: " << diff_main << endl;*/

			char answer[500] = "";
			sprintf(answer, "%d,%f,%f", n, diff_main, factorial);
			FileWriter(answer, file);
			FileWriter(newline, file);			
		}
	}

	/*char lineout[255] = "";
	sprintf (lineout, "Example 3 Main Execution Time: %f", diff_main);
	FileWriter(lineout, execution_times_file);*/

}