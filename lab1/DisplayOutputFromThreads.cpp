#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <fstream>
/*Get values 
Averages?
plot*/
using namespace std;

void serialOperation(){
	int threadId = omp_get_thread_num();			
	printf("hello world Thread: %d \n", threadId);
}


void parallelOperation(){

	#pragma omp parallel		
	{
		int threadId = omp_get_thread_num();			
		printf("hello world Thread: %d \n", threadId);
	}
}

void FileWriter(char* output)
{
	ofstream myfile;
  	myfile.open ("results.txt");
		myfile << output << "\n";
  	myfile.close();
}

int main () {	
	{
		double start = omp_get_wtime();

		serialOperation();
		parallelOperation();
		
		double end = omp_get_wtime(); 
		double diff = end - start;
		cout << diff << endl;
	}
	return 0;
}