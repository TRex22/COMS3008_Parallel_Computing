/*
Jason Chalom 711985 2016
Data Miner, do some basic stats on data collected
Use: g++ -fopenmp DataProcessor.cpp
*/

#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>     
#include <time.h>       
#include <fstream>
#include <string>
#include <cstring>
#include <stdexcept>

using namespace std;

void FileWriter(char* output, const char* file)
{
	ofstream myfile;
  	myfile.open (file, std::ios_base::app);
		myfile << output << "\n";
  	myfile.close();
}

double** GetCSVValues(char** block, int block_count)
{
	double** values = new double*[block_count];
	char* chars_array_delim;

	for(int i = 0; i < block_count; i++)
	{
		values[i] = new double[2];

		//cout << "block: " << block[0] << endl;
		//cout << "TEST: "<< sizeof(block) << endl;

		chars_array_delim = strtok(block[i], ",");

		if (chars_array_delim != NULL)
		{
			values[i][0] = atof(chars_array_delim);
			chars_array_delim = strtok (NULL, ",");
			values[i][1] = atof(chars_array_delim);
		}

		//cout << "dim" << values[i][0] << " tim: " << values[i][1] <<  endl;
	}

	return values;
}

double CalcAverage(double** values, int block_count)
{
	double sum = 0.0;

	for (int i = 0; i < block_count; i++)
	{
		sum += values[i][1];
	}

	return (sum / block_count);
}

double FindMax(double** values, int block_count)
{
	double max = values[0][1];

	for (int i = 0; i < block_count; i++)
	{
		double currentNumber = values[i][1];

		if (currentNumber > max)
		{
			max = currentNumber;
		}
	}

	return max;
}

double FindMin(double** values, int block_count)
{
	double min = values[0][1];

	for (int i = 0; i < block_count; i++)
	{
		double currentNumber = values[i][1];

		if (currentNumber < min)
		{
			min = currentNumber;
		}
	}

	return min;
}

double CalcRange(double min, double max)
{
	return max - min;
}

double CalcVariance(double** values, int block_count)
{
	double varSum = 0.0;

	for (int i = 0; i < block_count; i++)
	{
		varSum += pow(values[i][1], 2);
	}

	return varSum / block_count;
}

void InitOutput(char* file)
{
	char header[50] = "n,Average,Min,Max,Range,Variance";
	FileWriter(header, file);
}

//first arg is file to look at, second is where to save the results, thrid no rows
//averages per block
//range, min and max
//variance

//get a block
//count the block to use as a marker
//store in memory - small enough data
//then calc all required values
//save to file
int main(int argc, char* argv[])
{
	//check if args
	if (argc != 4)
	{
		std::cout << "Error: Must have three arguments.";
		throw std::length_error("Must have three arguments.");
	}

	int BLOCK_SIZE = atoi(argv[3]);
	InitOutput(argv[2]);

	string line;
	ifstream file (argv[1]);

	if (file.is_open())
	{
		cout << "Data Processor Starting...\n" << "File is open."<<endl;

		int block_count = 0;
		char** block = new char*[BLOCK_SIZE];
		for(int i = 0; i < BLOCK_SIZE; i++)
		{
			block[i] = new char[255];
		}

		getline(file,line); // remove first line

		while (getline (file,line))
		{
			//cout << line << '\n';

			//if line is empty
			if (line.empty())
			{
				getline(file,line); // remove line
			}

			block[block_count];
			sprintf(block[block_count], "%s", line.c_str());

			block_count++;			
			
			if (block_count == BLOCK_SIZE)
			{
				double** values = GetCSVValues(block, BLOCK_SIZE);

				double avg = CalcAverage(values, BLOCK_SIZE);
				double min = FindMin(values, BLOCK_SIZE);
				double max = FindMax(values, BLOCK_SIZE);
				double range = CalcRange(min, max);
				double var = CalcVariance(values, BLOCK_SIZE);

				char LineAvg[255] = "";

				//cout << "block: " << block[0] << endl;

				sprintf(LineAvg, "%d,%f,%f,%f,%f,%f", int(*values[0]), avg, min, max, range, var);
				FileWriter(LineAvg, argv[2]);

				//reset stuff
				block_count = 0;
				for (int i = 0; i < BLOCK_SIZE; i++)
				{
				    delete [] block[i];
				    block[i] = new char[255];
				}
			}
		}

		file.close();
		cout << "Complete." << endl;
	}

	else cout << "Unable to open file"; 

	return 0;
}