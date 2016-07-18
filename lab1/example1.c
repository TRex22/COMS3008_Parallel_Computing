#include "stdio.h"
#include "omp.h"
#include <iostream>

using namespace std;
//g++ -fopenmp
#pragma omp parallel
int main () {	
	{
		/*while (true){
			int threadId = omp_get_thread_num();
			//printf("hello(%d)", threadId);
			//printf("world(%d)\n", threadId);
			//cout << "hello world " << threadId << "\n" << endl;
			printf("hello world Thread: %d \n", threadId);
		}*/

		int threadId = omp_get_thread_num();			
		printf("hello world Thread: %d \n", threadId);

		//printf("hello(%d)", threadId);
		//printf("world(%d)\n", threadId);
		//cout << "hello world " << threadId << "\n" << endl;
	}
	return 0;
}

void serialOperation(){

}


void parallelOperation(){
	int threadId = omp_get_thread_num();
	//printf("hello(%d)", threadId);
	//printf("world(%d)\n", threadId);
	//cout << "hello world " << threadId << "\n" << endl;
	printf("hello world Thread: %d \n", threadId);
}
