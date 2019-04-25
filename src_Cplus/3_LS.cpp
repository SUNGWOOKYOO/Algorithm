#include <iostream>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

// leetcode 3/966
class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		if (s.empty()) return 0;
		if (s.length() == 1) return 1;
		int n = s.length();
		int max_length = 0;
		int this_length = 1;
		std::map<char, int> h;
		h[s[0]] = 1;

		for (int i = 1; i < n; ++i) {
			if (h[s[i]] != 0) {
				this_length = min(i - h[s[i]] + 1, this_length + 1);
				h[s[i]] = i + 1;
			}
			else {
				this_length = this_length + 1;
				h[s[i]] = i + 1;
			}
			max_length = max(max_length, this_length);
		}
		
		//h.size()
		char* result = new char[n];
		for (auto it = h.begin(); it != h.end(); ++it) {
			cout << it->first << " " << it->second << endl;
			result[(it->second)-1] = it->first;
		}

		for (int i = 0; i < n; ++i) {
			cout << result[i];
		}
		cout << endl;
		delete[]result;
		

		return max_length;
	}
};

// solution : https://medium.com/@timtim305/leetcode-3-longest-substring-without-repeating-characters-37a425f7c193
int main() {
	/*
	std::map<char, int> h;
	h['a'] = 3;
	h['c'] = 2;
	h['d'] = 4;
	h['a'] = 5;
	for (auto it = h.begin(); it != h.end(); ++it) {
		cout << it->first <<", "<< it->second << endl;
	}
	*/
	string s;
	cin >> s;
	Solution sol; 
	cout << sol.lengthOfLongestSubstring(s) << endl;


	return 0;
}