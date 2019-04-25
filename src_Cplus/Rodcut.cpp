#include <stdio.h>
#include<iostream>
#include <limits>
#include <algorithm>
using namespace std;

void rodcut(int n, int *p) {
	// TODO
	int *r = new int[n + 1];
	int *s = new int[n + 1];
	r[0] = 0;
	for (int j = 1; j < n + 1; ++j) {
		int q = std::numeric_limits<int>::min();
		for (int i = 1; i < j + 1; ++i) {
			if (q < p[i] + r[j - i]) {
				q = p[i] + r[j - i];
				s[j] = i;
			}
		}
		r[j] = q;
	}
	for (int i = 1; i < n + 1; ++i) {
		cout << i << ", " << r[i] << ", " << s[i] << endl;
	}
}

int lookup(int* p, int n, int* r) {
	if (r[n] >= 0) return r[n];
	if (n == 0) return 0;
	int q = -(1e+8);
	for (int i = 1; i < n + 1; ++i) {
		//cout << "lookup(" << n - i << ")" << endl;
		q = std::max(q, p[i] + lookup(p, n - i, r));
	}
	r[n] = q;
	//cout << "r[" << n << "] = " << r[n] << endl;
	return q;
}
int rodcut2(int* p, int n) {
	int* r = new int[n + 1];
	for (int i = 0; i < n + 1; ++i) r[i] = -(1e+8);
	return lookup(p, n, r);
}

int* getprice(int n) {
	int *p = new int[n + 1];
	p[0] = 0;
	for (int i = 1; i <= n; ++i)
		cin >> p[i];
	return p;
}

int main() {
	/* input
		10
		1 5 8 9 10 17 17 20 24 30 */
	int n;
	cin >> n;
	int *p = getprice(n);
	//rodcut(n, p);
	cout << rodcut2(p, n) << endl;

	//output : r[] = 1 5 8 10 13 17 18 22 25 30
	return 0;
}