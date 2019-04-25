#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
	// O(n^2)
	vector<int> nextGreaterElements(vector<int>& a) {
		int n = a.size();
		vector<int> c;
		c.resize(n, -1);
		for (int i = 0; i < n; ++i) {
			bool flag = false;
			for (int j = i + 1; j < n; ++j) {
				if (a[i] < a[j]) {
					c[i] = a[j];
					flag = true;
					break;
				}
			}
			if (flag == false) {
				for (int j = 0; j < i; ++j) {
					if (a[i] < a[j]) {
						c[i] = a[j];
						break;
					}
				}
			}

		}

		for (auto e : c) {
			cout << e << " ";
		}cout << endl;

		return c;
	}
};

int main() {
	vector<int> input;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int e;
		cin >> e;
		input.push_back(e);
	}
	Solution sol;
	sol.nextGreaterElements(input);

	return 0;
}

