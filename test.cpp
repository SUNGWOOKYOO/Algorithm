#include <iostream>
#include <iomanip>
using namespace std;

void func() {
	static int a = 0;
	a++;
	cout << a << setw(5);
}

void main() {
	for (int i = 0; i < 10; ++i) {
		func();
	}cout << endl;
}