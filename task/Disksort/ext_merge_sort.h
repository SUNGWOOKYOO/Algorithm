#pragma once

class ExtMergeSort {
public:
	ExtMergeSort(int page_size);
	int get_initial_buffer_size(); // 3 * page_size
	void main();
private:
	const int page_size;
	const int initial_buffer_size; // 3 * page_size
	int num_of_initial_files; // the number of output files of the initial pass
	void initial_pass();
};
