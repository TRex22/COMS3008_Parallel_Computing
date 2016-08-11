/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 1.TrapezoidalSolver.cpp -o example1.out

Usage: ./example1.out initThreads initialPartitions blockSize noIncrements incrementSize writeFile?

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
bool writeFile = 0;
char newline[1] = "";

const int a = 0;
const int b = 20;

const double analytical_integration_answer = pow(-exp(1),(-20)) * (20) - pow(exp(1),(-20)) + 1; //found in part 2 of lab 3 documentation

//file outputs
const char* file1 = "results/Example1_parallel_partitions.csv";
const char* file2 = "results/Example1_parallel_threads.csv";
const char* file3 = "results/Example1_serial.csv";

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
	char header1[75] = "Partition Size, Parallel Trapezoidal Approximation, Time, Error, Abs Error";
	FileWriter(header1, file1);

	char header2[75] = "Thread Count, Parallel Trapezoidal Approximation, Time, Error, Abs Error";
	FileWriter(header2, file2);

	char header3[75] = "Partition Size, Serial Trapezoidal Approximation, Time, Error, Abs Error";
	FileWriter(header3, file3);
}

double calcFunction(double x)
{
	return x * pow(exp(1),(-x));
}

double calcTrapezoidalApprox(int m)
{
	//using derivation (h/2)(sum(f(xi) + f(xi+1)))
	double h = (b-a);
	h = h / m;

	double approx = 0.0;
	double x0 = a;
	double x1 = a + h;

	for (int i = 0; i < m; i++)
	{
		approx += calcFunction(x0) + calcFunction(x1);
		x0 = x1;
		x1 = x1 + h;
	}

	double result = (h / 2) * approx;
	return result;
}

double calcParallelTrapezoidalApprox(int noThreads, int m)
{
	omp_set_num_threads(noThreads);
	//using derivation (h/2)(sum(f(xi) + f(xi+1)))
	double h = (b-a);
	h = h / m;

	double approx = 0.0;
	double x0 = a;
	double x1 = a + h;

	#pragma omp parallel for
	for (int i = 0; i < m; i++)
	{
		approx += calcFunction(x0) + calcFunction(x1);
		x0 = x1;
		x1 = x1 + h;
	}

	double result = (h / 2) * approx;
	return result;
}

double calcError(double approx)
{
	double error = analytical_integration_answer - approx;
	//cout << "error: " << error << endl;
	return error;
}

int main(int argc, char* argv[])
{
	//noThreads initialPartitions blockSize noIncrements incrementSize
	//check if args
	if (argc != 7)
	{
		std::cout << "Error: Must have six arguments.";
		throw std::length_error("Must have six arguments.");
	}

	int noThreads = atoi(argv[1]);
	int initialPartitions = atoi(argv[2]);
	int blockSize = atoi(argv[3]);
	int noIncrements = atoi(argv[4]);
	int incrementSize = atoi(argv[5]);

	writeFile = atoi(argv[6]);
	
	omp_set_num_threads(noThreads);

	cout << "Running TrapezoidalSolver ..." << endl;
	initFileOuts();

	double start_main = omp_get_wtime();

	//serial
	for (int i = 0; i < noIncrements; i++)
	{
		for (int j = 0; j < blockSize; j++)
		{
			int noPartitions = initialPartitions + (i * incrementSize);
			
			double start = omp_get_wtime();
			double trapezoidal_approximation = calcTrapezoidalApprox(noPartitions);
			double end = omp_get_wtime(); 
			double diff = end - start;

			double error = calcError(trapezoidal_approximation);

			if (!writeFile)
			{
				printf("%d,%f,%d,%e,%e  ", noPartitions, trapezoidal_approximation, diff, error, abs(error));
				cout << "main execution time: " << diff << endl;
			}

			//save to file
			//"Partition Size, Serial Trapezoidal Approximation, Time, Error"
			char answer[500] = "";
			sprintf(answer, "%d,%f,%d,%e,%e", noPartitions, trapezoidal_approximation, diff, error, abs(error));
			FileWriter(answer, file3);	
		}
	}
	
	//parallel partitions
	for (int i = 0; i < noIncrements; i++)
	{
		for (int j = 0; j < blockSize; j++)
		{
			//partition increment, lock no threads
			int noPartitions = initialPartitions + (i * incrementSize);
			noThreads = 4;

			double start = omp_get_wtime();
			double trapezoidal_approximation = calcParallelTrapezoidalApprox(noThreads, noPartitions);
			double end = omp_get_wtime(); 
			double diff = end - start;

			double error = calcError(trapezoidal_approximation);

			if (!writeFile)
			{
				printf("%d,%f,%d,%e,%e  ", noPartitions, trapezoidal_approximation, diff, error, abs(error));
				cout << "main execution time: " << diff << endl;
			}

			//save to file
			//"Partition Size, Serial Trapezoidal Approximation, Time, Error"
			char answer[500] = "";
			sprintf(answer, "%d,%f,%d,%e,%e", noPartitions, trapezoidal_approximation, diff, error, abs(error));
			FileWriter(answer, file1);


			//thread increment, lock no partitions
			noPartitions = 10000;
			noThreads = noThreads + (i * incrementSize);

			start = omp_get_wtime();
			double trapezoidal_approximation2 = calcParallelTrapezoidalApprox(noThreads, noPartitions);
			end = omp_get_wtime(); 
			diff = end - start;

			error = calcError(trapezoidal_approximation2);

			if (!writeFile)
			{
				printf("%d,%f,%d,%e,%e  ", noThreads, trapezoidal_approximation2, diff, error, abs(error));
				cout << "main execution time: " << diff << endl;
			}

			//save to file
			//"Partition Size, Serial Trapezoidal Approximation, Time, Error"
			char answer2[500] = "";
			sprintf(answer2, "%d,%f,%d,%e,%e", noThreads, trapezoidal_approximation2, diff, error, abs(error));
			FileWriter(answer2, file2);
		}
	}

	double end_main = omp_get_wtime(); 
	double diff_main = end_main - start_main;

	char lineout[255] = "";
	sprintf (lineout, "Example 1 Main Execution Time: %f", diff_main);
	cout << "main execution time: " << diff_main << endl;
	FileWriter(lineout, execution_times_file);	
}