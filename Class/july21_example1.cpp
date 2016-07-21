#include <iostream>
#include "omp.h"

using namespace std;

int main(){
	//omp_set_num_threads(29622); //50 000 is near limit 30 000
	//omp_set_num_threads(25000);
	omp_set_num_threads(100);
	#pragma omp single
	{

	}
	int numProcs = 0;
	int numThreads = 0;
	#pragma omp parallel
	{
		numProcs = omp_get_num_procs();
		numThreads = omp_get_num_threads();
	}

	cout << "numProcs: " << numProcs << endl;
	cout << "numThreads: " << numThreads << endl;

	int count1 = 0;
	#pragma omp parallel
	{
		//#pragma omp atomic
		count1 = count1 + 1; //not always the same value
	}
	cout << "count1: " << count1 << endl;	

	int count2 = 0;
	#pragma omp parallel
	{
		#pragma omp atomic
		count2 = count2 + 1;
	}
	cout << "count2: " << count2 << endl;

	#pragma omp parallel
	{
		/*while(true)
		{
			cout << "oh no!" << endl;
		}*/
	}
}