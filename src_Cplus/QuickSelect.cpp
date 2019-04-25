#include <iostream>
#include <ctime>
using namespace std;

void swap(int* a, int i, int j) {
	cout << "swap " << i << "," << j << endl;
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

int partition(int* A, int p, int r) {
	// radom choose [p,r-1]
	int randN = rand() % (p - r) + p;
	cout << "randN: " << randN << endl;
	swap(A, randN, r);
	int X = A[r];
	cout << "pivot: " << X << endl;

	int i = p - 1;
	for (int j = p; j < r; ++j) {
		if (A[j] < X) {
			i = i + 1;
			swap(A, i, j);
		}
	}
	swap(A, i + 1, r);

	return i + 1;
}

int QuickSelect(int *A, int p, int r, int i) {
	if (p == r)
		return A[p];
	int q = partition(A, p, r);
	for (int i = 0; i < 12; ++i) {
		cout << A[i] << " ";
	}cout << endl;

	int k = q - p + 1;
	cout << "q, k:  " <<q<<","<<k << endl;

	if (i == k) {
		cout << q << endl;
		cout << "i==k"<<endl;
		return A[q];
	}
	else if (i < k) {
		cout << "Quickselect(" << p << "," << q-1 << ", " << i << ")" << endl;
		return QuickSelect(A, p, q - 1, i);
	}
	else {
		cout << "Quickselect(" << q + 1 << "," << r << ", " << i - k << ")" << endl;
		return QuickSelect(A, q + 1, r, i - k);
	}
}int main() {
	int A[] = {3,2,1,6,13,5,12,15,11,10,4,9};
	int n = std::size(A);
	srand((unsigned int)time(0));

	for (int i = 0; i < n; ++i) {
		cout << A[i] << " ";
	}cout << endl;

	int i;
	
	cin >> i;
	if (i <= n) {
		cout << "start!" << endl;
		cout << "Quickselect(0,"<<n-1<<","<<i<<")" << endl;
		cout << "result: " << QuickSelect(A, 0, n-1, i) << endl;
	}
	
	for (int i = 0; i < n; ++i) {
		cout << A[i] << " ";
	}cout << endl;

	return 0;
}