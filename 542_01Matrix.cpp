#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
		int m = matrix.size(); // rows.size
		int n = matrix[0].size(); //cols.size
		int max_v = 10000;
		vector<vector<int>> output;
		output.resize(m);
		for (int i = 0; i < m; ++i) output[i].resize(n);

		// dynamic programing 
		// (1), (4) 만 해도 optimal sol을 구할 수 있다. induction step을통해 증명가능  
		// (1)
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == 0 && j == 0) {//1   
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = max_v;
					}
				}
				else if(i==0 && j!=0){
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(max_v, output[i][j - 1]) + 1;
					}
				}
				else if (j==0 && i!=0) {
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(output[i-1][j], max_v) + 1;
					}
				}
				else if (i!=0 && j!=0) {
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(output[i - 1][j], output[i][j - 1]) + 1;
					}
				}
			}
		}
		cout << "(1)" << endl;
		for (auto rows : output) {
			for (auto e : rows) {
				cout << e << " ";
			}
			cout << endl;
		}

		//(2)
		for (int i = 0; i < m; ++i) {
			for (int j = n-1; j > -1; --j) {
				if (i == 0 && j == n-1) {//1   
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(max_v, output[i][j]);
					}
				}
				else if (i == 0 && j != (n-1)) {
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(output[i][j],min(max_v, output[i][j + 1]) + 1);
					}
				}
				else if (j == (n-1) && i != 0) {
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(output[i][j], min(output[i - 1][j], max_v) + 1);
					}
				}
				else if (i != 0 && j != (n-1)) {
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(output[i][j], min(output[i - 1][j], output[i][j + 1]) + 1);
					}
				}
			}
		}
		cout << "(2)" << endl;
		for (auto rows : output) {
			for (auto e : rows) {
				cout << e << " ";
			}
			cout << endl;
		}
		
		//(3)
		for (int i = (m-1); i > -1; --i) {
			for (int j = 1; j < n; ++j) {
				if (i == (m-1) && j == 0) {//1   
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(max_v, output[i][j]);
					}
				}
				else if (i == (m-1) && j != 0) {
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(output[i][j], min(output[i][j - 1], max_v) + 1);
					}
				}
				else if (j == 0 && i != (m-1)) {
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(output[i][j], min(output[i + 1][j], max_v) + 1);
					}
				}
				else if (i != (m-1) && j != 0) {
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(output[i][j], min(output[i][j - 1], output[i + 1][j]) + 1);
					}
				}
			}
		}
		cout << "(3)" << endl;
		for (auto rows : output) {
			for (auto e : rows) {
				cout << e << " ";
			}
			cout << endl;
		}

		//(4)
		for (int i = (m-1); i > -1; --i) {
			for (int j = (n-1); j > -1; --j) {
				if (i == (m - 1) && j == (n-1)) {//1   
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(max_v, output[i][j]);
					}
				}
				else if (i == (m - 1) && j != (n-1)) {
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(output[i][j], min(output[i][j + 1], max_v) + 1);
					}
				}
				else if (j == (n - 1) && i != (m - 1)) {
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(output[i][j], min(max_v, output[i + 1][j]) + 1);
					}
				}
				else if (i != (m - 1) && j != (n - 1)) {
					if (matrix[i][j] == 0) {
						output[i][j] = 0;
					}
					else {
						output[i][j] = min(output[i][j], min(output[i][j + 1], output[i + 1][j]) + 1);
					}
				}
			}
		}
		cout << "(4)" << endl;
		for(auto rows: output){
			for(auto e: rows){
				cout<< e <<" ";
			}
			cout<<endl;
		}
		
		return output;
	}
};

// solution: https://medium.com/@lenchen/leetcode-542-01-matrix-b85e06193ec8
int main() {
	vector<vector<int>> input;
	vector<vector<int>> output;
	int m, n;
	cin >> m;
	cin >> n;
	input.resize(m);
	for (int i = 0; i < m; ++i) input[i].resize(n);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> input[i][j];
		}
	}
	Solution sol;
	output = sol.updateMatrix(input);

	cout << "result: " << endl;
	for (auto rows : output) {
		for (auto e : rows) {
			cout << e << " ";
		}
		cout << endl;
	}
}