#include <iostream>
#include <string>
#include <fstream>
#include <tuple>
// #include <algorithm>
using namespace std;

auto max_subarray(int a[], int length) {
	int start = 0, end = 0;
	int max_sum = -1e8;

	// implement here
	int n = length;

	max_sum = 0;
	int this_sum = 0;
	for (int j = 0; j < n; ++j) {
		this_sum += a[j];
		// max_sum = max(max_sum, this_sum);
		// if (this_sum < 0) this_sum = 0;
		if (this_sum > max_sum) {
			max_sum = this_sum;
			end = j;
		}
		else if (this_sum < 0) {
			this_sum = 0;
			start = j + 1;
		}

	}

	return make_tuple(max_sum, start, end);
}

int main(int argc, char *argv[]) {
	// get input
	int length;
	cin >> length;

	int *arr = new int[length];

	for (int i = 0; i < length; i++) {
		cin >> arr[i];
	}

	// maximum range sum
	auto sum_tup = max_subarray(arr, length);


	// output result
	int sum, start, end;
	tie(sum, start, end) = sum_tup;

	cout << "Start : " << start << endl;
	cout << "End : " << end << endl;
	cout << "Subarray : ";
	for (int i = start; i <= end; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << "Max sum : " << sum << endl;

	// memory deallocation
	delete[] arr;

	return 0;
}