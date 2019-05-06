#include<iostream>
using namespace std;

// naive algorithm : O(N+M)
int* Findfreq_naive(int* a, int N, int M) {
	int* F = new int[M+1];
	for (int i = 0; i <= M; ++i) {
		F[i] = 0;
	}
	for (int i = 0; i < N; ++i) {
		F[a[i]] += 1;
	}
	return F;
}

// Divide and Conquer 
int FindLastidx2(int *a, int k, int i, int j);
int FindLastidx(int *a, int k, int i, int j);

int* Findfreq(int *a, int n, int M) {
	int* F = new int[M+1];
	int prev_idx = -1;
	int last_idx = 0;
	for (int k = 0; k <= M; ++k) {
		last_idx = FindLastidx(a, k, 0, (n - 1));
		F[k] = last_idx - prev_idx;
		prev_idx = last_idx;
	}
	return F;
}

void Printfreq(int *a, int n, int M) {
	int prev_idx = -1;
	int last_idx = 0;
	while(last_idx < n-1) {
		last_idx = FindLastidx(a, a[prev_idx + 1], 0, (n - 1));
		cout << "F["<< a[prev_idx + 1] << "] = " << last_idx - prev_idx << endl;
		prev_idx = last_idx;
	}
}

int FindLastidx(int *a, int k, int i, int j) {
	if (i == j) {
		if (a[i] == k) return i;
		else return (i-1);
	}
	int mid = (i + j) / 2;
	if (a[mid] <= k) return FindLastidx(a, k, mid + 1, j);
	else return FindLastidx(a, k, i, mid);
}

// 반드시 k 가 a안에 존재해야한다. 
int FindLastidx2(int *a, int k, int i, int j) {
	if (i == j) return i;

	int mid = (i + j) / 2;

	if (a[mid] < k) return FindLastidx2(a, k, mid + 1, j);
	else if (a[mid] > k) return FindLastidx2(a, k, i, mid - 1);
	else { 
		if (a[mid + 1] == k) return FindLastidx2(a, k, mid + 1, j);
		else return mid;
	}
}

// simple Divide and conquer algorithm
void DC_count(int* a, int* f, int i, int j) {
	//cout << "DC_count(a,F,"<< i <<","<< j <<");" << endl;
	if (a[i] == a[j]) {
		f[a[i]] += j - i + 1;
		return;
	}
	//int mid = i + (j - i) >> 1;
	int mid = (i + j) / 2;
	DC_count(a, f, i, mid);
	DC_count(a, f, mid + 1, j);
}
auto Findfreq_final(int* a, int n, int M) {
	auto F = new int[M+1];
	for (int i = 0; i <= M; ++i) {
		F[i] = 0;
	}
	DC_count(a, F, 0, n - 1);
	return F;
}

int main() {
	// If you wanna use below line, 
	// you should add input.txt into your project>resource file>input.txt
	freopen("input.txt", "r", stdin);
	cout << "Enter input size n : ";
	int n;
	cin >> n;
	cout << endl;
	int* a = new int[n];
	cout << "Enter input seq: ";
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	int M = a[n - 1];
	cout << endl;

	cout << "naive approach: ";
	int* o = Findfreq_naive(a, n, M); //size M 
	for (int i = 0; i <= M; ++i) {
		cout << o[i] << " ";
	}cout << endl;

	// Find frequency
	// Time Complexity T(n) = O(Mlog(n))
	cout << "Divide and conquer1: ";
	int* F = Findfreq(a, n, M);
	for (int i = 0; i < (M+1); ++i) {
		cout<< F[i];
		if (i != M) {
			cout << " ";
		}
	}
	cout << endl;
	Printfreq(a, n, M);
	
	cout << "Divide and conquer2: " << endl;
	int prev_idx = -1;
	int last_idx = 0;
	while (last_idx < n - 1) {
		last_idx = FindLastidx2(a, a[prev_idx + 1], 0, n - 1);
		cout << "F[" << a[prev_idx + 1] << "] = " << last_idx - prev_idx << endl;
		prev_idx = last_idx;
	}
	
	cout << "final Divide and conquer approach: "; 
	int* o2 = Findfreq_final(a, n, M);
	for (int i = 0; i <= M; ++i) {
		cout << o2[i] << " ";
	}cout << endl;

	return 0;
}
