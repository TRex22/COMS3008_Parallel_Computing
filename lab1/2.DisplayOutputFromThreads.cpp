/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 2.DisplayOutputFromThreads.cpp -o example2.out
*/

#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>     
#include <time.h>       
#include <fstream>

using namespace std;

const int experimentNumber = 100; //number of times to increment a dimension
const int incrementNumber = 5; //increment size of a dimension
const int startNumberOfThreads = 1;
char newline[1] = "";

//file output
const char* file = "results/Example2_Increment_ThreadCount.csv";
const char* file2 = "results/Example2_Fixed_At_10_Threads.csv";
const char* execution_times_file = "results/ExecutionTimes.txt";

void FileWriter(char* output, const char* file)
{
	ofstream myfile;
  	myfile.open (file, std::ios_base::app);
		myfile << output << "\n";
  	myfile.close();
}

void serialOperation(){
	int threadId = omp_get_thread_num();			
	printf("hello world Thread: %d \n", threadId);
}

void parallelOperation(const char* file_out){

	#pragma omp parallel		
	{
		int threadId = omp_get_thread_num();			
		//printf("std out using thread: %d \n", threadId);

		char lineout[255] = "";
		sprintf(lineout, "%d", threadId);
		FileWriter(lineout, file_out);
	}
}

void initFileOuts()
{
	char header[20] = "Thread";
	FileWriter(header, file);
	FileWriter(header, file2);
}

void IncreasingNoThreads()
{
	for (int i = 0; i < experimentNumber; i++)
	{
		omp_set_num_threads(startNumberOfThreads + (incrementNumber * i));
		//serialOperation(); //just a test, it is always main thread (0)
		parallelOperation(file);
		FileWriter(newline, file);
	}
}

void FixedAt10Threads()
{
	for (int i = 0; i < experimentNumber; i++)
	{
		omp_set_num_threads(10);
		//serialOperation(); //just a test, it is always main thread (0)
		parallelOperation(file2);
		FileWriter(newline, file2);
	}
}

int main () {	
	{
		cout << "Running Experiment 2 ..." << endl;
		initFileOuts();
		double start = omp_get_wtime();

		IncreasingNoThreads();
		FixedAt10Threads();		

		double end = omp_get_wtime(); 
		double diff = end - start;
		cout << "main execution time: " << diff << endl;

		char lineout[255] = "";
		sprintf (lineout, "Example 2 Main Execution Time: %f", diff);
		FileWriter(lineout, execution_times_file);
	}
	return 0;
}