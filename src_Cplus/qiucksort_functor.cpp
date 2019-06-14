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

void quick_sort(vector<int>::iterator l, vector<int>::iterator r)
{
	//implement here
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
