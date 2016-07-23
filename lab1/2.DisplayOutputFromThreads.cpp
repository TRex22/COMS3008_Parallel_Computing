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
const char* file = "results/Example2.txt";

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

void parallelOperation(){

	#pragma omp parallel		
	{
		int threadId = omp_get_thread_num();			
		//printf("std out using thread: %d \n", threadId);

		char lineout[255] = "";
		sprintf(lineout, "%d", threadId);
		FileWriter(lineout, file);
	}
}

int main () {	
	{
		cout << "Running Experiment 2 ..." << endl;

		double start = omp_get_wtime();

		for (int i = 0; i < experimentNumber; i++)
		{
			omp_set_num_threads(startNumberOfThreads + (incrementNumber * i));
			//serialOperation(); //just a test, it is always main thread (0)
			parallelOperation();
			FileWriter(newline, file);
		}

		double end = omp_get_wtime(); 
		double diff = end - start;
		cout << "main execution time: " << diff << endl;

		char lineout[255] = "";
		sprintf (lineout, "main execution time: %f", diff);
		FileWriter(lineout, file);
	}
	return 0;
}