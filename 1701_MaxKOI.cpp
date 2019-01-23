#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <iomanip>
using namespace std;

class Solution {
public:
	bool match(string word, int i, int j) {
		return ((word[i] == 'a' && word[j] == 't') || (word[i] == 'g' && word[j] == 'c'));
	}
	int Lookup(string word, int** c, int i, int j) {
		if (c[i][j] >= 0)
			return c[i][j];
		if (i == j) {
			//cout << "base case 1:" << endl;
			c[i][j] = 0;
			return 0;
		}
		else if ((j - i == 1) && match(word, i, j)) {
			//cout << "base case 2:" << endl;
			c[i][j] = 2;
			return 2;
		}
		else if((j - i > 0)){
			if (match(word, i, j)) {
				//cout << "case1 :" << "Find c[" << i << "][" << j << "] ";
				int q1 = 0;
				int q2 = 0; int thismax = 0;
				q1 = Lookup(word, c, i + 1, j - 1) + 2;
				//cout << ", where c[" << i+1 << "][" << j - 1 << "] = " << q1 << endl;
				for (int k = i; k < j; ++k) {
					//cout << "call [" << i << "][" << k << "] and [" << k+1 << "][" << j << "]"<<endl;
					thismax = max(thismax, Lookup(word, c, i, k) + Lookup(word, c, k + 1, j));
					if (q2 < thismax) {
						q2 = thismax;
					}
				}
				c[i][j] = max(q1, q2);
			}
			else {
				//cout << "case2 :" << "Find c[" << i << "][" << j << "] ";
				int q1 = 0;
				int q2 = 0; int thismax = 0;
				q1 = Lookup(word, c, i + 1, j - 1);
				//cout << ", where c[" << i + 1 << "][" << j - 1 << "] = " << q1 << endl;
				for (int k = i; k < j; ++k) {
					thismax = max(thismax, Lookup(word, c, i, k) + Lookup(word, c, k + 1, j));
					if (q2 < thismax) {
						q2 = thismax;
					}
				}
				c[i][j] = max(q1, q2);
			}
		}
		//cout << "c[" << i << "][" << j << "] = " << c[i][j] << endl;
		return c[i][j];
	}
	int MaxKOI(string word) {
		int result = 0;
		int n = word.length();
		int** c = new int*[n];
		for (int i = 0; i < n; ++i) {
			c[i] = new int[n];
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				c[i][j] = -100;
			}
		}
		result = Lookup(word, c, 0, n-1);
		/*
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cout << setw(4) <<c[i][j] << " ";
			}
			cout << endl;
		}
		*/
		for (int i = 0; i < n; i++) {
			delete[] c[i];
		}
		delete[] c;

		return result;
	}
};

int main(){
	cout << "Enter input DNA seq: ";
	string word = "tatagcat";
	//cin >> word;

	Solution sol;
	int result = sol.MaxKOI(word);
	//cout << "result: " << result << endl;
	cout << result << endl;
	return 0;
}
