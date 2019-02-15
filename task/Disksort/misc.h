#pragma once

#include <string>

void mad(); // throw exception which means there is something wrong
void write_array(std::string filename, int arr[], int len);
	// write the contents of the array in the binary file and the text file for debugging
void gen_data(std::string filename, int size);
