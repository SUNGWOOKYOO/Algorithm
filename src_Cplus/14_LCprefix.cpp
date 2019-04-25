#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		if (strs.size() == 0) return "";
		if (strs.size() == 1) return strs[0];

		// if strs.size() > 1
		/* debug
		for (auto it = strs.begin(); it != strs.end(); ++it) {
			cout << (*it) << endl;
		}cout << endl;
		*/
		string tmp = strs[0]; // initialization		
		int finish;
		for (int j = 1; j < strs.size(); ++j) {
			finish = min(tmp.size(), strs[j].size());
			tmp = strs[0].substr(0, finish);

			//cout << "finish : " << finish << endl;
			//cout << "j = " << j << endl;
			for (int i = 0; i < finish; ++i) {
				//cout << "tmp[" << i << "]" << endl;
				if (tmp[i] != strs[j][i]) {
					//cout << "No: tmp[" << i << "] no pass, break!" << endl;
					tmp = strs[0].substr(0, i);
					cout << tmp << endl;
					break;
				}
			}
		}
		return tmp;
	}
};

int main() {
	vector<string> inputs;
	cout << "the num of strings : " << endl;
	int n;
	cin >> n;

	string str;
	
	for (int i = 0; i < n; ++i) {
		cin >> str;
		inputs.push_back(str);
	}
	
	Solution sol;
	cout << "result: " << sol.longestCommonPrefix(inputs);

	return 0;
}