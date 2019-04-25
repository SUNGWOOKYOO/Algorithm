#include <iostream>
using namespace std;


class ComplexNumber {
private:
	double real;
	double imag;
public:
	// constructor
	ComplexNumber(double r = 0, double i = 0) :real(r), imag(i) {}
	ComplexNumber(const ComplexNumber& c) : real(c.real), imag(c.imag) {}

	// operater<< and operator>> for output
	friend ostream& operator <<(ostream&, const ComplexNumber&);
	friend istream& operator >>(istream&, ComplexNumber&);

	// assignment operator
	ComplexNumber& operator =(const ComplexNumber &c) {
		cout << "Operator called" << endl;
		this->real = c.real;
		this->imag = c.imag;
		return *this;
	}

	// implement the operators here
	ComplexNumber& operator +(const ComplexNumber &c) {
		this->real += c.real;
		this->imag += c.imag;
		return *this;
	}
	friend ComplexNumber& operator +(double, ComplexNumber &);

	ComplexNumber& operator -(const ComplexNumber &c) {
		this->real -= c.real;
		this->imag -= c.imag;
		return *this;
	}
	friend ComplexNumber& operator -(double, ComplexNumber &);

	ComplexNumber operator !() {
		ComplexNumber temp(this->real, this->imag);
		temp.imag = (-1) * (this->imag);
		return temp;
	}

	ComplexNumber& operator *(const ComplexNumber &c) {
		this->real = this->real*c.real - this->imag*c.imag;
		this->imag = this->real*c.imag + this->imag*c.real;
		return *this;
	}
	friend ComplexNumber& operator *(double, ComplexNumber &);

	friend ComplexNumber operator /(double, ComplexNumber &);
	ComplexNumber operator /(ComplexNumber &c) {
		double k = 1.0;
		ComplexNumber temp = k / c;
		return (*this)*(temp);
	}
};


ComplexNumber& operator +(double k, ComplexNumber &c) {
	c.real = k + c.real;
	return c;
}

ComplexNumber& operator -(double k, ComplexNumber &c) {
	c.real = k - c.real;
	return c;
}

ComplexNumber& operator *(double k, ComplexNumber &c) {
	c.real = k * c.real;
	c.imag = k * c.imag;
	return c;
}

ComplexNumber operator /(double k, ComplexNumber &c) {
	ComplexNumber temp = !c;

	return k / (c.real*c.real + c.imag*c.imag) * (temp);
}


ostream& operator <<(ostream& out, const ComplexNumber& c) {
	ComplexNumber tmp;
	tmp.real = c.real;
	tmp.imag = c.imag;
	if (c.real == -0) {
		tmp.real = 0;
	}
	if (c.imag == -0) {
		tmp.imag = 0;
	}
	if (c.imag < 0) {
		out << tmp.real << tmp.imag << "i";
		return out;
	}
	out << tmp.real << "+" << tmp.imag << "i";

	return out;
}

istream& operator >>(istream& in, ComplexNumber& c) {
	in >> c.real;
	in >> c.imag;
	return in;
}


int main() {
	ComplexNumber a;
	ComplexNumber b;
	cin >> a;
	cin >> b;

	cout << !a << endl;
	cout << !b << endl;

	cout << 1 / a << endl;
	cout << 1 / b << endl;

	cout << a + b << endl;
	cout << a - b << endl;
	cout << a * b << endl;
	cout << a / b << endl;

	cout << -0.1 * a << endl;
	cout << b * 10 << endl;
	cout << !a + !b << endl;
	cout << !a * b << endl;

	return 0;

}