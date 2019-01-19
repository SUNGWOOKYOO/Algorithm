#include<iostream>
#include<string>
using namespace std;

int lcs_aux(string& x, string& y, int** lcs, int** dir, int i, int j) {
	// TODO
}

void print_lcs(string &x, string &y, int **lcs, int **dir, int i, int j) {
	// TODO
}

void lcs(string& x, string& y) {
	int m = x.length();
	int n = y.length();
	int** lcs = new int*[m];
	int** dir = new int*[m];
	for (int i = 0; i < m; ++i) {
		lcs[i] = new int[n];
		dir[i] = new int[n];
		for (int j = 0; j < n; ++j) {
			lcs[i][j] = -1;
		}
	}
	lcs_aux(x, y, lcs, dir, m - 1, n - 1);
	print_lcs(x, y, lcs, dir, m - 1, n - 1);
}

int main() {
	string x, y;
	getline(cin, x);
	getline(cin, y);
	lcs(x, y);
	return 0;
}