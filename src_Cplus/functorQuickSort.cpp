#if 1
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

int main() {
	//vector<int> vec = { 1,45,6,7,1,8,3,168,46,23,156 };
	freopen("input.txt", "r", stdin);
	vector<int> vec;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int e;
		cin >> e;
		vec.push_back(e);
	}
	quick_sort(vec.begin(), vec.end());
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}
#elif 0
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//implement your own functors and use it in quicksort

class smaller_than {	//you can change the name
public:
	smaller_than(int b) :bound(b) {}
	bool operator()(const int n) { return n <= bound; }
private:
	int bound;
};

void quick_sort(vector<int>::iterator l, vector<int>::iterator r)
{
	//implement here
	if (l != r) {

		//partition
		int pivot = *(l);
		auto it = std::partition(l, r, smaller_than(pivot));

		//// swap last and it 
		int temp = pivot;
		*(l) = *(it - 1);
		*(it - 1) = temp;

		// recursive call
		quick_sort(l, (it - 1));
		quick_sort(it, r);
	}
}


int main() {
	//vector<int> vec = { 1,45,6,7,1,8,3,168,46,23,156 };
	freopen("input.txt", "r", stdin);
	vector<int> vec;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int e;
		cin >> e;
		vec.push_back(e);
	}
	quick_sort(vec.begin(), vec.end());
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}
#elif 0
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <forward_list>

using namespace std;

template <class ForwardIt>
void quick_sort(ForwardIt first, ForwardIt last)
{
	if (first == last) return;
	auto pivot = *std::next(first, std::distance(first, last) / 2);
	ForwardIt middle1 = std::partition(first, last,
		[pivot](const auto& em) { return em < pivot; });
	ForwardIt middle2 = std::partition(middle1, last,
		[pivot](const auto& em) { return !(pivot < em); });
	quick_sort(first, middle1);
	quick_sort(middle2, last);
}

int main() {
	//vector<int> vec = { 1,45,6,7,1,8,3,168,46,23,156 };
	freopen("input.txt", "r", stdin);
	vector<int> vec;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int e;
		cin >> e;
		vec.push_back(e);
	}
	quick_sort(vec.begin(), vec.end());
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}

#endif
