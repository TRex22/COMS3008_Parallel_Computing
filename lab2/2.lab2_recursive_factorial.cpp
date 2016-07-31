/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 2.lab2_recursive_factorial.cpp -o example2.out
*/

#include <stdio>
#include <stdlib>
#include <cmath>
#include <time.h>
#include <iostream>
#include <fstream>
#include <omp.h>

using namespace std;

//variables
int noThreads = 1;

const int overideNFactorial = 10000;
const double Min = 1;
const double Max = 100;
/*const bool PrintArray = true;*/
const int experimentNumber = 1000; //number of iterations
const int averageNumber = 50; //number of times to repeat a dimension

char newline[1] = "";

//file outputs
const char* file = "results/Example3_1_VaryNoThreads_FixedArraySize.csv";
const char* execution_times_file = "results/ExecutionTimes.txt";

void PrintMatrix (double *vector)
{
	std::cout << "Vector:" << endl;
	for (int i = 0; i < row; i++)
	{
		std::cout << vector[i] << " ";
		std::cout << std::endl;
	}
}

void FileWriter(char* output, const char* file)
{
	ofstream myfile;
  	myfile.open (file, std::ios_base::app);
		myfile << output << "\n";
  	myfile.close();
}

void initFileOuts()
{
	char header1[20] = "Sequential Factorial, Time";
	FileWriter(header1, file);
}

int calcRecursiveFactorial (int n)
{
	
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
	FileWriter(factorial, file);

	char lineout[255] = "";
	sprintf (lineout, "Example 2 Main Execution Time: %f", diff_main);
	FileWriter(lineout, execution_times_file);

}