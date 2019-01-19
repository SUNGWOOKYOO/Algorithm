#include <iostream>

using namespace std;


class MyInteger {
private:
	int data;
public:
	MyInteger(int num = 0) :data(num) {}

	MyInteger &operator+(const int i) {
		data += i;
		return *this;
	}
	friend MyInteger& operator+(const int, MyInteger&);
	friend ostream& operator<<(ostream&, const MyInteger&);
};

MyInteger& operator+(const int num, MyInteger& my) {
	my.data += num;
	return my;
}

ostream& operator<<(ostream& out, const MyInteger& my) {
	out << my.data << endl;
	return out;
}

/* ================================================================================================================================
						Complex class
================================================================================================================================ */
class Complex {
private:
	int int_part;
	int img_part;
public:
	Complex() {}
	Complex(int _int, int _img) :int_part(_int), img_part(_img) {}
	Complex & operator+(const Complex right) {
		int_part += right.int_part;
		img_part += right.img_part;
		return *this;
	}

	friend istream& operator>>(istream&, Complex&);
	friend ostream& operator<<(ostream&, const Complex&);
};

istream& operator>>(istream& in, Complex& com) {
	in >> com.int_part;
	in.ignore(1);
	in >> com.img_part;
	return in;
}

ostream& operator<<(ostream& out, const Complex& com) {
	out << com.int_part;
	out << " + ";
	cout << com.img_part << "i";
	return out;
}

int main() {
	cout << "======================= Integer ==========================" << endl;
	MyInteger a(100);
	a = a + 10;
	cout << a << endl;
	a = 10 + a;
	cout << a << endl;

	cout << "======================= Complex ==========================" << endl;
	Complex c1;
	Complex c2;
	cin >> c1;
	cin >> c2;
	cout << c1 + c2 << endl;
	return 0;
}