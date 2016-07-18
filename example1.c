#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <chrono>

using namespace std;

int main () {
	#pragma omp parallel
	{
		/*while (true){
			int threadId = omp_get_thread_num();
			//printf("hello(%d)", threadId);
			//printf("world(%d)\n", threadId);
			//cout << "hello world " << threadId << "\n" << endl;
			printf("hello world Thread: %d \n", threadId);
		}*/
		auto t1 = std::chrono::high_resolution_clock::now();

		int threadId = omp_get_thread_num();
			//printf("hello(%d)", threadId);
			//printf("world(%d)\n", threadId);
			//cout << "hello world " << threadId << "\n" << endl;
			printf("hello world Thread: %d \n", threadId);
		
		auto t2 = std::chrono::high_resolution_clock::now();
    	std::cout << "f() took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
              << " milliseconds\n";

	}
	return 0;
}
