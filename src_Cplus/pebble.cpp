#include <iostream>
#include <array>
#include <algorithm>
#include <iomanip>
using namespace std;
int pebble(int** w, int n) {
	int m = 3;
	int **c = new int*[m+1];
	for (int i = 0; i < m + 1; ++i) {
		c[i] = new int[n];
	}

	for (int i = 0; i < m + 1; ++i) {
		for (int j = 0; j < n; ++j) {
			c[i][j] = -1000;
		}
	}

	c[0][0] = w[0][0];
	c[1][0] = w[1][0];
	c[2][0] = w[2][0];
	c[3][0] = w[0][0] + w[2][0];

	for (int i = 1; i < n; ++i) {
		c[0][i] = max(c[1][i - 1], c[2][i - 1]) + w[0][i];
		c[1][i] = max(max(c[0][i - 1], c[2][i - 1]), c[3][i - 1]) + w[1][i];
		c[2][i] = max(c[0][i - 1], c[1][i - 1]) + w[2][i];
		c[3][i] = c[1][i - 1] + w[0][i] + w[2][i];
	}
	int result = max(max(c[0][n - 1], c[1][n - 1]), max(c[2][n - 1], c[3][n - 1]));

	cout << "c[][] : " << endl;
	for (int i = 0; i < m + 1; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << setw(10) << c[i][j];
		}cout << endl;
	}
	
	
	for (int i = 0; i < m+1; ++i) {
		delete[]c[i];
	}
	delete c;
	
	return result;
}
int main() {
	int n;
	cin >> n;

	int m = 3;

	int** w = new int*[m];
	for (int i = 0; i < m; ++i) {
		w[i] = new int[n];
	}

	/* [input]
		8
		6 7 12 -5 5 3 11 3
		-8 10 14 9 7 13 8 5
		11 12 7 4 8 -2 9 4
	*/

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> w[i][j];
		}
	}

	cout << "w[][] : " << endl;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << setw(10)<< w[i][j];
		}cout << endl;
	}

	cout << "result: " << pebble(w, n) << endl;
	// expected result : 106
	
	for (int i = 0; i < m; ++i) {
		delete[]w[i];
	}
	delete w;
	
}