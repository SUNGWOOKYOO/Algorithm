#include <iostream>
#include <stdio.h>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool f_compare(tuple<int, string> a, tuple<int, string> b) {
	return get<1>(a) < get<1>(b);
}

int main() {
	int n;
	//freopen("input3.txt", "r", stdin);
	cin >> n;
	int e;
	string s;
	vector< tuple<int, string> > v;

	for (int i = 0; i < n; ++i) {
		cin >> e;
		cin >> s;
		v.push_back(make_tuple(e, s));
	}

	for (auto tu : v)
		cout << get<0>(tu) << " " << get<1>(tu) << " ";
	cout << endl;

	cout << "after sort" << endl;
	
	sort(v.begin(), v.end(), f_compare);
	
	for (auto tu : v)
		cout << get<0>(tu) << " " << get<1>(tu) << " ";
	cout << endl;

	return 0;
}



