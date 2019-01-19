#include <iostream>
using namespace std;

int min(int x, int y) {
	/*
	You can use this function
	*/
	if (x < y) return x;
	else return y;
}

void backtracking(int i, int j, int **l) {
	if (l[i][j - 1] == 1 && j > 1) {
		backtracking(0, j - 1, l);
		//cout << j << "th path ";
		cout << "1  ";
	}
	else if (l[i][j - 1] == 2 && j > 1) {
		backtracking(1, j - 1, l);
		//cout << j << "th path ";
		cout << "2  ";
	}
	else {
		cout << "start!   ";
	}
}

int main() {
	int numOfstation;
	cin >> numOfstation;
	int e1, e2, x1, x2;
	int * a1 = new int[numOfstation];
	int * a2 = new int[numOfstation];
	int * t1 = new int[numOfstation - 1];
	int * t2 = new int[numOfstation - 1];
	cin >> e1;
	for (int i = 0; i < numOfstation; i++)
		cin >> a1[i];
	cin >> x1;

	cin >> e2;
	for (int i = 0; i < numOfstation; i++)
		cin >> a2[i];
	cin >> x2;

	for (int i = 0; i < numOfstation - 1; i++)
		cin >> t1[i];
	for (int i = 0; i < numOfstation - 1; i++)
		cin >> t2[i];

	/*

	Implement here

	*/
	int **f = new int*[2];
	for (int i = 0; i < 2; ++i) {
		f[i] = new int[numOfstation];
	}

	int **l = new int*[2];
	for (int i = 0; i < 2; ++i) {
		l[i] = new int[numOfstation];
	}

	f[0][0] = e1 + a1[0];
	f[1][0] = e2 + a2[0];
	for (int j = 1; j < numOfstation; j++) {
		if (f[0][j - 1] + a1[j] <= f[1][j - 1] + t2[j - 1] + a1[j]) {
			f[0][j] = f[0][j - 1] + a1[j];
			l[0][j] = 1;
		}
		else {
			f[0][j] = f[1][j - 1] + t2[j - 1] + a1[j];
			l[0][j] = 2;
		}
		if (f[1][j - 1] + a2[j] <= f[0][j - 1] + t1[j - 1] + a2[j]) {
			f[1][j] = f[1][j - 1] + a2[j];
			l[1][j] = 2;
		}
		else {
			f[1][j] = f[0][j - 1] + t1[j - 1] + a2[j];
			l[1][j] = 1;
		}
	}

	int optimalF = 0;
	int optimalL = 0;
	if (f[0][numOfstation - 1] + x1 <= f[1][numOfstation - 1] + x2) {
		optimalF = f[0][numOfstation - 1] + x1;
		optimalL = 1;
	}
	else {
		optimalF = f[1][numOfstation - 1] + x2;
		optimalL = 2;
	}

	cout << "OptimalF : " << optimalF << endl;
	cout << "OptimalL : " << optimalL << endl;
	cout << "path Info: " << endl;
	for (int j = 1; j < numOfstation; ++j) {
		cout << l[0][j] << " ";
	}
	cout << endl;
	for (int j = 1; j < numOfstation; ++j) {
		cout << l[1][j] << " ";
	}
	cout << endl;

	// backtracking 
	cout << "backtracking ... : " << endl;
	backtracking(optimalL - 1, numOfstation, l);
	cout << optimalL << endl;

	delete[] a1;
	delete[] a2;
	delete[] t1;
	delete[] t2;
	return 0;
}