#include <iostream>
using namespace std;

// recursive version
int BS1(int *a, int i, int j, int k) {
	if (i == j) {
		if (a[i] == k) return i;
		else return -1;
	}
	int mid = i + ((j - i) >> 1);
	if (a[mid] < k)
		return BS1(a, mid + 1, j, k);
	else if (a[mid] > k)
		return BS1(a, i, mid - 1, k);
	else 
		return mid;
}

// iterative version 
int BS2(int *a, int n, int k) {
	int i = 0;
	int j = n - 1;
	int mid = 0;
	// suppose that a is a sorted array
	while (i<=j) { // when i>j can be satisfied, the loop will end
		mid = i + ((j - i) >> 1); // i + (j - i)right-shifted by 1
		if (a[mid] == k) // this case should be the top of the cases.
			return mid;
		else if (a[mid] > k)
			j = mid - 1;
		else if (a[mid] < k)
			i = mid + 1;
	}

	return -1;
}

int main() {
	int a[] = { 1,3,5,8,9,13,15,17 };
	cout << BS1(a, 0, 7, 17)<<endl;
	cout << BS2(a, 8, 17) << endl;
	return 0;
}