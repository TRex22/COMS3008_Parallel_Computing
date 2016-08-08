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
const double Min = 1;
const double Max = 100;
bool writeFile = 0;
char newline[1] = "";

const int a = 0;
const int b = 20;
const double analytical_integration_answer = pow(-exp(1),(-20)) * (20) - pow(exp(1),(-20)) + 1; //found in part 2 of lab 3 documentation

//file outputs
const char* file = "results/Example1.csv";
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

}

const long double calcFunction(double x)
{
	return x * pow(exp(1),(-x));
}

long double calcTrapezoidalApprox(int noPartitions) 
{
	double partitionWidth = (b-a) / noPartitions;

	double approx = calcFunction(a) + calcFunction(b); //end ones
	double a_now = a;
	for (int i = 0; i < noPartitions - 2; i++)
	{
		double b_now = (i+1) * (a_now + partitionWidth);
		approx += calcFunction(b_now);

		a_now = b_now;
	}

	return (partitionWidth / 2) * approx;
}

int main(int argc, char* argv[])
{
	//check if args
	if (argc != 10)
	{
		std::cout << "Error: Must have nine arguments.";
		throw std::length_error("Must have nine arguments.");
	}
	
	
	//omp_set_num_threads(noThreads);

	cout << "Running TrapezoidalSolver ..." << endl;
	initFileOuts();

	//partition width
	//(b-a)/amount
	double start_main = omp_get_wtime();

	double noPartitions = 1000.00;
	long double trapezoidal_approximation = calcTrapezoidalApprox(noPartitions);
	cout << "Approx: " << trapezoidal_approximation << endl;

	double end_main = omp_get_wtime(); 
	double diff_main = end_main - start_main;

	char lineout[255] = "";
	sprintf (lineout, "Example 1 Main Execution Time: %f", diff_main);
	cout << "main execution time: " << diff_main << endl;
	FileWriter(lineout, execution_times_file);	
}