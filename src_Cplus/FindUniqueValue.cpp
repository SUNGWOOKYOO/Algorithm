#include<iostream>
using namespace std;

// program methology 2018 midterm Q2. 
template<typename T>
T find(T* a, int p, int r) {
	int q = (p + r) / 2;
	if (p == q)
		return a[p];
	// make sure that a[p..q] size is always odd 
	if ((q - p + 1) % 2)
		q -= 1;
	// then, if a[q-1] == a[q], unique value always exist in a[p..q] 
	if (a[q - 1] == a[q])
		find(a, q + 1, r);
	else
		find(a, p, q - 1);
}

void main() {
	// input array is sorted and has an unique value in the array, else things are double occurred consecutively.
	// what is the unique number? find the unique value in the given array
	int a[] = { 1,1,2,2,3,4,4,5,5,6,6,7,7,8,8 };
	int b[] = { 10,10,17,17,18,18,19,19,21,21,23 };
	int c[] = { 1,10,10,17,17,18,18,19,19,21,21,24,24 };
	cout << find(a, 0, size(a) - 1) << endl; //3
	cout << find(b, 0, sizeof(b) / sizeof(int) - 1) << endl; //23
	cout << find(c, 0, size(c) - 1) << endl; //1
	cout << size(a) << endl; //15
	cout << sizeof(a) << endl; //60
}