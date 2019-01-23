#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		int *tmp = new int[k];
		/*
		for (int i = 0; i < k; ++i) {
			tmp[i] = std::numeric_limits<int>::min();
		}
		*/
		int key;
		int i, j;
		for (int m = 0; m < nums.size(); ++m) {
			cout << "m = " << m << endl;
			if (k > m) {
				tmp[m] = nums[m];
				key = tmp[m];
				j = m;
			}
			else{
				if (tmp[k - 1] < nums[m]) {
					tmp[k - 1] = nums[m];
					key = tmp[k - 1];
					j = k - 1;
				}
				else {
					continue;
				}
			}

			i = j - 1;
			while (i > -1 && key > tmp[i]) {
				tmp[i + 1] = tmp[i];
				i = i - 1;
			}
			i = i + 1;
			tmp[i] = key;

			for (int l = 0; l < k; ++l) {
				cout << tmp[l] << " ";
			}cout << endl;

		}
		return tmp[k - 1];
	}
};

int main() {

	Solution sol;
	vector<int> v;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int e;
		cin >> e;
		v.push_back(e);
	}
	cout << "k: ";
	int k; 
	cin >> k;
	cout << "result : " << sol.findKthLargest(v, k) << endl;
	/* input 
		6
		3 2 1 5 6 4
		2
		expected result: 5
	*/
	return 0;
}