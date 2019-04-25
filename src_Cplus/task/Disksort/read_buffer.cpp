#include "read_buffer.h"

#include <iostream>

ReadBuffer::ReadBuffer(int capacity, string filename) :
		capacity(capacity), curr_pos(capacity), IFS(filename, std::ios::binary) {
	buffer = new int[capacity];
	// IFS.open(filename, std::ios::binary);
}

ReadBuffer::~ReadBuffer() {
	delete[] buffer;
	IFS.close();
}

bool ReadBuffer::read(int &x) {
	if (curr_pos >= capacity) {
		if (IFS.read((char*) buffer, sizeof(int) * capacity))
			curr_pos = 0;
		else
			return false;
	}
	x = buffer[curr_pos];
	curr_pos++;
	return true;
}
/*
bool ReadBuffer::eof() {
	return (IFS.eof() && curr_pos >= capacity);
}
*/
