#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
	int maxProfit(vector<int>& p) {
		p.push_back(-1000000); // sentinel value;
		int n = p.size();
		int* s = new int[n];
		int start = 0;
		s[0] = 0;
		s[1] = 0;
		if (p[0] >= p[1])
			start = 1;

		for (int i = 2; i < n; ++i) {
			if (p[start] <= p[i - 1]) {
				if (p[i - 1] <= p[i]) {
					s[i] = s[i - 1];
				}
				else {
					s[i] = s[i - 1] + p[i - 1] - p[start];
					//cout << "margin " << "p["<< i - 1 <<"]-p["<<start<<"]= "<< p[i - 1] - p[start] << endl;
					start = i;
				}
			}
			else {
				if (p[i - 1] <= p[i]) {
					s[i] = s[i - 1];
					start = i - 1;
				}
				else {
					s[i] = s[i - 1];
					start = i;
				}
			}
			//cout << "s[" << i << "] = " << s[i] << endl;
			//cout << "start = " << start << endl;
		}

		/*
		for (int i = 0; i < n; ++i) {
			cout << p[i] << " ";
		}cout << endl;

		for (int i = 0; i < n; ++i) {
			cout<< s[i] << " ";
		}cout << endl;
		*/

		int result = s[n - 1];
		delete[]s;
		return result;
	}
};

int main() {
	vector<int> prices;
	int n;
	cin >> n;
	int tmp;
	for (int i = 0; i < n; ++i) {
		cin >> tmp;
		prices.push_back(tmp);
	}
	/*
		14	
		5 2 3 2 6 6 2 9 1 0 7 4 5 0
	*/
	Solution sol;
	cout << "result: "<< sol.maxProfit(prices);
}
