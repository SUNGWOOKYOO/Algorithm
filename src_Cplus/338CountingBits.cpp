#include<iostream>
#include<vector>
#include<limits>
using namespace std;

class Solution {
public:
	// naive solution O(nlogn)
	int getCount(int n) {
		int result = 0;
		while (n != 0) {
			if (n % 2 == 1) {
				++result;
			}
			n = n / 2;
		}
		return result;
	}
	vector<int> countBits_naive(int num) {
		vector<int> result(num + 1, -1);
		for (int i = 0; i <= num; ++i) {
			result[i] = getCount(i);
		}
		return result;
	}
	int turnoffleftmostbit(int n) {
		unsigned int count = 0;
		int tmp = n;
		while (tmp >>= 1) {
			++count;
		}

		return n & ((1 << count) - 1);
	}
	int lookup(vector<int>& result, int n) {
		cout << "lookup(" << n << ")" << endl;
		if (result[n] > 0) {
			return result[n];
		}
		if (turnoffleftmostbit(n) == 0) {
			result[n] = 1;
			return 1;
		}
		else {
			int x = turnoffleftmostbit(n);
			result[n] = 1 + lookup(result, x);
			return result[n];
		}
	}

	vector<int> countBits(int n) {
		vector<int> result(n + 1, 0);
		for (int i = n; i >= 0; --i) {
			lookup(result, i);
		}
		return result;
	}

	/* https://www.programcreek.com/2015/03/leetcode-counting-bits-java/
		<recurrence>
		r[n] = 1 + r[x]	,if turnoffleftmostbit != 0
			 = 1		,if turnoffleftmostbit == 0 (that is, 2^m + x = n, where x > 0)
	*/

	vector<int> countBits2(int n) {
		vector<int> result(n + 1, 0);

		int p = 1; //p tracks the index for number x
		int pow = 1;
		for (int i = 1; i <= n; i++) {
			if (i == pow) {
				result[i] = 1;
				pow <<= 1;
				p = 1;
			}
			else {
				result[i] = result[p] + 1;
				p++;
			}
		}
		return result;
	}

};

int main() {
	Solution sol;
	/*
	auto result = sol.countBits_naive(5);
	for (auto e: result) {
		cout << e << " ";
	}cout << endl;
	*/
	//cout << sol.turnoffleftmostbit(5) << endl;

	auto result = sol.countBits2(5);
	for (auto e : result) {
		cout << e << " ";
	}cout << endl;

	return 0;
}