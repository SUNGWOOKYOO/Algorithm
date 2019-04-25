#include<iostream>
using namespace std;

// Divide and Conquer 
int FindLastidx2(int *a, int k, int i, int j);
int FindLastidx(int *a, int k, int i, int j);

int* Findfreq(int *a, int n, int M) {
	int* F = new int[M+1];
	int prev_idx = -1;
	int last_idx = 0;
	for (int k = 0; k < (M+1); ++k) {
		last_idx = FindLastidx(a, k, 0, (n - 1));
		F[k] = last_idx - prev_idx;
		prev_idx = last_idx;
	}
	return F;
}

void Printfreq(int *a, int n, int M) {
	int prev_idx = -1;
	int last_idx = 0;
	while(last_idx < n-1) {
		last_idx = FindLastidx(a, a[prev_idx + 1], 0, (n - 1));
		cout << "F["<< a[prev_idx + 1] << "] = " << last_idx - prev_idx << endl;
		prev_idx = last_idx;
	}
}

int FindLastidx(int *a, int k, int i, int j) {
	if (i == j) {
		if (a[i] == k) return i;
		else return (i-1);
	}
	int mid = (i + j) / 2;
	if (a[mid] <= k) return FindLastidx(a, k, mid + 1, j);
	else return FindLastidx(a, k, i, mid);
}

// 반드시 k 가 a안에 존재해야한다. 
int FindLastidx2(int *a, int k, int i, int j) {
	if (i == j) return i;

	int mid = (i + j) / 2;

	if (a[mid] < k) return FindLastidx2(a, k, mid + 1, j);
	else if (a[mid] > k) return FindLastidx2(a, k, i, mid - 1);
	else { 
		if (a[mid + 1] == k) return FindLastidx2(a, k, mid + 1, j);
		else return mid;
	}
}

int main() {
	cout << "Enter input size n : ";
	int n;
	cin >> n;
	int* a = new int[n];
	cout << "Enter input seq: ";
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	int M = a[n - 1];

	
	// Find frequency
	// Time Complexity T(n) = O(Mlog(n))

	int* F = Findfreq(a, n, M);
	for (int i = 0; i < (M+1); ++i) {
		cout<< F[i];
		if (i != M) {
			cout << " ";
		}
	}
	cout << endl;
	Printfreq(a, n, M);
	
	/*
	int prev_idx = -1;
	int last_idx = 0;
	while (last_idx < n - 1) {
		last_idx = FindLastidx2(a, a[prev_idx + 1], 0, n - 1, n);
		cout << "F[" << a[prev_idx + 1] << "] = " << last_idx - prev_idx << endl;
		prev_idx = last_idx;
	}
	*/

	return 0;
}
