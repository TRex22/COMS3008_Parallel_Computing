/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 1.TrapezoidalSolver.cpp -o example1.out

Usage: 

./compile.sh to compile everything
./kickoff to run all, save to file and then determine averages using dataProcessor.out
*/

#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
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
const char* file = "results/Example2.csv";
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
/*	char header1[50] = "n, Time, Factorial";
	FileWriter(header1, file);*/
}

double calcFunction(double x)
{
	return x * pow(exp(1),(-x));
}

int main(int argc, char* argv[])
{
	//check if args
	if (argc != 7)
	{
		std::cout << "Error: Must have six arguments.";
		throw std::length_error("Must have six arguments.");
	}

	/*n = atoi(argv[1]);
	averageNumber = atoi(argv[2]);
	int increment = atoi(argv[3]);
	experimentNumber = atoi(argv[4]);

	writeFile = atoi(argv[5]);
	noThreads = atoi(argv[6]);
	omp_set_num_threads(noThreads);*/

	cout << "Running Monte Carlo Trapezoidal Solver ..." << endl;
	initFileOuts();

	double start_main = omp_get_wtime();

	

	double end_main = omp_get_wtime(); 
	double diff_main = end_main - start_main;

	char lineout[255] = "";
	sprintf (lineout, "Example 1 Main Execution Time: %f", diff_main);
	cout << "main execution time: " << diff_main << endl;
	FileWriter(lineout, execution_times_file);	
}