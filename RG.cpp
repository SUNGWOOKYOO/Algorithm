#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int* Linear(int* a, int n) {
	int M = a[n - 1];
	int* F = new int[M + 1];
	for (int i = 0; i <= a[n - 1]; ++i) {
		F[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		F[a[i]] = F[a[i]] + 1;
	}
	return F;
}

bool Checker(int* f1, int* f2, int M) {
	//cout << "checker start!" << endl;
	for (int i = 0; i < M; ++i) {
		if (f1[i] != f2[i]) return false;
	}
	//cout << "true" << endl;
	//cout << "checker end!" << endl;
	return true;
}

int FindLastidx(int *a, int k, int i, int j) {
	if (i == j) {
		if (a[i] == k) return i;
		else return (i - 1);
	}
	int mid = (i + j) / 2;
	if (a[mid] <= k) return FindLastidx(a, k, mid + 1, j);
	else return FindLastidx(a, k, i, mid);
}

int* Findfreq(int *a, int n) {
	int M = a[n - 1];
	int* F = new int[M + 1];
	int prev_idx = -1;
	int last_idx = 0;
	for (int k = 0; k < (M + 1); ++k) {
		last_idx = FindLastidx(a, k, 0, (n - 1));
		F[k] = last_idx - prev_idx;
		prev_idx = last_idx;
	}
	return F;
}

int* RandomGenerator(int n, int k, int p) {
	int* a = new int[n];
	a[0] = 1;
	for (int i = 1; i < n; i++) {
		if (1 == (rand() % k)) {
			a[i] = a[i - 1] + p;
		}
		else {
			a[i] = a[i - 1];
		}
	}
	return a;
}

int main() {
	int n;
	cin >> n;

	srand((unsigned int)time(NULL));
	for (int k = 2; k < 1000; ++k) {
		int* a = RandomGenerator(n, k, 1); // 1/k probability
		/*
		for (int j = 0; j < n; ++j) {
			cout << a[j] << " ";
		}
		cout << endl;
		*/

		int* f1 = Linear(a, n);
		int* f2 = Findfreq(a, n);
		//cout << Checker(f1, f2, a[n - 1]) << endl;
		if(Checker(f1, f2, a[n - 1]) == false) cout<<"False"<<endl;
		delete[]a;
		delete[]f1;
		delete[]f2;
	}
	cout << "Random1 complete! " << endl;

	for (int k = 2; k < 1000; ++k) {
		int* a = RandomGenerator(n, ((rand() % 10) + 1), 1); //random probability
		
		/*
		for (int j = 0; j < n; ++j) {
			cout << a[j] << " ";
		}
		cout << endl;
		*/

		int* f1 = Linear(a, n);
		int* f2 = Findfreq(a, n);
		//cout << Checker(f1, f2, a[n - 1]) << endl;
		//cout << "debug" << endl;
		if (Checker(f1, f2, a[n - 1]) == false) cout << "False" << endl;
		delete[]a;
		delete[]f1;
		delete[]f2;
	}
	cout << "Random2 complete!" << endl;

	for (int k = 2; k < 1000; ++k) {
		int* a = RandomGenerator(n, ((rand() % 10) + 1), (rand() % 5 + 1)); //random probability

		/*
		for (int j = 0; j < n; ++j) {
			cout << a[j] << " ";
		}
		cout << endl;
		*/

		int* f1 = Linear(a, n);
		int* f2 = Findfreq(a, n);
		//cout << Checker(f1, f2, a[n - 1]) << endl;
		//cout << "debug" << endl;
		if (Checker(f1, f2, a[n - 1]) == false) cout << "False" << endl;
		delete[]a;
		delete[]f1;
		delete[]f2;
	}
	cout << "Random3 complete!" << endl;

	return 0;
}