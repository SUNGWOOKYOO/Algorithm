#include "misc.h"

#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::cout;
using std::endl;
using std::stringstream;

void mad() {
	throw std::exception();
}

void write_array(string filename, int arr[], int len) {
	{
		stringstream ss;
		ss << "output_binary/" << filename;
		ofstream OFS(ss.str(), ios::binary);
		if (!OFS.is_open()) {
			cout << "failed to open output file" << endl;
			cout << "make sure that the directory \""<< ss.str() << "\" exists \n"
					<< endl;
			mad();
		}
		OFS.write((char*) arr, sizeof(int) * len);
		OFS.close();
	}
	{
		stringstream ss;
		ss << "output_debug/" << filename;
		ofstream OFS(ss.str());
		if (!OFS.is_open()) {
			cout << "failed to open output file" << endl;
			cout << "make sure that the directory \"" << ss.str() << "\" exists \n"
				<< endl;
			mad();
		}
		for (int j = 0; j < len; ++j)
			OFS << arr[j] << endl;
		OFS.close();
	}
}

void gen_data(string filename, int size) {
	int range = size;
	int x;

	ofstream out(filename, ios::binary);
	for (int i = 0; i < size; ++i) {
		x = std::rand() % range;
		// cout << x << endl;
		out.write((char*) &x, sizeof(int));
	}
	out.close();
}
