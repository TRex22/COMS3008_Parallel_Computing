/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 2.cpp -o example2.out

Usage: ./example2.out initThread maxThreads particleCount blockSize noIncrements incrementSize writeFile?

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
const char* file1 = "results/Example2_parallel_particles.csv";
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
	char header1[75] = "Particle Size, Parallel Sim Approximation, Time, Error, Abs Error";
	FileWriter(header1, file1);

	char header2[75] = "Thread Count, Parallel Sim Approximation, Time, Error, Abs Error";
	FileWriter(header2, file2);

	char header3[75] = "Particle Size, Serial Sim Approximation, Time, Error, Abs Error";
	FileWriter(header3, file3);
}

double calcFunction(double x)
{
	return x * exp(-x);
}

double calcArea(double length, double breadth)
{
	return length * breadth;
}

double simArea(double c, double d)
{
	double length = d-c;
	double breadth = b-a;
	//cout << "Area: " << calcArea(length, breadth) << endl;
	return calcArea(length, breadth);
}

bool simPoint(double c, double d)
{
	//make random x,y
	unsigned int seed = time(NULL);//omp_get_thread_num(); //could use, not proper seed tho

	double x = (double)rand_r(&seed) * (b - a) / ((double)RAND_MAX - a);
	double y = (double)rand_r(&seed) * (d - c) / ((double)RAND_MAX - c);

	//cout << "x:" << x << " y:" << y << endl;

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
	d = d + 1;

	int total = 0;
	int belowGraph = 0;
/*	int aboveGraph = 0;*/
	
	for (int i = 0; i < particleCount; i++)
	{
		bool test = simPoint(c, d);
		if (test)
		{
			belowGraph++;
		}
/*		else
		{
			aboveGraph ++;
		}*/
		total++;
	}

	//printf("in: %i total: %i\n\n", belowGraph, total);
	
	double result = simArea(c,d) * (double)((double)belowGraph / (double)total);
	//printf("result: %f\n\n", result);

	return result;
}

double parallelSimulateFunction(int noThreads, int particleCount, double c, double d)
{
	d = d + 1.0;
	omp_set_num_threads(noThreads);

	int total = particleCount; //0;
	int belowGraph = 0;
	bool test = false;
	
	#pragma omp parallel for private(test) shared(c, d) reduction(+:belowGraph)
	for (int i = 0; i < particleCount; i++)
	{
		test = simPoint(c, d);
		if (test)
		{
			belowGraph++;
		}
		//total++;
	}

	double result = simArea(c,d) * (double)((double)belowGraph / (double)total);
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
	if (argc != 8)
	{
		std::cout << "Error: Must have seven arguments.";
		throw std::length_error("Must have seven arguments.");
	}

	//initThread maxThreads particleCount blockSize noIncrements incrementSize writeFile?
	int noThreads = atoi(argv[1]);
	int maxThreads = atoi(argv[2]);
	int initialParticleCount = atoi(argv[3]);
	int blockSize = atoi(argv[4]);
	int noIncrements = atoi(argv[5]);
	int incrementSize = atoi(argv[6]);

	writeFile = atoi(argv[7]);

	omp_set_num_threads(noThreads);

	cout << "Running Monte Carlo Trapezoidal Solver ..." << endl;
	initFileOuts();

	double c = calcFunction(a);
	double d = calcFunction(b);

	double start_main = omp_get_wtime();

	//serial
	cout << "serial: " << endl;
	for (int i = 0; i < noIncrements; i++)
	{
		for (int j = 0; j < blockSize; j++)
		{
			int noParticles = initialParticleCount + (i * incrementSize);

			double start = omp_get_wtime();
			double approx = simulateFunction(initialParticleCount, c, d);
			double end = omp_get_wtime();
			double diff = end - start;

			double error = calcError(approx);

			if (!writeFile)
			{
				printf("%d,%.11lf,%.11lf,%e,%e", noParticles, approx, diff, error, abs(error));
				cout << "main execution time: " << diff << endl;
			}

			//save to file
			//"Partition Size, Serial Trapezoidal Approximation, Time, Error"
			char answer[500] = "";
			sprintf(answer, "%d,%.11lf,%.11lf,%e,%e", noParticles, approx, diff, error, abs(error));
			FileWriter(answer, file3);
		}
	}

	//parallel
	cout << "parallel: " << endl;
	for (int i = 0; i < noIncrements; i++)
	{
		for (int j = 0; j < blockSize; j++)
		{
			//cout << "Parallel Particles: " << endl;
			//iterate through particles lock threads to 4
			int noParticles = initialParticleCount + (i * incrementSize);
			noThreads = 4;

			double start = omp_get_wtime();
			double approx1 = parallelSimulateFunction(noThreads, initialParticleCount, c, d);
			double end = omp_get_wtime();
			double diff = end - start;
			
			double error = calcError(approx1);

			if (!writeFile)
			{
				printf("%d,%.11lf,%.11lf,%e,%e", noParticles, approx1, diff, error, abs(error));
				cout << "main execution time: " << diff << endl;
			}

			//save to file
			//"Partition Size, Serial Trapezoidal Approximation, Time, Error"
			char answer1[500] = "";
			sprintf(answer1, "%d,%.11lf,%.11lf,%e,%e", noParticles, approx1, diff, error, abs(error));
			FileWriter(answer1, file1);

//			------------------------------------------------------------------------------------------       \\

			//iterate through threads lock particles to 1000000
			//cout << "Parallel Threads: " << endl;
			noThreads = (i * incrementSize);
		
			if (noThreads <= maxThreads)
			{
				noParticles = 1000000;
				
				start = omp_get_wtime();
				double approx2 = parallelSimulateFunction(noThreads, initialParticleCount, c, d);
				end = omp_get_wtime();
				diff = end - start;
				
				error = calcError(approx2);

				if (!writeFile)
				{
					printf("%d,%.11lf,%.11lf,%e,%e", noThreads, approx2, diff, error, abs(error));
					cout << "main execution time: " << diff << endl;
				}

				//save to file
				//"Partition Size, Serial Trapezoidal Approximation, Time, Error"
				char answer2[500] = "";
				sprintf(answer2, "%d,%.11lf,%.11lf,%e,%e", noThreads, approx2, diff, error, abs(error));
				FileWriter(answer2, file2);
			}
		}
	}

	double end_main = omp_get_wtime();
	double diff_main = end_main - start_main;

	char lineout[255] = "";
	sprintf (lineout, "Example 1 Main Execution Time: %.11lf", diff_main);
	cout << "main execution time: " << diff_main << endl;
	FileWriter(lineout, execution_times_file);
}