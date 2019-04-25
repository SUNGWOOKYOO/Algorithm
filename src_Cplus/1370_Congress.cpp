#include<iostream>
#include<iomanip>
#include<limits>
#include<tuple>
#include<map>
#include<vector>
#include<set>

using namespace std;

tuple<int, vector<int>> lookup(vector<tuple<int, int>>& list, map<tuple<int, int>, int>& Info, tuple<int, vector<int>>* L, int i);
tuple<int, vector<int>> Congress(vector<tuple<int, int>>& list, map<tuple<int, int>, int>& Info, int n) {
	tuple<int, vector<int>>* L = new tuple<int, vector<int>>[n];
	for (int i = 0; i < n; ++i) {
		get<0>(L[i]) = std::numeric_limits<int>::min();
	}
	auto result = lookup(list, Info, L, n - 1);
	
	/*
	for (int i = 0; i < n; ++i) {
		cout << "[" << get<0>(L[i]) << ", [";
		auto next = get<1>(L[i]);
		for (auto e :next) {
			cout << e << " ";
		}cout << "]]" << endl;
	}cout << endl;
	*/

	int maxV = 0;
	for (int i = 0; i < n; ++i) {
		int tmp = get<1>(L[i]).size();
		if (tmp > maxV) {
			result = L[i];
			maxV = tmp;
		}
	}

	delete[] L;
	return result;
}
tuple<int, vector<int>> lookup(vector<tuple<int, int>>& list, map<tuple<int, int>, int>& Info, tuple<int, vector<int>>* L, int i) {
	//cout << "lookup(" << i << ")" << endl;
	if (get<0>(L[i]) > 0) {
		return L[i];
	}
	if (i == 0) {
		get<0>(L[i]) = 1;
		get<1>(L[i]).push_back(Info[list[i]]);
		return L[i];
	}
	if (get<0>(list[i]) < get<1>(list[0])) { // Non compatible case
		get<0>(L[i]) = 1;
		get<1>(L[i]).push_back(Info[list[i]]);
		//cout << "debug "<<i <<" "<< get<0>(L[i]) << endl;
		return L[i];
	}
	int maxV = std::numeric_limits<int>::min();
	tuple<int, vector<int>> tmp_result;
	vector<int > max_vec;
	for (int k = 0; k < i; ++k) {
		//cout << "k = " << k << endl;
		tmp_result = lookup(list, Info, L, k);
		if (get<0>(list[i]) >= get<1>(list[k])) {
			int localV = get<0>(tmp_result) + 1;
			if (maxV < localV) {
				maxV = localV;
				max_vec = get<1>(tmp_result);
			}
		}
	}
	get<0>(L[i]) = maxV;
	get<1>(L[i]) = max_vec;
	get<1>(L[i]).push_back(Info[list[i]]);

	/*
	cout << "[" << get<0>(L[i]) << ", [";
	auto next = get<1>(L[i]);
	for (auto e : next) {
		cout << e << " ";
	}cout << "]]" << endl;
	*/

	return L[i];
}

// bottom up
tuple<int, vector<int>> Congress_BU(vector<tuple<int, int>>& list, map<tuple<int, int>, int>& Info, int n) {
	tuple<int, vector<int>>* L = new tuple<int, vector<int>>[n];
	for (int i = 0; i < n; ++i) {
		get<0>(L[i]) = std::numeric_limits<int>::min();
	}
	// base case
	get<0>(L[0]) = 1;
	get<1>(L[0]).push_back(Info[list[0]]);

	// iterative
	for (int i = 1; i < n; ++i) {
		if (get<0>(list[i]) < get<1>(list[0])) { // Non compatible case
			get<0>(L[i]) = 1;
			get<1>(L[i]).push_back(Info[list[i]]);
		}
		else {
			int maxV = std::numeric_limits<int>::min();
			tuple<int, vector<int>> tmp_result;
			vector<int > max_vec;
			for (int k = 0; k < i; ++k) {
				tmp_result = L[k];
				if (get<0>(list[i]) >= get<1>(list[k])) {
					int localV = get<0>(tmp_result) + 1;
					if (maxV < localV) {
						maxV = localV;
						max_vec = get<1>(tmp_result);
					}
				}
			}
			get<0>(L[i]) = maxV;
			get<1>(L[i]) = max_vec;
			get<1>(L[i]).push_back(Info[list[i]]);
		}
		// debug
		/*
		cout << "[" << get<0>(L[i]) << ", [";
		auto next = get<1>(L[i]);
		for (auto e : next) {
			cout << e << " ";
		}cout << "]]" << endl;
		*/
	}

	tuple<int, vector<int>>result;
	int maxV = 0;
	for (int i = 0; i < n; ++i) {
		if (get<1>(L[i]).size() > maxV) {
			result = L[i];
			maxV = get<1>(L[i]).size();

		}
	}
	delete[] L;
	return result;
}



void swap(vector<tuple<int, int>>& a, int i, int j) {
	tuple<int, int> tmp = a[j];
	a[j] = a[i];
	a[i] = tmp;
}

int partition(vector<tuple<int, int>>& a, int p, int r) {
	tuple<int, int> pivot = a[r];
	int i = p - 1;
	for (int j = p; j < r; ++j) {
		if (get<1>(a[j]) < get<1>(pivot)) {
			i = i + 1;
			swap(a, i, j);
		}
	}
	swap(a, i + 1, r);
	return i + 1;
}

void Quicksort(vector<tuple<int, int>>& a, int p, int r) {
	//cout << "qick(" << p << "," << r << ")" << endl;
	if (p >= r) return;
	int q = partition(a, p, r);
	Quicksort(a, p, q - 1);
	Quicksort(a, q + 1, r);
}

void Congress_greedy(vector<tuple<int, int>>& list, map<tuple<int, int>, int>& Info, int i, int n, vector<int>& Aset) {
	//cout << "act(" <<i<<")"<< endl;
	if (i == 0) {
		Aset.push_back(Info[list[0]]);
	}
	// find a compatible acitivity with earlist finishing time(greedy chioce)
	int m = i + 1;
	while (get<1>(list[i]) > get<0>(list[m]) && m < n) {
		m = m + 1;
	}
	if (m < n) {
		Aset.push_back(Info[list[m]]);
		Congress_greedy(list, Info, m, n, Aset);
		return;
	}
	return;
}

int main() {
	int n;
	cin >> n;
	int k;
	int* s = new int[n];
	int* f = new int[n];
	map<tuple<int,int>, int> Info;
	vector<tuple<int, int>> list;
	for (int i = 0; i < n; ++i) {
		// one line info
		cin >> k;
		cin >> s[k];
		cin >> f[k];
		Info[make_tuple(s[k], f[k])] = k;
		list.push_back(make_tuple(s[k], f[k]));
	}
	/*
	for (auto it = Info.begin(); it != Info.end(); ++it) {
		cout << "[("<< get<0>(it->first) << ", " << get<1>(it->first)<<"),"<< it->second << "]"<< endl;
	}
	*/
	/*
		6
		1 1 10
		2 5 6
		3 13 15
		4 14 17
		5 8 14
		6 3 12
	*/
	/*
		11
		1 1 4
		2 3 5
		3 0 6
		4 5 7
		5 3 8
		6 5 9
		7 6 10
		8 8 11
		9 8 12
		10 2 13
		11 12 14
	*/

	Quicksort(list, 0, (list.size() - 1));
	
	/*
	for (auto e: list) {
		cout << "(" << get<0>(e) << "," << get<1>(e) << ")" << endl;
	}
	*/
	
	// 1. DP:  O(n^2)
	cout << "DP topdown : " << endl;
	auto DPresult = Congress(list, Info, n);
	cout << get<0>(DPresult) << endl;
	auto vec = get<1>(DPresult);
	for (auto e: vec) {
		cout << e << " ";
	}cout << endl;

	cout << "DP bottomup: " << endl;
	auto DPresult2 = Congress_BU(list, Info, n);
	cout << get<0>(DPresult2) << endl;
	auto vec2 = get<1>(DPresult2);
	for (auto e : vec2) {
		cout << e << " ";
	}cout << endl;

	// 2. Greedy:  O(n)
	
	cout << "Greedy: " << endl;
	vector<int> Aset2;
	//insert sentinel value
	list.push_back(make_tuple(-1, std::numeric_limits<int>::max()));
	Congress_greedy(list, Info, 0, n, Aset2);
	cout << Aset2.size() << endl;

	for (auto e : Aset2) {
		cout << e << " ";
	}cout << endl;
	
}