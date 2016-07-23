//using a matrix dynamically allocated
void dynamic_array(char* dimensions)
{
	/*//it is statically allocated a beginning of program and destroyed at end of program
	double matrix[row][col];

	//row
	double start_row = omp_get_wtime();
	row_dominant(matrix);
	double end_row = omp_get_wtime(); 
	double diff_row = end_row - start_row;
	//write to file
	cout << "row_dominant execution time: " << diff_row << endl;
	char r_out[255] = "row_dominant execution time: ";
	sprintf(r_out, "%s %f", r_out, diff_row);
	FileWriter(r_out, row_dynamic_file);

	//col
	double start_col = omp_get_wtime();
	col_dominant(matrix);
	double end_col = omp_get_wtime(); 
	double diff_col = end_col - start_col;
	//write to file
	cout << "col_dominant execution time: " << diff_col << endl;
	char c_out[255] = "col_dominant execution time: ";
	sprintf(c_out, "%s %f", c_out, diff_col);
	FileWriter(c_out, col_dynamic_file);

	if(PrintArray)
	{
		PrintMatrix(matrix);
	}	*/
}

char row_d[255] = "row_dynamic_file";
FileWriter(row_d, row_dynamic_file);
char col_d[255] = "col_dynamic_file";
FileWriter(col_d, col_dynamic_file);

cout << "dynamic_array: " << endl;
dynamic_array(dimensions);



const char* row_dynamic_file = "results/Example1_row_dynamic.txt";
const char* col_dynamic_file = "results/Example1_col_dynamic.txt";