/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 3.lab2_parallel_seqential_factorial.cpp -o example3.out
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
	char header1[20] = "Sequential Factorial";
	FileWriter(header1, file);
}

int main () 
{	
	//seed rnd
	srand(time(NULL));

	cout << "Running Sequential Factorial ..." << endl;
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

}