#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace helpers
{
	public: 
		class FileWriter(String output)
		{
			ofstream myfile;
		  	myfile.open ("results.txt");
	  		myfile << output + "\n";
		  	myfile.close();
		}

		class timer()
		{
			
		}


}