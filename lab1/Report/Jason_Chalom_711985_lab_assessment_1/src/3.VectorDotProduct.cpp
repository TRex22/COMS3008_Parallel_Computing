/*
Jason Chalom 711985 2016
Use: g++ -fopenmp 3.VectorDotProduct.cpp -o example3.out
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
int row = 5000000;
int noThreads = 1;

const double Min = 0.00;
const double Max = 100.00;
/*const bool PrintArray = true;*/
const int experimentNumber = 1000; //number of iterations
const int averageNumber = 50; //number of times to repeat a dimension

char newline[1] = "";

//file outputs
const char* exp1File = "results/Example3_1_VaryNoThreads_FixedArraySize.csv";
const char* exp2File = "results/Example3_2_VaryArraySize_FixedThreadCount4.csv";
const char* exp3File = "results/Example3_3_RND_Parallel_VaryThreads.csv";
const char* exp4File = "results/Example3_4_RND_Parallel_VaryArraySize.csv"; 
const char* execution_times_file = "results/ExecutionTimes.txt";

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

double* RandomVector()
{
	double *vector = new double[row];

	for(int i = 0; i < row; i++)
	{
		vector[i] = rand()*(Max-Min) + Min;
	}

	return vector;
}

double* ParallelRandomVector()
{
	double *vector = new double[row];

	#pragma omp parallel for
	for(int i = 0; i < row; i++)
	{
		vector[i] = rand()*(Max-Min) + Min;
	}

	return vector;
}

double DotProduct(double *vector1, double *vector2)
{
	if (sizeof(vector1) == sizeof(vector2)) //hack
	{
		double sum = 0.00;
		for (int i = 0; i < row; i++)
		{
			sum += vector1[i]*vector2[i];
		}

		//cout << "Seqential DotProduct: " << sum << endl;
		return sum;
	}

	return 0.00;
}

double ParallelDotProduct(double *vector1, double *vector2)
{
	if (sizeof(vector1) == sizeof(vector2)) //hack
	{
		double sum = 0.00;

		#pragma omp parallel for
		for (int i = 0; i < row; i++)
		{
			sum += vector1[i]*vector2[i];
		}

		//cout << "Parallel DotProduct: " << sum << endl;
		return sum;
	}

	return 0.00;
}

double seqential_dot_product()
{
	double start = omp_get_wtime();

	double *vector1 = RandomVector ();		
	double *vector2 = RandomVector ();		

	double dotProd = DotProduct(vector1, vector2);
	
	double end = omp_get_wtime(); 
	double diff = end - start;
	//cout << diff << endl;

	delete[] vector1;
	delete[] vector2;

	return diff;
}

double parallel_dot_product()
{
	double start = omp_get_wtime();

	double *vector1 = RandomVector ();		
	double *vector2 = RandomVector ();		

	double dotProd = ParallelDotProduct(vector1, vector2);
	
	double end = omp_get_wtime(); 
	double diff = end - start;
	//cout << diff << endl;

	delete[] vector1;
	delete[] vector2;

	return diff;
}

double parallel_dot_product_rnd()
{
	double start = omp_get_wtime();

	double *vector1 = ParallelRandomVector ();		
	double *vector2 = ParallelRandomVector ();			

	double dotProd = ParallelDotProduct(vector1, vector2);
	
	double end = omp_get_wtime(); 
	double diff = end - start;
	//cout << diff << endl;

	delete[] vector1;
	delete[] vector2;

	return diff;
}

void VaryNoThreads()
{
	//fix array size to row = 5000000
	row = 5000000;

	for (int i = 0; i < experimentNumber; i++)
	{
		noThreads = i + 1;
		for (int j = 0; j < averageNumber; j++)
		{
			omp_set_num_threads(noThreads);

			double executionTime = parallel_dot_product();

			char lineout[25] = "";
			sprintf(lineout, "%d,%f", (i+1), executionTime);
			FileWriter(lineout, exp1File);
		}
		FileWriter(newline, exp1File);	
	}
}

void VarySizeOfVector()
{
	//fix thread count to 4
	noThreads = 4;
	omp_set_num_threads(noThreads);

	for (int i = 0; i < experimentNumber; i++)
	{
		row = i + 1;
		for (int j = 0; j < averageNumber; j++)
		{
			double executionTime = parallel_dot_product();

			char lineout[25] = "";
			sprintf(lineout, "%d,%f", (i+1), executionTime);
			FileWriter(lineout, exp2File);
		}
		FileWriter(newline, exp1File);
	}
}

void ParallelizeRNDFixRow()
{
	//fix array size to row = 5000000
	row = 5000000;

	for (int i = 0; i < experimentNumber; i++)
	{
		noThreads = i + 1;
		for (int j = 0; j < averageNumber; j++)
		{
			omp_set_num_threads(noThreads);

			double executionTime = parallel_dot_product_rnd();

			char lineout[25] = "";
			sprintf(lineout, "%d,%f", (i+1), executionTime);
			FileWriter(lineout, exp3File);
		}
		FileWriter(newline, exp1File);
	}
}

void ParallelizeRNDFixThreads()
{
	//fix thread count to 4
	noThreads = 4;
	omp_set_num_threads(noThreads);

	for (int i = 0; i < experimentNumber; i++)
	{
		row = i + 1;
		for (int j = 0; j < averageNumber; j++)
		{
			double executionTime = parallel_dot_product_rnd();

			char lineout[25] = "";
			sprintf(lineout, "%d,%f", (i+1), executionTime);
			FileWriter(lineout, exp4File);
		}
		FileWriter(newline, exp1File);
	}
}

void initFileOuts()
{
	char header1[20] = "ThreadCount,Time";
	char header2[20] = "Dimension,Time";

	FileWriter(header1, exp1File);
	FileWriter(header2, exp2File);
	FileWriter(header1, exp3File);
	FileWriter(header2, exp4File);

}

int main () 
{	
	//seed rnd
	srand(time(NULL));

	cout << "Running Experiment 3 ..." << endl;
	initFileOuts();

	double start_main = omp_get_wtime();

	//standard tests
	/*
		seqential_dot_product();
		parallel_dot_product();
		parallel_dot_product_rnd();
	*/

	VaryNoThreads();
	VarySizeOfVector();
	ParallelizeRNDFixRow();
	ParallelizeRNDFixThreads();

	double end_main = omp_get_wtime(); 
	double diff_main = end_main - start_main;
	cout << "main execution time: " << diff_main << endl;

	FileWriter(newline, exp1File);
	FileWriter(newline, exp2File);
	FileWriter(newline, exp3File);
	FileWriter(newline, exp4File);

	char lineout[255] = "";
	sprintf (lineout, "Example 3 Main Execution Time: %f", diff_main);
	FileWriter(lineout, execution_times_file);

	return 0;
}
