#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;

//http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
//taken from a library Im writing
double RandomDouble (double min, double max)
{
	random_device rd;     // only used once to initialise (seed) engine
	mt19937_64 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	uniform_real_distribution<double> uni(min, max); // guaranteed unbiased
	double random_integer = uni(rng);
	return random_integer;
}

/*double** rndMatrix(int row, int col, int min, int max){
	double** pmatrix = new double *[row];
	for (int i = 0; i < row; i++)
	{
		pmatrix[i] = new double[col];
		for (int j = 0; j < col; j++)
		{
			pmatrix[i][j] = RandomDouble(min, max);
		}
	}

	return pmatrix;
}*/
int row, col = 20;
double** mat = new double[row][col];

void row_dominant(){
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mat[i][j] = RandomDouble(min, max);
		}
	}
}

void col_dominant(){
	for (int j = 0; j < col; j++)
	{
		for (int i = 0; i < row; i++)
		{
			mat[i][j] = RandomDouble(min, max);
		}
	}
}

int main () {	
	{
		double start = omp_get_wtime();

		row_dominant();
		col_dominant();

		double end = omp_get_wtime(); 
		double diff = end - start;
		cout << diff << endl;
	}
	return 0;
}