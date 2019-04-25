#pragma once
#include <string>
#include <fstream>

#include "misc.h"

using std::string;

class OutputBuffer {
public:
	OutputBuffer(int capacity, string file_path, string debug_file_path);
	//	Allocate the array 'buffer'. Open OFS, OFS_debug.
	~OutputBuffer(); // Close the OFS, OFS_debug. Release the array 'buffer'
	void add(int);
	/*
		Add one integer to the 'buffer'.
		If the buffer is full,
			Write the contents of the buffer to the files.
			Clear the buffer (current_size = 0).
	*/

private:
	int *buffer;
	int capacity;
	int current_size;
	string filename;
	std::ofstream OFS, OFS_debug;
};
