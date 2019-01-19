#include <iostream>
#include <array>
using namespace std;

int InsertionSelect(int A[], int n, int k) {
	int* F = new int[k+1];
	int i, key;
	for (int j = 1; j < n + 1; ++j) {
		if (j <= k) {
			F[j] = A[j];
			key = F[j];
			i = j - 1;
		}
		else {
			if (A[j] <= F[k]) {
				F[k] = A[j];
				key = F[k];
				i = k - 1;
			}
		}
		while (i > 0 && F[i] > key) {
			F[i + 1] = F[i];
			i = i - 1;
			F[i + 1] = key;
		}
		cout << "after..." << endl;
		for (int i = 0; i < k + 1; ++i) {
			cout << F[i] << " ";
		}cout << endl;
	}

	int result = F[k];
	delete[]F;
	return result;
}

int main(){
	int A[] = { -1,3,2,1,6,13,5,12,15,11,10,4,9 };
	int n = std::size(A) - 1;

	int k;
	cin >> k;
	if (k <= n) {
		cout << "start!" << endl;
		cout << InsertionSelect(A, n, k) << endl;
	}
	return 0;
}