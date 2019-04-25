#include<iostream>
#include<vector>
using namespace std;

// Error! But, I do not know about the cause of malfunctioning
class Solution {
public:
	bool wiggleTest(vector<int>& v, int i) {
		if (i <= 0)
			return false;

		if (i == 1) {
			if (v[0] == v[1])
				return false;
			return true;
		}
		else if (i >= 2) {
			if ((v[i] - v[i - 1]) > 0 && (v[i - 1] - v[i - 2]) <= 0)
				return true;
			else if ((v[i] - v[i - 1]) < 0 && (v[i - 1] - v[i - 2]) >= 0)
				return true;
			else
				return false;
		}
	}

	int wiggleMaxLength(vector<int>& v) {
		if (v.size() == 0)
			return 0;
		if (v.size() == 1)
			return 1;

		int n = v.size();
		vector<int> W(n);
		W[0] = 1;

		for (int i = 1; i < n; ++i) {
			if (wiggleTest(v, i))
				W[i] = W[i - 1] + 1;
			else
				W[i] = W[i - 1];
		}

		for (int e : W) {
		cout << e << " ";
		}cout << endl;

		return W[n - 1];
	}
};

int main() {
	int n;
	cin >> n;
	vector<int> vec(n);
	for (int& e : vec) {
		cin >> e;
	}

	/*for (int e : vec) {
		cout << e << " ";
	}cout << endl;*/

	/*
	6
	1 7 4 9 2 5
	*/

	Solution sol;
	/*for (int i = 0; i < n; ++i) {
		cout << sol.wiggleTest(vec, i) << endl;
	}*/
	cout << sol.wiggleMaxLength(vec) << endl;

	return 0;
}

/*
public class Solution {
	private int calculate(int[] nums, int index, boolean isUp) {
		int maxcount = 0;
		for (int i = index + 1; i < nums.length; i++) {
			if ((isUp && nums[i] > nums[index]) || (!isUp && nums[i] < nums[index]))
				maxcount = Math.max(maxcount, 1 + calculate(nums, i, !isUp));
		}
		return maxcount;
	}

	public int wiggleMaxLength(int[] nums) {
		if (nums.length < 2)
			return nums.length;
		return 1 + Math.max(calculate(nums, 0, true), calculate(nums, 0, false));
	}
}
*/