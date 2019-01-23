#include <iostream>
#include <vector>
#include <string>
using namespace std;

void Activity(vector<int>& s, vector<int>& f, int k, int n, vector<string>& Aset) {
	
	// find a compatible acitivity with earlist finishing time(greedy chioce)
	int m = k + 1;
	while (s[m] < f[k] && n >= m ) {
		m = m + 1;
	}
	if (m <= n) {
		Aset.push_back("a" + std::to_string(m));
		Activity(s, f, m, n, Aset);
		return;
	}

	return;
}

int main() {
	vector<int> s,f;
	int n;
	cout << "Enter the num of activities:  " ;
	cin >> n;
	// n = 11

	cout << "Insert Input arrays " << endl;
	// Assume that inputs are already sorted : f[1] <= f[2] <= f[3] <= ... <= f[11]
	/*
		starting time and finishing time: 
		11
		1 3 0 5 3 5 6 8 8 2 12 
		4 5 6 7 8 9 10 11 12 13 14
	*/
	int input;
	for (int i = 0; i < n; ++i) {
		// starting time
		cin >> input;
		s.push_back(input);
	}
	// sentinel value
	s.insert(s.begin(), -1);
	s.push_back(1000);

	for (int i = 0; i < n; ++i) {
		// finishing time
		cin >> input;
		f.push_back(input);
	}
	// sentinel value
	f.insert(f.begin(), 0);
	f.push_back(-1);

	vector<string> Aset;
	Activity(s, f, 0, n, Aset);
	
	for (string a : Aset) {
		cout << a << " ";
	}cout << endl;


	return 0;
}