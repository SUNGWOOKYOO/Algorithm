#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
	int minDeletionSize(vector<string>& A) {
		int m = A.size();
		int n = A[0].size();
		vector<int> indexset;
		for (int j = 0; j < n; ++j) {
			for (int i = 0; i < m; ++i) {
				//cout << A[i][j] << endl;
				if (i != 0) {
					if (A[i][j] - A[i - 1][j] < 0) {
						indexset.push_back(j);
						break;
					}
				}
			}//cout <<endl;
		}
		int result = indexset.size();
		for (auto e : indexset) {
			cout << e << " ";
		}cout << endl;

		return result;
	}
};

int main() {
	int n;
	cin >> n;
	vector<string> A;
	string str;
	for (int i = 0; i < n; ++i) {
		cin >> str;
		A.push_back(str);
	}

	/*
	3
	rrjk
	furt
	guzm
	*/
	Solution sol;
	cout << "result: "<< sol.minDeletionSize(A);
	return 0;
}