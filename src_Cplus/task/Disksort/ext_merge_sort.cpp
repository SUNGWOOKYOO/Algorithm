#include "ext_merge_sort.h"

#include <sstream>
#include <iostream>
#include <fstream>

#include "misc.h"
#include "sort.h"
#include "merge.h"

using std::stringstream;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;

ExtMergeSort::ExtMergeSort(int page_size) :
		page_size(page_size), initial_buffer_size(page_size * 3), num_of_initial_files(0) {
}

void ExtMergeSort::main() {
	initial_pass();

	int nRun = 0;

	// ASSUME that the input size is always initial_buffer_size * 2^n
	// Then, the number of files is always 2^n
	for (int i = num_of_initial_files; i >= 2; i /= 2) {
		// i: the number of input files to process
		int j = 0; // input file index
		int c = 0; // output file index
		while (j < i) {
			stringstream ss_out, ss_out_debug;
			ss_out << "output_binary/temp_" << (nRun + 1) << "_" << (c);
			ss_out_debug << "output_debug/temp_" << (nRun + 1) << "_" << (c++);
			stringstream ss_read1, ss_read2;
			ss_read1 << "output_binary/temp_" << nRun << "_" << (j++);
			ss_read2 << "output_binary/temp_" << nRun << "_" << (j++);

			string out_file_path = ss_out.str();
			string debug_out_file_path = ss_out_debug.str();
			string in_file_path1 = ss_read1.str();
			string in_file_path2 = ss_read2.str();

			// ========== implement here =============
			merge(page_size, in_file_path1, in_file_path2,
					out_file_path, debug_out_file_path);
			// =======================================
		}
		++nRun;
	}
}

int ExtMergeSort::get_initial_buffer_size() {
	return initial_buffer_size;
}

void ExtMergeSort::initial_pass() {
	ifstream IFS("input.bin", ios::binary);
	if (!IFS.is_open()) {
		cout << "failed to open input file" << endl;
		mad();
	}
	int fileID = 0;
	int *buf = new int[initial_buffer_size];
	while (IFS.read((char*) buf, sizeof(int) * initial_buffer_size)) {
		sort(buf, initial_buffer_size);
		stringstream ss_filename;
		ss_filename << "temp_0_" << fileID;
		write_array(ss_filename.str(), buf, initial_buffer_size);
		++fileID;
	}
	delete[] buf;
	num_of_initial_files = fileID;
}
