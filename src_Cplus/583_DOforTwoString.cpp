#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
	/*
	int minDistance(string word1, string word2) {
		int m = word1.length();
		int n = word2.length();
		int** c = new int*[m + 1];
		for (int i = 0; i < m+1; ++i) {
			c[i] = new int[n + 1];
		}
		for (int i = 0; i < m + 1; ++i) {
			for (int j = 0; j < n + 1; ++j) {
				c[i][j] = 0;
			}
		}
		for (int i = 1; i < m + 1; ++i) {
			for (int j = 1; j < n + 1; ++j) {
				if (word1[i - 1] != word2[j - 1]) {
					c[i][j] = max(c[i - 1][j], c[i][j - 1]);
				}
				else {
					c[i][j] = c[i - 1][j - 1] + 1;
				}
			}
		}

		int result = c[m][n];
		
		for (int i = 0; i < n+1; i++) {
			delete[] c[i];
		}
		delete[] c;
		
		return (m + n - 2 * result);
	}
	*/
	/*
	int minDistance(string word1, string word2) {
		int m = word1.length();
		int n = word2.length();
		int* c1 = new int[n + 1];
		for (int j = 0; j < n + 1; ++j) c1[j] = 0;
		int* c2 = new int[n + 1];
		for (int i = 1; i < m + 1; ++i) {
			for (int j = 0; j < n + 1; ++j) {
				if (j == 0) {
					c2[j] = 0;
				}
				else {
					if (word1[i - 1] != word2[j - 1]) {
						c2[j] = max(c2[j - 1], c1[j]);
					}
					else {
						c2[j] = c1[j - 1] + 1;
					}
				}
			}
			for (int k = 0; k < n + 1; ++k) {
				c1[k] = c2[k];
			}
		}
		int result = c2[n];
		delete[]c2;
		delete[]c1;
		return (m + n - 2 * result);
	}
	*/
	int minDistance(string word1, string word2) {
		int m = word1.length();
		int n = word2.length();
		int* c1 = new int[n + 1];
		for (int j = 0; j < n + 1; ++j) c1[j] = 0;
		int* c2 = new int[n + 1];
		for (int i = 1; i < m + 1; ++i) {
			for (int j = 0; j < n + 1; ++j) {
				if (j == 0) {
					c2[j] = 0;
				}
				else {
					if (word1[i - 1] != word2[j - 1]) {
						c2[j] = max(c2[j - 1], c1[j]);
					}
					else {
						c2[j] = c1[j - 1] + 1;
					}
				}
			}
		}

		int result = c1[n];
		delete[]c2;
		delete[]c1;
		return (m + n - 2 * result);
	}
};

int main() {
	cout << "Enter Inputs : " << endl;
	string word1, word2;
	cin >> word1;
	cin >> word2;
	Solution sol;
	int result = sol.minDistance(word1, word2);
	cout << result << endl;
	return 0;
}