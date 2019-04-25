#include <iostream>
using namespace std;

// TODO
void get_pointers1(int*& _p1, int*& _p2, int* pa, int* pb) {
	_p1 = pa;
	_p2 = pb;
}
void get_pointers2(int*& _p1, int*& p2, int& c, int&d) {
	p1 = &c;
	p2 = &d;
}

// !!! DO NOT MODIFY THE MAIN FUNCTION !!!
int main() {
	int *p1, *p2;
	int a, b, c, d;

	// By plugging a vlaue into pointer, we can assign a,b 
	get_pointers1(p1, p2, &a, &b);
	cin >> *p1 >> *p2;
	cout << a << " " << b << endl;

	get_pointers2(p1, p2, c, d);
	cin >> *p1 >> *p2;
	cout << c << " " << d << endl;
}
// !!! DO NOT MODIFY THE MAIN FUNCTION !!!
