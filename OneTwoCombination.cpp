#include <iostream>
using namespace std;

// Bottom up approach 
int Count(int n) {
	int* a1 = new int[n + 1];	// 1 + {a1[n-1] + a2[n-1]}
	int* a2 = new int[n + 1];	// 2 + {a[n-2]}
	// base case 
	a1[0] = 1;
	a1[1] = 1;
	a2[1] = 0;
	for (int j = 2; j < n + 1; ++j) {
		a1[j] = a1[j - 1] + a2[j - 1];
		a2[j] = a1[j - 2];
		cout << j << " col Debug: "<< a1[j] << " " << a2[j] << endl;
	}

	return a1[n] + a2[n];
}

int main() {
	int n;
	cout << "Enter n: ";
	cin >> n;
	int result = Count(n); // Time Complexity T(n) = O(n)

	cout << "Result: "<< result;
}