#include "output_buffer.h"

OutputBuffer::OutputBuffer(int capacity, string file_path, string debug_file_path) :
		capacity(capacity), current_size(0), OFS(file_path, std::ios::binary), OFS_debug(debug_file_path) {
	this->buffer = new int[capacity];
	// OFS.open(file_path, std::ios::binary);
	// OFS_debug.open(debug_file_path);
}

OutputBuffer::~OutputBuffer() {
	OFS.close();
	OFS_debug.close();
	delete[] buffer;
}

void OutputBuffer::add(int x) {
	buffer[current_size] = x;
	current_size++;
	if (current_size >= capacity){
		OFS.write((char*) buffer, sizeof(int) * capacity);
		for (int i = 0; i < capacity; i++) {
			OFS_debug << buffer[i] << std::endl;
		}
		current_size = 0;
	}
}
