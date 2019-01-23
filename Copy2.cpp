#include <iostream>
using namespace std;

class A {
public:
	A() { cout << "1"; }
	~A() { cout << "2"; }
	A(const A& obj) { cout << "3"; }
};
class B : A{
public:
	B() { cout << "4"; }
	~B() { cout << "5"; }
	B(const B& obj) { cout << "6"; }
};
class C : B {
public:
	C() { cout << "7"; }
	~C() { cout << "8"; }
	C(const C& obj) { cout << "9"; }
};

int main() {
	// generate an instance
	C* c1 = new C(); // expected result : 147
	cout << "\n";
	// generate and Copy an instance 
	C d(*c1); // expected result : 149
	cout << "\n";
	delete c1; // // expected result : 852
	cout << "\n";
	return 0; // expected result : 852
}