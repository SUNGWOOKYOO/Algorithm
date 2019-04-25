#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;
int calc(const string &op, const string &int1_str, const string &int2_str);
int parse(const string &str);

class OpException :public runtime_error {
public:
	OpException() :runtime_error("") { }
};

class IntException :public runtime_error {
public:
	IntException() :runtime_error("") {}
};

class DivideByZeroException :public runtime_error {
public:
	DivideByZeroException() :runtime_error("") {}
};

int main() {
	string op, int1, int2;
	cin >> int1 >> op >> int2;

	try {
		int result = calc(op, int1, int2);
		cout << result;
	}
	catch (OpException &) {
		cout << "Invalid operator";
	}
	catch (IntException &) {
		cout << "Invalid integer";
	}
	catch (DivideByZeroException &) {
		cout << "9999999999";
	}
	return 0;
}

int calc(const string &op, const string &int1_str, const string &int2_str) {
	int int1 = parse(int1_str);
	int int2 = parse(int2_str);
	if (int2 == 0) throw DivideByZeroException();

	if (op == "+")
		return int1 + int2;
	else if (op == "-")
		return int1 - int2;
	else if (op == "*")
		return int1 * int2;
	else if (op == "/") {
		return int1 / int2;
	}
	else {
		throw OpException();
	}
}

int parse(const string &str) {
	for (auto ch : str) {
		if (isdigit(ch) == false) {
			throw IntException();
		}

	}
	return std::atoi(str.c_str());
}