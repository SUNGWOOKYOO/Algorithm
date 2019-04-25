#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


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