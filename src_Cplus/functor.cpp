#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

#if 0

bool GT3(const std::string& s) {
	return s.size() >= 3;
}
bool GT6(const std::string& s) {
	return s.size() >= 6;
}

class larger_than {
public:
	larger_than(int b) :bound(b) {}
	bool operator()(const int n) { return n > bound; }
private:
	int bound;
};

int main() {

	/*
	std::vector<std::string> words;

	words.push_back("Programming"); words.push_back("Methodlogy");
	words.push_back("is");	words.push_back("easy");
	words.push_back("or");	words.push_back("not easy");
	std::cout << count_if(words.begin(), words.end(), GT3) << std::endl;
	std::cout << count_if(words.begin(), words.end(), GT6) << std::endl;
	*/
	std::vector<int> vec;
	srand((unsigned int)time(0));
	for (int i = 0; i < 20; i++)
		vec.push_back(rand() % 100);

	cout << "Before calling partition function : " << endl;
	for (auto v: vec) {
		cout << v << " ";
	}
	cout << endl;

	auto it = std::partition(vec.begin(), vec.end(), larger_than(50));
	cout << "The position of it: "<< *it << endl;

	for (auto iter = vec.begin(); iter != it; ++iter)
		cout << *iter << " ";
	cout << endl;
	for (auto iter = it; iter != vec.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
}

#elif 1

//implement your own functors and use it in quicksort
class smaller_than {	//you can change the name
public:
	smaller_than(int b) :bound(b) {}
	bool operator()(const int n) { return n < bound; }
private:
	int bound;
};

class swaplast {	//you can change the name
public:
	swaplast() {}
	bool operator()(vector<int>::iterator l) {

	}
private:
};


void quick_sort(vector<int>::iterator l, vector<int>::iterator r)
{
	//implement here
	/*
	int last = *(r-1);
	cout << "last value: " << last << endl;;
	auto it = std::partition(l, r, smaller_than(last));
	cout << "pivot position: " << *it << endl;
	int temp = last;
	*(r-1) = *(it);
	*(it) = temp;
	*/

	if (l != r) {

		//partition
		int last = *(r - 1);
		auto it = std::partition(l, r, smaller_than(last));
		// swap last and it 
		int temp = last;
		*(r - 1) = *(it);
		*(it) = temp;

		// recursive call
		quick_sort(l, (it));
		quick_sort(it + 1, r);
	}


}


void main() {
	vector<int> vec = { 1,45,6,7,1,8,3,168,46,23,156 };

	quick_sort(vec.begin(), vec.end());
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}
#endif 