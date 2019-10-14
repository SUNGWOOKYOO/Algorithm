#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:

	// O(n^2) top down with memoization
	bool lookup(vector<int>& a, bool* j, bool* memo, int i) {
		if (i == 0)
			return true;
		if (memo[i])
			return j[i];

		bool q = false;
		for (auto k = 0; k < i; ++k)
			q = q || (lookup(a, j, memo, k) && (a[k] >= i - k));

		memo[i] = true;
		j[i] = q;
		return j[i];
	}

	bool canJump(vector<int>& a) {
		int n = a.size();
		bool* j = new bool[n];
		bool* memo = new bool[n];
		// initialization
		for (int i = 1; i < n; ++i) {
			j[i] = false;
			memo[i] = false;
		}
		return lookup(a, j, memo, n - 1);
	}

	// O(n^2)
	bool canJump_DP(vector<int>& a) {
		int n = a.size();
		bool* j = new bool[n];
		j[0] = true;
		for (int i = 1; i < n; ++i) {
			j[i] = false;
			for (int k = 0; k < i; ++k) {
				j[i] = j[i] || (j[k] && (a[k] >= i - k));
			}
		}
		/*
		for (int i = 0; i < n; ++i) {
			cout << j[i] << " ";
		}cout << endl;
		*/
		return j[n - 1];
	}

	// O(n)
	bool canJump_Incremental(vector<int>& a) {
		int n = a.size();
		bool* j = new bool[n];
		bool* h = new bool[n+1];
		j[0] = true;
		h[1] = j[0];
		for (int i = 1; i < n; ++i) {
			j[i] = h[i] || (j[i - 1] && (a[i - 1] >= 1));
			h[i + 1] = j[i];
		}
		/*
		for (int i = 0; i < n; ++i) {
			cout << j[i] << " ";
		}cout << endl;
		*/
		return j[n - 1];
	}

	bool canJump_greedy(vector<int>& a) {
		// backward
		int n = a.size();
		int last = n - 1;
		for (int i = n - 2; i >= 0; i--) {
			if (i + a[i] >= last)last = i;
		}
		return last <= 0;
	}

	bool canJump_greedy2(vector<int>& a) {
		// forward
		int n = a.size();
		int maxj = a[0];
		for (int i = 0; i <= maxj; i++) {
			maxj = max(maxj, i + a[i]); // greedy choice 
			if (maxj >= n-1) return true;
		}
		return false;
	}
};

int main() {
	int n;
	cin >> n;
	vector<int> a;
	for (int i = 0; i < n; ++i) {
		int e;
		cin >> e;
		a.push_back(e);
	}
	Solution sol;
	/*
	5	
	2 3 1 1 4

	5
	3 2 1 0 4
	*/
	cout << "Top down" << endl;
	cout << sol.canJump(a) << endl;
	
	cout << "DP" << endl;
	cout << sol.canJump_DP(a) <<endl;

	cout << "Incremental" << endl;
	cout << sol.canJump_Incremental(a) << endl;

	cout << "greedy" << endl;
	cout << sol.canJump_greedy2(a) << endl;

	return 0;
}