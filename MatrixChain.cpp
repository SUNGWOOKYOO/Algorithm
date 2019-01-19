#include <iostream>
#include <algorithm>
#include <array>
#include <iomanip>
using namespace std;

// top down 
/* p's index starts from 0 to n-1
  so, we need to set (m[1,1] ~ m[n,n]) base cases
*/
int lookup(int*, int**, int, int);
int MatrixChain(int *p, int n) {
	int** m = new int*[n+1];
	for (int i = 0; i < n + 1; ++i) {
		m[i] = new int[n + 1];
	}
	for (int i = 0; i < n + 1; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			m[i][j] = 1e+8;
		}
	}
	int result = lookup(p, m, 1, n);

	for (int i = 0; i < n + 1; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			cout << m[i][j] << setw(10);
		}
		cout << endl;
	}

	for (int i = 0; i < n + 1; ++i) {
		delete[] m[i];
	}
	delete[] m;

	return result;
}

int lookup(int* p, int** m, int i, int j) {
	if (m[i][j] <= 1e+7) return m[i][j];
	if (i == j) {
		//cout << "base case" << endl;
		m[i][j] = 0;
		return 0;
	}
	//cout << "not base case: m[" << i << "," << j << "] is called " <<endl;
	int q = 1e+8;
	for (int k = i; k < j; ++k) {
		q = min(q, lookup(p, m, i, k) + lookup(p, m, k + 1, j) + p[i - 1] * p[k] * p[j]);
	}
	//cout << "m[" << i << "," << j << "] = " << q << endl;
	m[i][j] = q;
	return q;
}

// bottom up
int MatrixChain2(int *p, int n) {
	int **m = new int*[n + 1];
	for (int i = 0; i < n + 1; ++i) {
		m[i] = new int[n + 1];
	}

	for (int i = 0; i < n + 1; ++i) {
		m[i][i] = 0;
	}

	for (int l = 2; l < n + 1; ++l) {
		for (int i = 1; i < n - l + 2; ++i) {
			int j = i + l - 1;
			int q = 1e+8;
			for (int k = i; k < j; ++k) {
				q = min(q, m[i][k] + m[k + 1][j] + p[i - 1]*p[k]*p[j]);
			}
			m[i][j] = q;
		}
	}

	for (int i = 0; i < n + 1; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			cout << m[i][j] << setw(10);
		}
		cout << endl;
	}

	int result = m[1][n];

	for (int i = 0; i < n + 1; ++i) {
		delete[] m[i];
	}
	delete[] m;

	return result;
}

int main() {
	cout << "Matrix parenthesization problem" << endl;
	int p[] = { 30,35,15,5,10,20,25 };
	cout << "result: "<<MatrixChain(p, (std::size(p)-1) ) << endl;
	cout << "result2: " << MatrixChain2(p, (std::size(p) - 1)) << endl;
	// expected result: 15125

	return 0;
}