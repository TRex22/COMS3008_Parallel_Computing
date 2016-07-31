/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 4.lab2_parallel_recursive_factorial.cpp -o example4.out
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

const int overideNFactorial = 10000;
const double Min = 1;
const double Max = 100;
/*const bool PrintArray = true;*/
const int experimentNumber = 1000; //number of iterations
const int averageNumber = 50; //number of times to repeat a dimension

char newline[1] = "";

//file outputs
const char* file = "results/Example4.csv";

void FileWriter(char* output, const char* file)
{
	ofstream myfile;
  	myfile.open (file, std::ios_base::app);
		myfile << output << "\n";
  	myfile.close();
}

void initFileOuts()
{
//	char header1[50] = "Sequential Factorial";
	//FileWriter(header1, file);
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