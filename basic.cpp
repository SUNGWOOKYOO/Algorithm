#include <iostream>
#include <vector>
#include <tuple>
#include <ctime>
#include <chrono>
#include <cmath>

using namespace std;

#if 0
// TODO
void get_pointers1(int*& _p1, int*& _p2, int* pa, int* pb) {
	_p1 = pa;
	_p2 = pb;
}
#elif 0
// std::tuple
std::tuple<int, int> division(int x, int y) {
	return std::make_tuple(x/y, x%y);
	//return std::tuple<int, int>(x/y, x%y);
}
#elif 1
// time measurement
void Test() {
	for (long i=0; i < 10000000; ++i) {
		std:sqrt(123.456L);
	}
}
#endif

int main() {
#if 0 
	int i = 10;
	int& ir = i;
	int* p = &i;
	cout << i << endl; // reference to i 
	cout << *p << endl; // pointer 
	
	int arr[] = { 1,3,5,7 };
	cout << *(arr + 1) << endl;

	int *p1, *p2;
	int a, b, c, d;

	// =====================================================
	int *p1, *p2;
	int a, b, c, d;
	// By plugging a vlaue into pointer, we can assign a,b 
	get_pointers1(p1, p2, &a, &b);
	cin >> *p1 >> *p2;
	cout << a << " " << b << endl;
#elif 0
	// ====================================================
	int X, Y; 
	std::cin >> X >> Y;
	int** a = new int*[X];
	for (int i = 0; i < X; ++i) {
		a[i] = new int[Y];
	}

	for (int i = 0; i < X; ++i) {
		for (int j = 0; j < Y; ++j) {
			a[i][j] = i + j;
			std::cout << "a["<<i<<"]["<<j<<"]"<< " ";
		}
		cout << endl;
	}

	for (int i = 0; i < X; ++i) {
		delete[] a[i];
	}
	delete[] a; 
#elif 0
	// ====================================================
	vector<int> myv;
	int sum(0);
	myv.push_back(100);
	myv.push_back(200);
	myv.push_back(300);
	myv.insert(myv.begin(), 50);

	while (!myv.empty()) {
		/*
		for (vector<int>::iterator it = myv.begin(); it < myv.end(); it++) {
			cout << *it << " ";
		}
		*/
		for (auto it = myv.begin(); it < myv.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;

		sum += myv.back();
		myv.pop_back();
	}
	cout << "¥Ò(myv): " << sum << endl;
#elif 0
	// ====================================================
	/* std::tuple
		Defining the tuple
			tuple<type1, type2, ¡¦> name
		Accessing the tuple
			get<position>(name)	*/
	int quotient, remainder;
	std::tuple<int, int> result = division(77, 14);
	quotient = std::get<0>(result);
	remainder = std::get<1>(result);
	cout << quotient << " " << remainder << std::endl;

	cout << std::tuple_size<tuple<int, int>>::value << endl;
	//cout << tuple_size<decltype(result)>::value << endl;

#elif 1
	// ====================================================
	// time measure
	time_t timer;
	struct tm* timeInfo;
	time(&timer); // get current time
	timeInfo = localtime(&timer);
	cout << timeInfo->tm_year + 1900 << ". " << timeInfo->tm_mon + 1 << ". "
		<< timeInfo->tm_mday << endl << timeInfo->tm_hour << ":"
		<< timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;
	/*
	auto start = std::chrono::system_clock::now();
	Test();
	// Do not declare this type to auto 
	std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
	cout << "Running time: " << sec.count() << "seconds" << endl;
	*/
	//chrono::system_clock::time_point start = chrono::system_clock::now();
	auto start = chrono::system_clock::now();
	Test();
	auto end = chrono::system_clock::now();
	auto sec = chrono::duration_cast<chrono::milliseconds>(end - start);
	cout<< "Running time: " << sec.count() << "ms" << endl;
#endif
}