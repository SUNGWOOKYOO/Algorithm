#include<iostream>
#include<tuple>
#include<vector>
#include<iomanip>

using namespace std;
// fractional kanpsack problem 
class Value {
public:
	vector<tuple<int, int>>& IT;
	Value(vector<tuple<int, int>>& _IT):IT(_IT) {
	}
	int operator[](int idx) {
		return get<0>(IT[idx]);
	}
};
class Weight {
public:
	vector<tuple<int, int>>& IT;
	Weight(vector<tuple<int, int>>& _IT) :IT(_IT) {
	}
	int operator[](int idx) {;
		return get<1>(IT[idx]);
	}
};

void swap(vector<tuple<int, int>>& a, int i, int j) {
	tuple<int, int> tmp = a[j];
	a[j] = a[i];
	a[i] = tmp;
}

bool comp(vector<tuple<int, int>>& a, int j, tuple<int, int> pivot) {
	Value v(a);
	Weight w(a);
	if ((v[j] / w[j]) > (get<0>(pivot) / get<1>(pivot)))
		return true;
	else
		return false;
}

int partition(vector<tuple<int, int>>& a, int p, int r, bool (*comp)(vector<tuple<int, int>>&, int, tuple<int,int>)) {
	tuple<int, int> pivot = a[r];
	int i = p - 1;
	for (int j = p; j < r; ++j) {
		if (comp(a,j,pivot)) {
			i = i + 1;
			swap(a, i, j);
		}
	}
	swap(a, i + 1, r);
	return i + 1;
}

void Quicksort(vector<tuple<int, int>>& a, int p, int r, bool(*comp)(vector<tuple<int, int>>&, int, tuple<int, int>)) {
	//cout << "qick(" << p << "," << r << ")" << endl;
	if (p >= r) return;
	int q = partition(a, p, r, comp);
	Quicksort(a, p, q - 1, comp);
	Quicksort(a, q + 1, r, comp);
}

// greedy 
double knapack_fractional(Value& v, Weight& w, int n, int maxw) {
	int residualw = maxw;
	double result = 0; 
	for (int i = 1; i <= n; ++i) {
		if (w[i] <= residualw) {
			result = result + v[i];
			residualw = residualw - w[i];
		}
		else {
			// w[i] > residualw
			result = result + (double)v[i] * (double)(residualw / (double)w[i]);
			break;
		}
	}
	return result;
}

int main() {
	vector<tuple<int, int>> items;
	int n;
	cin >> n;
	int maxw;
	cin >> maxw;

	int* prices = new int[n];
	int* weights = new int[n];
	for (int i = 0; i < n; ++i)
		cin >> prices[i];
	for (int i = 0; i < n; ++i)
		cin >> weights[i];
	for (int i = 0; i < n; ++i) {
		items.push_back(make_tuple(prices[i], weights[i]));
	}
	// sort by decreasing order (v[i]/w[i]) 
	Quicksort(items, 0, n - 1, comp); // use the predefined comp 
	items.insert(items.begin(), make_tuple(-1, -1));

	Value v(items);
	Weight w(items);

	for (int i = 0; i <= n; ++i) {
		cout << setw(10) << "price[" << i << "]: " << v[i] << setw(10) << "weight[" << i << "]: " << w[i] << endl;
	}

	double result = knapack_fractional(v, w, n, maxw);
	cout << result;
	
	/*
	3
	5
	60 100 120
	1 2 3
	*/
	return 0;
}