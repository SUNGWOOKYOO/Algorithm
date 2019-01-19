#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:

	int BS(vector<int>& A, int i, int j, int k) {
		cout << "BS(A," << i << "," << j << "," << k << ")" << endl;
		if (i >= j) {
			if (A[i] == k) return i;
			else return -1;
		}
		
		int mid = i + ((j - i) >> 1);
		if (A[j] < A[mid]) { // [ascending [mid] ..][pivot][ascending]
			if (A[mid] < k) {
				return BS(A, mid + 1, j, k);
			}
			else if (A[mid] > k) {
				if (A[j] < k) {
					return BS(A, i, mid - 1, k);
				}
				else if (A[j] > k) {
					return BS(A, mid + 1, j, k);
				}
				else {
					return j;
				}
			}
			else {
				return mid;
			}
		}
		else { //[ascending ][pivot][.. [mid] ascending]
			if (A[mid] < k) {
				if (A[j] < k) {
					return BS(A, i, mid - 1, k);
				}
				else if (A[j] > k) {
					return BS(A, mid + 1, j, k);
				}
				else {
					return j;
				}
			}
			else if (A[mid] > k) {
				return BS(A, i, mid - 1, k);
			}
			else {
				return mid;
			}
		}
	}

	int search(vector<int>& nums, int target) {
		if (nums.size() == 0) return 0;
		int result = BS(nums, 0, nums.size() - 1, target);
		return result;
	}
};

int main() {
	vector<int> A;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int tmp;
		cin >> tmp;
		A.push_back(tmp);
	}

	int k;
	cin >> k;

	Solution sol;
	int result = sol.search(A, k);
	cout << result << endl;

	return 0;
}