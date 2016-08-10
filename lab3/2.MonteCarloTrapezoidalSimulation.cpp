/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 2.cpp -o example2.out

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

const int padding = 20;

const double analytical_integration_answer = pow(-exp(1),(-20)) * (20) - pow(exp(1),(-20)) + 1; //found in part 2 of lab 3 documentation

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

bool simPoint(int c, int d)
{
	//make random x,y
	int x = rand()*(b-a)+a;
	int y = rand()*(d-c)+c;

	//in or out

	double functionValue = calcFunction(x);

	if (y > functionValue) return false;
	else return true;
}

double simulateFunction(int c, int d)
{
	int total = 0;
	int inGraph = 0;
	//TODO fix
	for (int i = 0; i < 1000000; i++)
	{
		bool test = simPoint(c, d);
		if (test)
		{
			inGraph ++;
		}
		total ++;
	}

	double result = inGraph / total;
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

	int c = calcFunction(a) + padding;
	int d = calcFunction(b) + padding;

	double approx = simulateFunction(c,d);

	printf("%f\n", approx);

	double end_main = omp_get_wtime(); 
	double diff_main = end_main - start_main;

	char lineout[255] = "";
	sprintf (lineout, "Example 1 Main Execution Time: %f", diff_main);
	cout << "main execution time: " << diff_main << endl;
	FileWriter(lineout, execution_times_file);	
}