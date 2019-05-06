#include <iostream>
using namespace std;

int CountInversion_naive(int* a, int n) {
	int count = 0;
	for (int i = 0; i < n-1; ++i) {
		for (int j = i+1; j < n; ++j) {
			if (a[i] > a[j]) {
				count += 1;
			}
		}
	}
	return count;
}

void merge(int* a, int& count, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	// Let L[0 .. n1] and R[0 ..n2] be new arrays
	int *L = new int[n1 + 1];
	int *R = new int[n2 + 1];
	for (int i = 0; i < n1; i++)
	{
		L[i] = a[p + i];
	}
	for (int j = 0; j < n2; j++)
	{
		R[j] = a[q + j + 1];
	}
	L[n1] = numeric_limits<int>::max();
	R[n2] = numeric_limits<int>::max();

	int i = 0;
	int j = 0;
	for (int k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			a[k] = L[i];
			i += 1;
		}
		else
		{
			a[k] = R[j];
			j += 1;
			// if a[i] > a[j], we get into this field
			if (i != n1)
				count += n1 - i;
		}
	}
	delete[]L;
	delete[]R;
}

void merge_sort(int* a, int& count, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		merge_sort(a, count, p, q);
		merge_sort(a, count, q + 1, r);
		merge(a, count, p, q, r);
	}
}

int CountInversion_DC(int* a, int n) {

	// copy: O(n)
	int* tmp = new int[n];
	for (int i = 0; i < n; ++i) {
		tmp[i] = a[i];
	}

	int count = 0;
	merge_sort(tmp, count, 0, n - 1);
	for (int i = 0; i < n; ++i) {
		cout << tmp[i] << " ";
	}cout << endl;

	return count;
}

int main() {
	freopen("input.txt", "r", stdin);
	cout << "Enter input size n : ";
	int n;
	cin >> n;
	cout << endl;
	int* a = new int[n];
	cout << "Enter input seq: ";
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}cout << endl;

	cout << "naive approach: ";
	cout << CountInversion_naive(a, n) << endl;

	// https://www.geeksforgeeks.org/counting-inversions/
	cout << "divide conquer: ";
	cout << CountInversion_DC(a, n) << endl;

	return 0;
}