#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <limits>
#include <chrono>
using namespace std;

// 0 approach: naive(all pair) O(n^2)
int distance(int* a, int i, int j) {
	if (i == j)
		return std::numeric_limits<int>::max();
	return std::abs(a[j] - a[i]);
}
int dist_naive(int* a, int n) {
	int minv = std::numeric_limits<int>::max();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			minv = std::min(minv, distance(a, i, j));
		}
	}
	return minv;
}

// 1 approach: Incremental O(n^2)
int dist_incremental(int* a, int n) {
	int minv = std::numeric_limits<int>::max();;
	for (int j = 1; j < n; ++j) {
		for (int i = 0; i < j; ++i) {
			minv = min(minv, std::abs(a[j] - a[i]));
		}
	}
	return minv;
}

// 2 approach: divide and conquer O(n^2)
int dist_DC(int* a, int i, int j) {
	//cout << "dist_DC(" << i << "," << j << ")" << endl;
	if (i >= j)
		return std::numeric_limits<int>::max();
	if (j - i == 1)
		return std::abs(a[j] - a[i]);
	int mid = i + ((j - i) >> 1);
	int left = dist_DC(a, i, mid);
	int right = dist_DC(a, mid + 1, j);
	int cross = std::numeric_limits<int>::max();
	for (int p = i; p <= mid; ++p) {
		for (int r = mid + 1; r <= j; ++r) {
			cross = std::min(cross, std::abs(a[p] - a[r]));
		}
	}
	return min(min(right, left), cross);
}
// 3 approach: sort and dp O(nlogn)
void swap(int* a ,int i, int j) {
	int tmp = a[j];
	a[j] = a[i];
	a[i] = tmp;
}

int partition(int* a, int p, int r) {
	int pivot = a[r];
	int i = p - 1;
	for (int j = p; j < r; ++j) {
		if (a[j] < pivot) {
			i = i + 1;
			swap(a, i, j);
		}
	}
	swap(a, i + 1, r);
	return i + 1;
}

void Quicksort(int* a, int p, int r) {
	//cout << "qick(" << p << "," << r << ")" << endl;
	if (p >= r) return;
	int q = partition(a, p, r);
	Quicksort(a, p, q - 1);
	Quicksort(a, q + 1, r);
}

int lookup(int *a, int* d, int  i) {
	//cout << "lookup " << i << endl;
	if (d[i] < std::numeric_limits<int>::max()) {
		return d[i];
	}
	if (i == 0) {
		d[i] = 0;
		return std::numeric_limits<int>::max();;
	}
	if (i == 1) {
		d[1] = a[1] - a[0];
		return d[1];
	}
	d[i] = min(lookup(a, d, i - 1), std::abs(a[i] - a[i - 1]));
	return d[i];
}

int dist(int *a, int n) {
	// preprocessing O(nlogn)
	//cout << "a: ";
	Quicksort(a, 0, n-1);
	
	/*
	cout << "a: ";
	for (int i = 0; i < n; ++i) {
		cout << a[i] << " ";
	}cout << endl;
	*/

	int *d = new int[n];
	for (int i = 0; i < n; i++) {
		d[i] = std::numeric_limits<int>::max();
	}

	/*
	for (int i = 0; i < n; ++i) {
		cout << d[i] << " ";
	}cout << endl;
	*/

	// DP O(n)
	int result = lookup(a, d, n - 1);
	
	/*
	cout << "d: ";
	for (int i = 0; i < n; ++i) {
		cout << d[i] << " ";
	}cout << endl;
	*/

	delete[]d;

	return result;
}

int dist2(int* a, int n) {
	int* d = new int[n];
	d[0] = std::numeric_limits<int>::max();
	d[1] = std::abs(a[1] - a[0]);
	for (int i = 2; i < n; ++i) {
		d[i] = min(d[i - 1], a[i] - a[i - 1]);
	}
	int result = d[n - 1];
	delete[]d;
	return result;
}

int main() {
	//int a[7] = { 1,19,15,13,5,30,59 };
	//int *p = a;
	/*
	Quicksort(p, 0, 6);
	for (int e: a) {
		cout << e << " ";
	}cout << endl;
	*/

	//int n;
	//cout << "Enter Input size: ";
	//cin >> n;
	//int *p = new int[n];

	//srand(unsigned int(time(0)));
	//
	//for (int i = 0; i < n; ++i) {
	//	// [-5000, 5000] random 
	//	p[i] = rand() % (5000 - (-5000) + 1) - 5000 ;
	//	cout << p[i] << " ";
	//}cout << endl;

	freopen("input.txt", "r", stdin);
	cout << "Enter input size n : ";
	int n;
	cin >> n;
	cout << endl;
	int* p = new int[n];
	cout << "Enter input seq: ";
	for (int i = 0; i < n; ++i) {
		cin >> p[i];
	}cout << endl;
	/*
	input.txt
	7
	1 19 15 13 5 30 59
	*/

	auto start = chrono::system_clock::now();
	cout << "	>> 0 approach result : " << dist_naive(p, n) << endl;
	auto end = chrono::system_clock::now();
	auto time = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "	>> time : " << time.count() << endl;

	start = chrono::system_clock::now();
	cout << "	>> 1 approach result : " << dist_incremental(p, n) << endl;
	end = chrono::system_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "	>> time : " << time.count() << endl;

	start = chrono::system_clock::now();
	cout << "	>> 2 approach result : " << dist_DC(p, 0, n - 1) << endl;
	end = chrono::system_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "	>> time : " << time.count() << endl;

	start = chrono::system_clock::now();
	cout << "	>> 3-1 approach result : " << dist(p, n) << endl;
	end = chrono::system_clock::now();
	time = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "	>> time : " << time.count() << endl;

	start = chrono::system_clock::now();
	cout << "	>> 3-2 approach result : " << dist2(p, n) << endl;
	end = chrono::system_clock::now();

	time = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "	>> time : " << time.count() << endl;

	return 0;
}