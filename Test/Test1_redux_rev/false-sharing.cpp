/*
COMS 3008 PC Test 1
Jason Chalom 711985
False Sharing example
*/

#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include "stdlib.h"

using namespace std;

//from wikipedia
//https://en.wikipedia.org/wiki/False_sharing

int x;
int y;

//edited to make omp sections rather than two 'concurrent' functions
void parallel(){
	#pragma omp parallel shared(x,y)
	{
	   #pragma omp sections
		{
			#pragma omp section 
			{
				int sum = 0;
				for (int i = 0; i < 1000000; i++){
					sum += x;
				}
				cout << sum << endl;
			}
			
			#pragma omp section 
			{
				for (int i = 0; i < 1000000; i++){
					y++;
				}
			}			
		}
    }
}

int main(){

	parallel();
}