# include <iostream>
using namespace std;

int naive(int* a, int n) {
	int count = 0;
	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (a[i] > a[j]) {
				count += 1;
			}
		}
	}
	return count;
}

void merge(int a[], int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	int *L = new int[n1 + 1], *R = new int[n2 + 1];

	for (int i = 0; i < n1; ++i)
		L[i] = a[p + i];
	for (int j = 0; j < n2; ++j)
		R[j] = a[q + 1 + j];
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;

	int i = 0, j = 0;
	int inv = 0;
	for (int k = p; k <= r; ++k) {
		if (L[i] <= R[j]) {
			a[k] = L[i];
			i++;
		} else {
			a[k] = R[j];
			j++;
		}
	}
	delete[] L;
	delete[] R;
}

int bs(int a[], int p, int r, int X) {
	if (p == r) {
		if (a[p] < X)
			return 1;
		else
			return 0;
	}
	int q = (p + r) / 2;
	if (a[q] < X)
		return (q - p + 1) + bs(a, q + 1, r, X);
	else
		return bs(a, p, q, X);
}

int countInv(int a[], int p, int q, int r) {
	int inv = 0;
	for (int k = p; k <= q; ++k) {
		inv += bs(a, q + 1, r, a[k]);
	}
	return inv;
}

int mergeSort(int a[], int p, int r) {
	int inv = 0;
	if (p < r) {
		int q = (p + r) / 2;
		inv += mergeSort(a, p, q);
		inv += mergeSort(a, q + 1, r);
		inv += countInv(a, p, q, r);
		merge(a, p, q, r);
	}
	return inv;
}


int main() {
	freopen("input.txt", "r", stdin);

	int n; 
	cin >> n; 
	int* a = new int[n];
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	cout << endl;

	/*for (int i = 0; i < n; ++i) {
		cout << a[i] << " ";
	}cout << endl;*/

	cout << "# of inversions naive: " << CountInversion_naive(a, n) << endl;
	cout << "# of inversions: " << mergeSort(a, 0, n - 1) << endl;

	/*for (int i = 0; i < n; ++i) {
		cout << a[i] << " ";
	}cout << endl;*/

	return 0;
}