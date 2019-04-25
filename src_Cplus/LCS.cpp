#include<iostream>
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;

void print_lcs(string &x, string &y, int **c, int i, int j) {
	// TODO
	if (i == 0 || j == 0)
		return;

	if (x[i - 1] == y[j - 1]) {
		print_lcs(x, y, c, i - 1, j - 1);
		cout << x[i - 1];
	}
	else {
		if (c[i - 1][j] > c[i][j - 1])
			print_lcs(x, y, c, i - 1, j);
		else {
			print_lcs(x, y, c, i, j - 1);
		}
	}
}

int lcs(string& x, string& y) {
	int m = x.length();
	int n = y.length();
	int** c = new int*[m+1];
	int** dir = new int*[m];
	for (int i = 0; i < m+1; ++i) {
		c[i] = new int[n+1];
		dir[i] = new int[n];
		for (int j = 0; j < n+1; ++j) {
			c[i][j] = -1;
		}
	}

	for (int i = 0; i < m + 1; ++i) {
		c[i][0] = 0;
	}
	for (int j = 0; j < n + 1; ++j) {
		c[0][j] = 0;
	}

	for (int i = 1; i < m + 1; ++i) {
		for (int j = 1; j < n + 1; ++j) {
			if (x[i - 1] == y[j - 1])
				c[i][j] = c[i - 1][j - 1] + 1;
			else
				c[i][j] = max(c[i - 1][j], c[i][j - 1]);
		}
	}

	int result = c[m][n];
	print_lcs(x, y, c, m, n);
	cout << endl;
	
	return result;
}

int lookup(string& x, string& y, int** c, int i, int j) {
	//cout << "lookup(" << i << "," << j << ")" << endl;
	if (c[i][j] >= 0)
		return c[i][j];
	if (i == 0 || j == 0) {
		c[i][j] = 0;
		return c[i][j];
	}

	// i > 0 or j > 0
	if (x[i - 1] == y[j - 1]) {
		c[i][j] = lookup(x, y, c, i - 1, j - 1) + 1;
		return c[i][j];
	}
	else {
		c[i][j] = max(lookup(x, y, c, i - 1, j), lookup(x, y, c, i, j - 1));
		return c[i][j];
	}
}

int lcs_recursive(string& x, string& y) {
	int m = x.length();
	int n = y.length();
	int** c = new int*[m + 1];
	for (int i = 0; i < m+1; ++i) {
		c[i] = new int[n + 1];
	}
	for (int i = 0; i < m + 1; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			c[i][j] = -(1e+3);
		}
	}
	int result = lookup(x, y, c, m, n);
	/*
	for (int i = 0; i < m + 1; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			cout << c[i][j] << setw(10);
		}cout << endl;
	}
	*/
	
	for (int i = 0; i < m + 1; ++i) {
		delete[]c[i];
	}
	delete[] c;

	return result;
}

int main() {
	string x, y;
	getline(cin, x);
	getline(cin, y);
	cout << "BottomUp_result: " << lcs(x, y) << endl;
	cout << "TopDown_result: "<< lcs_recursive(x, y) << endl;
	return 0;
}