/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 2.lab2_recursive_factorial.cpp -o example2.out
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

const int overideNFactorial = 100000; //max before a seg fault
const double Min = 1;
const double Max = 100;
/*const bool PrintArray = true;*/
const int experimentNumber = 1000; //number of iterations
const int averageNumber = 50; //number of times to repeat a dimension

char newline[1] = "";

//file outputs
const char* file = "results/Example2.csv";
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
	char header1[50] = "Recursive Factorial, Time";
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

int main () 
{	
	//seed rnd
	srand(time(NULL));

	cout << "Running Recursive Factorial ..." << endl;
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

	int factorial = calcRecursiveFactorial(n);

	double end_main = omp_get_wtime(); 
	double diff_main = end_main - start_main;
	
	cout << "Recursive Factorial of n: " << n << " is: " << factorial << endl;
	cout << "main execution time: " << diff_main << endl;

	char answer[500] = "";
	sprintf(answer, "%d,%f", factorial, diff_main);
	FileWriter(answer, file);

	char lineout[255] = "";
	sprintf (lineout, "Example 2 Main Execution Time: %f", diff_main);
	FileWriter(lineout, execution_times_file);

}