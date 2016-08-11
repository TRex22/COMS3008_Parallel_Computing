/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 2.cpp -o example2.out

Usage: ./example2.out initThread particleCount blockSize noIncrements incrementSize writeFile?

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

const double analytical_integration_answer = pow(-exp(1), (-20)) * (20) - pow(exp(1), (-20)) + 1; //found in part 2 of lab 3 documentation

//file outputs
const char* file1 = "results/Example2_parallel_partitions.csv";
const char* file2 = "results/Example2_parallel_threads.csv";
const char* file3 = "results/Example2_serial.csv";

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
	char header1[75] = "Partition Size, Parallel Sim Approximation, Time, Error, Abs Error";
	FileWriter(header1, file1);

	char header2[75] = "Thread Count, Parallel Sim Approximation, Time, Error, Abs Error";
	FileWriter(header2, file2);

	char header3[75] = "Partition Size, Serial Sim Approximation, Time, Error, Abs Error";
	FileWriter(header3, file3);
}

double calcFunction(double x)
{
	return x * pow(exp(1), (-x));
}

bool simPoint(double c, double d)
{
	//make random x,y
	unsigned int seed = time(NULL);//omp_get_thread_num(); //could use, not proper seed tho

	double x = (double)rand_r(&seed) * (b - a) / ((double)RAND_MAX - a);
	double y = (double)rand_r(&seed) * (d - c) / ((double)RAND_MAX - c);

	//cout << "x:" << x << " y:" << y << endl;
	//in or out

	double functionValue = calcFunction(x);

	if (y > functionValue)
	{
		return false;
	}
	else
	{
		return true;
	}
}

double simulateFunction(int particleCount, double c, double d)
{
	double total = 0;
	double inGraph = 0;
	//TODO fix
	for (int i = 0; i < particleCount; i++)
	{
		bool test = simPoint(c, d);
		if (test)
		{
			inGraph  = inGraph + 1;
		}
		total = i + 1;
	}

	//printf("in: %i total: %i", inGraph, total);
	double result = inGraph / total;
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
	srand((unsigned)time(NULL));

	//check if args
	if (argc != 7)
	{
		std::cout << "Error: Must have six arguments.";
		throw std::length_error("Must have six arguments.");
	}

	//initThread particleCount blockSize noIncrements incrementSize writeFile?
	int noThreads = atoi(argv[1]);
	int initialParticleCount = atoi(argv[2]);
	int blockSize = atoi(argv[3]);
	int noIncrements = atoi(argv[4]);
	int incrementSize = atoi(argv[5]);

	writeFile = atoi(argv[6]);

	omp_set_num_threads(noThreads);

	cout << "Running Monte Carlo Trapezoidal Solver ..." << endl;
	initFileOuts();

	double start_main = omp_get_wtime();

	//cout << "a:" << a << " b:" << b << endl;

	double c = calcFunction(a);
	double d = calcFunction(b);
	//cout << "c:" << c << " d:" << d << endl;

	double approx = simulateFunction(initialParticleCount, c, d);

	printf("%f\n", approx);

	double end_main = omp_get_wtime();
	double diff_main = end_main - start_main;

	char lineout[255] = "";
	sprintf (lineout, "Example 1 Main Execution Time: %f", diff_main);
	cout << "main execution time: " << diff_main << endl;
	FileWriter(lineout, execution_times_file);
}