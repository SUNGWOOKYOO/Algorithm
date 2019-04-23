#include <iostream>
#include <array>
#include <string>
using namespace std;

int main() {
	array <string, 2> strarr = {string("aaa"),"bbb"};

	for (auto s: strarr) {
		cout << s << endl;
	}

	return 0;
}