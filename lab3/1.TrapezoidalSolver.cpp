/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 1.TrapezoidalSolver.cpp -o example1.out

Usage: ./example1.out initThreads maxThreads initialPartitions blockSize noIncrements incrementSize writeFile?

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

const double a = 0.00;
const double b = 20.00;

const double analytical_integration_answer = 1 - (exp(-20)*20) - exp(-20); //found in part 2 of lab 3 documentation

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
	return x * exp(-x);
}

double calcTrapezoidalApprox(int m)
{
	//using derivation (h/2)(sum(f(xi) + f(xi+1)))
	double h = (b - a);
	h = h / m;

	double approx = 0.0;
	double x0 = a;
	double x1 = a + h;

	for (int i = 0; i < m - 1; i++)
	{
		approx += calcFunction(a + (i*h)) + calcFunction(a + ((i+1) * h));	
		/*cout << "calcFunction(x1)" << calcFunction(x1) << endl;*/
	}

	double result = (h / 2) * approx;
	return result;
}

double calcParallelTrapezoidalApprox(int noThreads, int m)
{
	omp_set_num_threads(noThreads);

	//using derivation (h/2)(sum(f(xi) + f(xi+1)))
	double h = (b - a);
	h = h / m;

	double approx = 0.0;

	#pragma omp parallel for reduction(+:approx)
	for (int i = 0; i < m - 1; i++)
	{
		approx += calcFunction(a + (i*h)) + calcFunction(a + ((i+1) * h));		
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
	//noThreads maxThreads initialPartitions blockSize noIncrements incrementSize
	//check if args
	if (argc != 8)
	{
		std::cout << "Error: Must have seven arguments.";
		throw std::length_error("Must have seven arguments.");
	}

	int noThreads = atoi(argv[1]);
	int maxThreads = atoi(argv[2]);
	int initialPartitions = atoi(argv[3]);
	int blockSize = atoi(argv[4]);
	int noIncrements = atoi(argv[5]);
	int incrementSize = atoi(argv[6]);

	writeFile = atoi(argv[7]);

	omp_set_num_threads(noThreads);

	cout << "Running TrapezoidalSolver ..." << endl;
	initFileOuts();

	double start_main = omp_get_wtime();

	//serial
	cout << "serial: " << endl;
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
				printf("%d,%.9lf,%.9lf,%e,%e  ", noPartitions, trapezoidal_approximation, diff, error, abs(error));
				cout << "main execution time: " << diff << endl;
			}

			//save to file
			//"Partition Size, Serial Trapezoidal Approximation, Time, Error"
			char answer[500] = "";
			sprintf(answer, "%d,%.9lf,%.9lf,%e,%e", noPartitions, trapezoidal_approximation, diff, error, abs(error));
			FileWriter(answer, file3);
		}
	}

	//parallel partitions
	cout << "parallel: " << endl;
	for (int i = 0; i < noIncrements; i++)
	{
		for (int j = 0; j < blockSize; j++)
		{
			//cout << "parallel partitions: " << endl;
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
				printf("%d,%.9lf,%.9lf,%e,%e  ", noPartitions, trapezoidal_approximation, diff, error, abs(error));
				cout << "main execution time: " << diff << endl;
			}

			//save to file
			//"Partition Size, Serial Trapezoidal Approximation, Time, Error"
			char answer[500] = "";
			sprintf(answer, "%d,%.9lf,%.9lf,%e,%e", noPartitions, trapezoidal_approximation, diff, error, abs(error));
			FileWriter(answer, file1);

//			------------------------------------------------------------------------------------------       \\
			
			//cout << "parallel threads: " << endl;
			noThreads = (i * incrementSize);
			if (noThreads == 0)
			{
				noThreads = 2;
			}

			if (noThreads <= maxThreads)
			{
				//thread increment, lock no partitions
				noPartitions = 1000000;
				
				start = omp_get_wtime();
				double trapezoidal_approximation2 = calcParallelTrapezoidalApprox(noThreads, noPartitions);
				end = omp_get_wtime();
				diff = end - start;

				error = calcError(trapezoidal_approximation2);

				if (!writeFile)
				{
					printf("%d,%.9lf,%.9lf,%e,%e  ", noThreads, trapezoidal_approximation2, diff, error, abs(error));
					cout << "main execution time: " << diff << endl;
				}

				//save to file
				//"Partition Size, Serial Trapezoidal Approximation, Time, Error"
				char answer2[500] = "";
				sprintf(answer2, "%d,%.9lf,%.9lf,%e,%e", noThreads, trapezoidal_approximation2, diff, error, abs(error));
				FileWriter(answer2, file2);
			}
		}
	}

	double end_main = omp_get_wtime();
	double diff_main = end_main - start_main;

	char lineout[255] = "";
	sprintf (lineout, "Example 1 Main Execution Time: %.9lf", diff_main);
	cout << "main execution time: " << diff_main << endl;
	FileWriter(lineout, execution_times_file);
}