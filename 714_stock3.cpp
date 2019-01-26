#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<limits>
using namespace std;

class Solution {
public:
	int maxProfit(vector<int>& p, int fee) {
		p.push_back(-100000);
		int n = p.size(); // the information of prices
		int* b = new int[n]; //the index of buying
		int* local_profit = new int[n];
		int* total_profit = new int[n];
		b[0] = 0;
		local_profit[0] = 0;
		total_profit[0] = 0;
		int m = 0;
		for (int i = 1; i < n; ++i) {
			if (local_profit[i - 1] < 0) {
				if (local_profit[i - 1] <= (p[i] - p[b[i - 1]] - fee)) {
					total_profit[i] = total_profit[i - 1];
					local_profit[i] = (p[i] - p[b[i - 1]] - fee);
					b[i] = i - 1;
					m = i;
				}
				else {
					total_profit[i] = total_profit[i - 1];
					local_profit[i] = 0;
					b[i] = i;
				}
			}
			else {
				if (local_profit[i - 1] <= (p[i] - p[b[i - 1]] - fee)) {

					if ((p[i] - p[b[i - 1]] - fee) >= (p[i] - p[m] - fee + local_profit[i - 1])) {
						total_profit[i] = total_profit[i - 1];
						local_profit[i] = p[i] - p[b[i - 1]] - fee;
						b[i] = b[i - 1];
						m = i;
					}
					else {
						total_profit[i] = total_profit[i - 1] + local_profit[i - 1];
						local_profit[i] = p[i] - p[m] - fee;
						b[i] = m;
						m = i;
					}
				}
				else {
					if (p[i - 1] - p[i] < fee) {
						total_profit[i] = total_profit[i - 1];
						local_profit[i] = local_profit[i - 1];
						b[i] = b[i - 1];
						if (p[i] < p[m]) {
							m = i;
						}
					}
					else {
						total_profit[i] = total_profit[i - 1] + local_profit[i - 1];
						local_profit[i] = 0;
						b[i] = i;
					}
				}
			}

		}
		int result = total_profit[n - 1];
		return result;
	}
	int maxProfit2(vector<int>& p, int fee) {
		int n = p.size();
		int* profit = new int[n + 1];
		profit[0] = 0;
		profit[1] = 0;
		for (int i = 2; i < n + 1; ++i) {
			profit[i] = std::numeric_limits<int>::min();
			for (int k = 0; k < i; ++k) {
				//cout << i << "," << p[i - 1] - p[k] - fee << endl;
				profit[i] =max(profit[i], max(profit[k], profit[k] + p[i-1] - p[k] - fee));
			}
			//cout << "profit[" << i << "] = " << profit[i];
		}
		/*
		for (int i = 0; i < n + 1; ++i) {
			cout << setw(10)<<profit[i];
		}cout << endl;
		*/
		int result = profit[n];
		return result;
	}

	int maxProfit_greedy(vector<int>& p, int fee) {
		int n = p.size();
		if (n < 2) {
			return 0;
		}
		int ans = 0;
		int minV = p[0];
		for (int i = 1; i < n; i++) {
			if (p[i] < minV)
				minV = p[i];
			else if (p[i] - minV > fee) {
				ans += p[i] - fee - minV;
				minV = p[i] - fee;
			}
		}
		return ans;
	}
};

int main() {
	int n;
	int fee;
	cin >> n;
	cin >> fee;
	int tmp;
	vector<int> prices;
	for (int i = 0; i < n; ++i) {
		cin >> tmp;
		prices.push_back(tmp);
	}

	/*
	12
	2
	7 3 2 4 6 2 8 10 11 15 18 24

	10
	2
	2 2 1 1 5 5 3 1 5 4
	*/
	Solution sol;
	cout << "DP: " << endl;
	cout << sol.maxProfit2(prices, fee) << endl;
	cout << "Greedy: " << endl;
	cout << sol.maxProfit_greedy(prices, fee);

	return 0;
}